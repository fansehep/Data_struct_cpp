#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include <deque>
#include <vector>
#include <memory>
#include <assert.h>
#include <unistd.h>
class ThreadPool
{
public:
  // 设置最大的任务数量
  void setMaxQueueSize(int maxsize)
  {
    this->maxQueueSize_ = maxsize;
  }
  ThreadPool() {}

  ~ThreadPool()
  {
    if (running_)
    {
      stop();
    }
  }
  // 停止所有线程
  void stop()
  {
    {
      std::lock_guard<std::mutex> leks(this->mutex_);
      running_ = false;
      cond_empty.notify_all();
      cond_full.notify_all();
    }
    // 回收所有线程
    for (auto &thd : this->threads_)
    {
      thd->join();
    }
  }
  // 开始启动。
  void start(int numThreads)
  {
    assert(threads_.empty());

    running_ = true;
    // 预分配
    threads_.reserve(numThreads);

    for (int i = 0; i < numThreads; ++i)
    {
      // 依次增加线程
      threads_.emplace_back(new std::thread(std::bind(&ThreadPool::runInThread, this)));
    }
    // 如果需要 0 个线程， 并且回调函数不为空 就调用回调函数
    if (numThreads == 0 && callbackfunction_)
    {
      callbackfunction_();
    }
  }
  // 设置该线程池的回调函数
  void setcallbackfunction(std::function<void()> &that)
  {
    this->callbackfunction_ = that;
  }

  // 传入函数
  void run(std::function<void()> task)
  {
    // 如果当前没有创建线程，就直接运行。
    if (threads_.empty())
    {
      task();
    }
    else
    {
      std::unique_lock<std::mutex> lths(this->mutex_);
      //  直到 runnning = true && 最大任务队列 > 0 并且当前任务的数量 >= 最大任务数量。
      while (isFull() && running_)
      {
        cond_full.wait(lths);
      }
      if (!running_)
      {
        return;
      }
      assert(!isFull());

      this->tasks_.push_back(std::move(task));
      cond_empty.notify_one();
    }
  }

private:
  mutable std::mutex mutex_;
  bool isFull() const
  {
    std::lock_guard<std::mutex> lhs(this->mutex_);
    return maxQueueSize_ > 0 && tasks_.size() >= maxQueueSize_;
  }
  //
  void runInThread()
  {
    if (callbackfunction_)
    {
      callbackfunction_();
    }
    while (running_)
    {
      std::function<void()> task(take());
      if (task)
      {
        task();
      }
    }
  }
  // 从任务队列中，获取一个任务并且返回。
  std::function<void()> take()
  {
    std::unique_lock<std::mutex> lths(this->mutex_);

    while (tasks_.empty() && running_)
    {
      cond_empty.wait(lths);
    }
    std::function<void()> task;

    if (!tasks_.empty())
    {
      task = tasks_.front();
      tasks_.pop_front();

      if (maxQueueSize_ > 0)
      {
        cond_full.notify_one();
      }
    }
    return task;
  }

  std::function<void()> callbackfunction_;

  // 任务队列
  std::deque<std::function<void()>> tasks_;
  // 线程对象
  std::vector<std::unique_ptr<std::thread>> threads_;
  // 最大任务队列数量。
  size_t maxQueueSize_ = 0;
  // 当前线程池是否正在运行
  bool running_ = false;
  // 条件变量
  std::condition_variable cond_empty;
  std::condition_variable cond_full;
};


int main(int argc, char *argv[])
{
  ThreadPool st;
  st.setMaxQueueSize(10);
  std::function<void()> callback = [](){ printf("hello,world!\n");};
  st.setcallbackfunction(callback);
  st.run(callback);
  sleep(10);
  st.stop();


  return 0;
}
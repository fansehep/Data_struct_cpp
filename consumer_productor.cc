#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <stack>
#include <string>
#include <unistd.h>
#include <functional>

// 标志位
bool foodready_ = false;
bool foodempty_ = true;

const int size_ = 10;
//  food
std::stack<std::string> food_;
//  互斥锁
std::mutex mutex_;
//  条件变量
std::condition_variable cond_;
//  消费者线程.
std::thread conmuser_;
//  生产者线程.
std::thread producter_;

bool constop = true;
bool prostop = true;

static void conmuse(void *arg)
{
  while (constop)
  {
    std::cout << "conmuse" << std::endl;
    std::unique_lock<std::mutex> lck(mutex_);
    while (!foodempty_)
    {
      cond_.wait(lck);
    }
    for (int i = 0; i < 10; i++)
    {
      char buf[32] = {0};
      snprintf(buf, sizeof(buf), " id : %d ", i);
      food_.push(buf);
    }
    foodready_ = true;
    foodempty_ = false;
    cond_.notify_one();
  }
}
static void product(void *arg)
{
  while (prostop)
  {
    std::cout << "producter" << std::endl;
    std::unique_lock<std::mutex> lck(mutex_);
    while (!foodready_)
    {
      cond_.wait(lck);
    }
    while (!food_.empty())
    {
      std::cout << food_.top() << "has been eaten" << std::endl;
      food_.pop();
    }
    foodempty_ = true;
    foodready_ = false;
    cond_.notify_one();
  }
}
void start()
{
  conmuser_ = std::thread(std::bind(conmuse, nullptr));
  producter_ = std::thread(std::bind(product, nullptr));
}

void stop()
{
  constop = false;
  prostop = false;
  conmuser_.join();
  producter_.join();
}

int main(int argc, char *argv[])
{
  start();
  sleep(15);
  stop();

  return 0;
}
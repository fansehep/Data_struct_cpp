
#include <iostream>
#include <mutex>
#include <stack>
#include <string.h>

template<typename type>
class ThreadSafeStack
{
public:
    ThreadSafeStack(int size)
    {
        this->dataptr = new type(size);
    }
    ThreadSafeStack(int size, type val);
    {
        this->dataptr = new type(size);
        this->realdatasize = size;
        auto ptr = this->dataptr;
        for( int i = 0;i < datasize;i++ )
        {   
            *ptr = type;
        }
    }
    ThreadSafeStack(ThreadSafeStack& that)
    {
        if(this->dataptr == nullptr)
        {
            this->dataptr = new type[that.Size()];
        }
        else if(this->size >= that.Size() )
        {
            memcpy(this->dataptr, )
        }
    }
    void Push(type val)
    {
        if( this->realdatasize == useindex)
        {
            this->
        }
    }
    int Size()
    {
        std::lock_guard<std::mutex> lock(this->mtx);
        return this->mtx;
    }
private:
    type* dataptr = nullptr;
    int   realdatasize = 0;  //实际分配的内存大小
    int   useindex =0;       //当前栈顶指针
    int   malloccount = 0;   //分配次数
    std::mutex mtx;
};



int main(int argc, char* argv[])
{
    std::stack<int> nums;
    nums.emplace();
    nums.empty();
    nums.pop();
    nums.push(1);
    nums.size();
    nums.swap(nums);
    nums.top();


    return 0;
}
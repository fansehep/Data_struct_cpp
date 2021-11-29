

#include <iostream>
#include <stack>


template<typename type>
class Stack
{
public:
    bool Push(type val)
    {
        int oldindex;
        do
        {
            oldindex = this->useindex;
            if( oldindex >= __INT_MAX__ )
            {
                return false;
            } 
            // 任意线程拿到当前的break while循环，其他线程都阻塞在这里。因为此时use_index + 1了，其他线程的这里if循环都为 false
            if(::sync_compare_and_swap(&this->useindex, oldindex, oldindex+1 ))
            {
                break;
            }
        }while(true);
        // 赋值操作
        this->nums[useindex] = val;
        return true;
    }
    bool Pop()
    {
        int oldindex;
        do
        {
            oldindex = this->useindex;
            if( oldindex == 0 )
            {
                return false;
            }
            
        } while (true);
        


    }
private:
    type* nums = nullptr;
    int numsSize = 0;
    int useindex = 0;
};

int main(int argc, char* argv[])
{
    std::stack<int> nums;
    nums.emplace();
    nums.empty();
    nums.pop();
    nums.push(1);
    nums.size();
    return 0;
}
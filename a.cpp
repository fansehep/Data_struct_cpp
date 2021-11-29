#include <iostream>
#include <mutex>
#include <thread>

// 这里的std::lock()需要包含<mutex>头文件
class some_big_object;
void swap(some_big_object &lhs, some_big_object &rhs);
class X
{
private:
    some_big_object some_detail;
    std::mutex m;

public:
    X(some_big_object const &sd) : some_detail(sd) {}

    friend void swap(X &lhs, X &rhs)
    {
        if (&lhs == &rhs)
            return;
        std::lock(lhs.m, rhs.m);                                    // 1
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 2
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); // 3
        swap(lhs.some_detail, rhs.some_detail);
    }
};
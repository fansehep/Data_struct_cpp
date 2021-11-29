/*
    无锁队列的实现  基于链表实现  
    - 由于无所队列需要原子操作，编译的时候记得 加上 -march=native (native表示本机)
*/
#include <iostream>

template<typename type>
class LockFreeQueue
{
private:
    struct Node
    {
        type  m_val;
        Node* m_next = nullptr;
        Node(type val)
        {
            this->val = val;
        }
        Node(){};
        Node(Node& val)
        {   
            this->m_val = val->m_val;
        }
        ~Node()
        {
            delete this->m_next;
        }
    }；
    Node<type>* m_head = nullptr; // 头节点
    Node<type>* m_tail = nullptr; // 尾节点
public:
    LockFreeQueue()
    {
        this->m_tail = this->m_head = new Node<type>(); // 初始化一个节点，头指针和尾指针指向同一节点
    }
    /*
        这里我们先创建一个新的节点。
        用一个 do {}while(condition)
        由于需要保证线程安全，我们使用原子函数 __sync_bool_compare_and_swap()
        这里我们可以看到，只要有一个线程__sync_bool_compare_and_swap，那么其他线程的push操作全部阻塞在这个循环中
        __sync_bool_compare_and_swap 全部失效
        此时只有跳出该while循环的线程可以更新根节点。且不需要循环
    */
    // void push(type val)
    // {
    //     Node<type>* p = nullptr;
    //     Node<type>* m_temp = new Node<type>(); 
    //     // 这里拿到需要拿到尾部节点,
    //     do
    //     {
    //         p = this->m_tail;   // 取得链表指针尾部的快照
    //         /*
    //          这里使用原子操作 __sync_bool_compare_and_swap(void* ptr, type oldval, type newval);
    //          如果这里的 *ptr == oldval, 那么就将 m_temp 赋值给 p->next;
    //         */
    //     } while (__sync_bool_compare_and_swap(p->next, nullptr, m_temp)); // CAS(p->next, nullptr, n);
    //     __sync_bool_compare_and_swap(this->tail, p, m_temp);
    // } 
    // 改良版
    /*
    上面的push函数的缺点就是 : 如果这个线程在更新 tail 节点之前，挂掉了，那么其他线程都处于阻塞状态，这是一件很可怕的事情。
    */
    void push(type val)
    {
        Node<type>* temp = new Node<type>(val);
        Node<type>* t_tail = nullptr;
        Node<type>* t_next = nullptr;
        while(true)
        {
            // 取到尾指针
            t_tail = this->m_tail;
            // 取到尾指针的next指针
            t_next = t_tail->next;
            // 如果尾指针已经被移动，那么就需要重新获得尾指针
            if( t_tail != this->m_tail ) continue;

            if(t_next == nullptr)
            {
                if(::__sync_bool_compare_and_swap(&(t)))
            }
        }
        ::__sync_bool_compare_and_swap(this->m_tail, t_tail, temp);
    }

};




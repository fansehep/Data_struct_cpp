// 红黑树
/*
    1.每个节点要么是黑色，要么是红色
    2.根节点是黑色
    3.每个叶子节点是黑色
    4.每个红色节点的两个子节点一定都是黑色
    5.任意一节点到达每个叶子节点的路径都包含的黑节点。

    1.根节点是黑色，叶节点是不存储数据的黑色空节点
    2.任何相邻的两个节点不能同时为红色
    3.任意节点到达 它 可到达的叶节点间包含了相同数量的黑色节点

    一。删掉红色节点之后，每个节点到达叶节点的路径长度都是相同的
*/



// 未写完，已放弃------<<___>>
#include <iostream>
    // 节点颜色
enum Color{black, red};

template<typename type>
struct Node
{
    type m_val;
    Node* m_left = nullptr;   //左节点
    Node* m_right = nullptr;  //右节点
    Node* m_parent = nullptr; //父节点

    int m_color = red; //由于需要满足红黑树的 任意一个节点到达每个叶子节点的路径都包含相同数量的黑色节点.
                       //所以我们默认不能够直接添加黑色节点,
    ~Node()
    {
        delete this->m_left;
        delete this->m_right;
        delete this->m_parent;
    }
    Node<type>(type val)
    {
        this->m_val = val;
    }
};

template <typename type>
class Red_Black_tree
{
public:
    ~Red_Black_tree()
    {
        ;
    }
    Red_Black_tree()
    {
        this->m_root = nullptr;
    }
    void add(type val)
    {
        //如果是根节点，那就直接返回
        if(this->m_root == nullptr)
        {
            this->m_root = new Node<type>(val); //
            return ;
        }

        Node<type>* tdx = this->m_root;
        //沿着根节点寻找插入位置
        do
        {
            if(val > tdx->m_val)
            {
                tdx = tdx->m_right;
            }
            else if(val < tdx->m_val)
            {
                tdx = tdx->m_left;
            }
            else
            {
                tdx->m_val = val;
                return;
            }
        } while (tdx != nullptr);

        Node<type>* res = new Node<type>(val);
        //到达当前的根节点，需要比较 
        if(val > tdx->m_val)
        {
            tdx->m_right = res;
        }
        else if(val < tdx->m_val)
        {
            tdx->m_left = res;
        }
        else
        {
            tdx->m_val = val;
        }


    }
private:
    // 左旋
    void left_Rotate(Node<type>*& p)
    {
        if(p != nullptr)
        {
            Node<type>* temp = p->m_right;
            p->m_right = temp->m_left;
            if(temp->m_left != nullptr)
            {
                temp->m_left->m_parent = p;
            }
            temp->m_parent = p->m_parent;

            //这里确定传入节点是他父亲节点的左节点还是右节点，需要接上去
            if(p->m_parent == nullptr)
            {
                this->m_root = temp;
            }
            else if(p->m_parent->m_left == p)
            {
                p->m_parent->m_left = temp;
            }
            else
            {
                p->m_parent->m_right = temp;
            }
            temp->m_left = p;
            p->m_parent = temp; 
        }
    }
    // 右旋
    void right_Rotate(Node<type>*& p)
    {
        if(p != nullptr)
        {
            Node<type>* temp = p->m_left;
            temp->m_left = temp->m_right;
            if( temp->m_right != nullptr)
            {
                temp->m_right->m_parent = p;
            }
            temp->m_parent = p->m_parent;
            if( p->m_parent == nullptr )
            {
                this->m_root = temp;
            }
            else if( p->m_parent->right == p)
            {
                p->m_parent->m_left = temp;
            }
            else
            {
                p->m_parent->m_left = temp;
            }
            temp->m_right = p;
            p->m_parent = temp;
        }
    }

    void fid_after_add(Node<type>* tex)
    {
        tex->m_color = red;
        // 1.tex的父节点是红色的，
        if(tex != nullptr && tex!= this->m_root && tex->m_parent->m_color == red)
        {
            if(parent_of(tex) == left_of(parent_of(parent_of(tex))) )
            {
                
            }
        }
    }
    Node<type>* parent_of(Node<type>* node)
    {
        return node != nullptr?node->m_parent:nullptr;
    }
    Node<type>* left_of(Node<type>* node)
    {
        return node != nullptr?node->m_:nullptr;
    }
    Node<type>* right_of(Node<type>* node)
    {
        return node != nullptr?node->m_parent:nullptr;
    }
    //  根节点
    Node<type> *m_root = nullptr;
    //  节点个数
    int m_size = 0;
};

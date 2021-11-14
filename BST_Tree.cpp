#include <iostream>
#include <string>
#include <algorithm>
//由于二叉搜索树是一种树的数据结构，所以没有索引的概念

//
template<typename type>
struct Node
{
    type  m_val;
    Node* m_left   = nullptr;     // 左节点
    Node* m_right  = nullptr;     // 右节点

    Node(int val)
    {
        this->m_val = val;
    }
    ~Node()
    {
        delete(m_left);
        delete(m_right);
    }
};
template<typename type>
class Binary_search_tree
{
public:
    ~Binary_search_tree()
    {
        _Delete_tree(this->m_root);
    }
    //当前树已经存储的元素数量
    int size()
    {
        return this->m_size;
    }
    //清空所有元素
    void clear()
    {
        _Delete_tree(this->m_root);
    }
    //增加元素
    void add(type val)
    {
        insert(val,this->m_root);
    }
    //找到元素
    Node<type>* find(type val)
    {
        Node<type>* res = _Find_Node_(val,this->m_root);
        if( res == nullptr )
        {
            return nullptr;
        }
        return res;
    }

    //删除元素
    bool remove(type val)
    {
        if( _Delete_Node_(val,this->m_root) == true )
        {
            this->m_size --;
            return true;
        }
        else
        {
            return false;
        }
    }
    void preolder_traversal()
    {
        _Pre_older(this->m_root);
    }
    void mid_traversal()
    {
        _Mid_older(this->m_root);
    }
    void epilo_traversal()
    {
        _Epli_older(this->m_root);
    }
private:
    Node<type>* m_root = nullptr;     //根节点
    int   m_size = 0;     //元素数量

    void insert(type& val,Node<type>*& root)
    {
        if(root == nullptr)
        {
            root = new Node<type>(val);
            this->m_size++;
        }
        if(val > root->m_val)
        {
            return insert(val,root->m_right);
        }
        else if(val < root->m_val)
        {
            return insert(val,root->m_left);
        }
    }

    Node<type>* _Find_Node_(type& val,Node<type>*& root)
    {
        if(root == nullptr)
        {
            return nullptr;
        }
        else if( root->m_val == val )
        {
            return root;
        }
        if( val > root->m_val )
        {
            return _Find_Node_(val,root->m_right);
        }
        else if( val < root->m_val )
        {
            return _Find_Node_(val,root->m_left);
        }
        return nullptr;
    }

    bool _Delete_Node_(type& val,Node<type>*& root)
    {
        if(root == nullptr)
        {
            return false;
        }
        // 当遍历到树底，只有一个节点时
        if( root->m_left == nullptr && root->m_right == nullptr )
        {
            if( root->m_val == val )
            {
                delete root;
                root = nullptr;
                return true;
            }
            else
            {
                return false;
            }
        }
        if( val > root->m_val )
        {
            return _Delete_Node_(val,root->m_right);
        }
        else if( val < root->m_val )
        {
            return _Delete_Node_(val,root->m_left);
        }
        // 此时遍历成功，找到该节点，考虑这个节点的属性
        else
        {
            Node<type>* p = nullptr;
            if( root->m_left == nullptr )
            {
                p = root;
                root = root->m_right;
                delete p;
                p = nullptr;
                return true;
            }
            else if( root->m_right == nullptr )
            {
                p = root;
                root = root->m_left;
                delete p;
                p = nullptr;
                return true;
            }
            //在中间层遍历到该节点
            /*
                在中间层遍历到该节点时，需要旋转这棵树，就是因为在他的右子树的最左边的节点是这棵右子树的最小值
            所以我们这里采取赋值方式，来旋转，但是我们仍然要递归地去删除它
            */
            else
            {
                Node<type>* p = root->m_right;
                
                while( p->m_left )
                {
                    p = p->m_left;
                }

                std::swap(root->m_val,p->m_val);

                _Delete_Node_(val,root);
                return true;
            } 
        }
    }
    void _Delete_tree(Node<type>*& root)
    {
        if(root)
        {
            _Delete_tree(root->m_left);
            _Delete_tree(root->m_right);
            delete root;
            root = nullptr;
        }
    }

    void _Pre_older(Node<type>*& root)
    {
        if( root == nullptr )
        {
            return ;
        }
        std::cout<<" "<<root->m_val<<" ";
        _Pre_older(root->m_left);
        _Pre_older(root->m_right);
    }
    void _Mid_older(Node<type>*& root)
    {
        if( root == nullptr )
        {
            return ;
        }
        _Mid_older(root->m_left);
        std::cout<<" "<<root->m_val<<" ";
        _Mid_older(root->m_right);
    }
    void _Epli_older(Node<type>*& root)
    {
        if( root == nullptr )
        {
            return ;
        }
        _Epli_older(root->m_left);
        _Epli_older(root->m_right);
        std::cout<<" "<<root->m_val<<" ";
    }
};

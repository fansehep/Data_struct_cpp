#include <iostream>

template<typename type>
struct Node
{
    type m_val;
    Node* left = nullptr;   //左节点
    Node* right = nullptr;  //右节点
    int m_deepth = 0;       //树的深度
    Node(type val)
    {
        this->m_val = val;
    }
    ~Node()
    {
        delete left;
        delete right;
    }
};

template<typename type>
class AVL_Tree
{
public:
    friend Node<type>;
    //增加元素
    void add(type val)
    {
        _Insert_Node(val,this->m_root);
    }
    //删除元素
    bool erase(type val)
    {
        if( _Delete_Node_(val,this->m_root) )
        {
            return true;
        }
        return false;
    }
    //查找元素
    Node<type>* find(type val)
    {

    }
    //清空元素
    void clear()
    {

    }
private:
    //获取当前节点的高度
    int get_height(Node<type>* root)
    {
        if( root == nullptr )
        {
            return 0;
        }
        else
        {
            return root->m_deepth;
        }
    } 
    // 插入元素
    Node<type>* _Insert_Node(type val,Node<type>* root)
    {
        if( root == nullptr )
        {
            root = new Node<int>(val);
            root->m_deepth = 1;
            return root;
        }
        if( val < root->m_val )
        {
            root->left = _Insert_Node(val,root->left);
        }
        else if( val > root->m_val )
        {
            root->right = _Insert_Node(val,root->right);
        }
        root->m_deepth = 1 + max(get_height(root->left),get_height(root->right));

        int bal = get_height(root->left) - get_height(root->right);

        if( bal > 1 )
        {
            if( val < root->left->m_val )
            {
                right_Rotation(root);
            }
            else
            {
                root->left = left_Rotation(root->left);
                return right_Rotation(root);
            }
        }

        else if( bal < -1 )
        {
            if( val > root->right->m_val )
            {
                return left_Rotation(root);
            }
            else
            {
                root->right = right_Rotation(root->right);
                return left_Rotation(root);
            }
        }
        return root;
    }
    //右旋节点
    /*
    右旋节点主要是因为根节点的左子树高度太高
            40      此时以40这个根节点来看，左子树的高度远远大于右子树的高度
           /        需要将 根节点 右旋，变成这样 
         30              30
        /  \            /  \
      20    35         20  40
                           /
                         35


    
    */
    Node<type>* right_Rotation(Node<type>* root)
    {
        Node<type>* newhead = root->left;
        root->left = newhead->right;
        newhead->right = root;
        
        root->m_deepth = 1 + max(get_height(root->left),get_height(root->right));
        newhead->m_deepth = 1 + max(get_height(root->left),get_height(root->right));

        return newhead;                                                                                                                                                                                                                                                                                                                                                                                                             
    }



    //左旋节点
    Node<type>* left_Rotation(Node<type>* root)
    {

        Node<type>* newhead = root->right;
        root->right = newhead->left;
        newhead->left = root;

        root->m_deepth = 1 + max(get_height(root->left), get_height(root->right));
        newhead->m_deepth = 1 + max(get_height(root->left), get_height(root->right));

        return newhead;
    }



    //删除元素
    Node<type>* _Delete_Node_(type val,Node<type>* root)
    {
        if( root == nullptr )
        {
            return nullptr;
        }
        if( val < root->m_val )
        {
            return _Delete_Node_(val,root->left);
        }
        else if( val > root->m_val )
        {
            return _Delete_Node_(val,root->right);
        }
        else
        {
            Node<type>* p = root->right;
            if( root->right == nullptr )
            {
                Node<type>* l = root->left;
                delete(root);
                root = l;
            }
            else if( root->left == nullptr )
            {
                delete(root);
                root = p;
            }
            //左右子节点都不为空
            else
            {
                while( p->left != nullptr )
                {
                    p = p->left;
                }
                root->m_val = p->m_val;
                root->right = _Delete_Node_(val,root->right);
            }
        }
        // 删除叶子节点，直接返回
        if( root == nullptr )
        {
            return root;
        }

        root->m_deepth = 1 + max(get_height(root->left)，get_height(root->right));
        int bal = get_height(root->left) - get_height(root->right);

        if( bal > 1)
        {
            if( get_height(root->left) >= get_height(root->right) )
            {
                return right_Rotation(root);
            }
            else
            {
                root->left = left_Rotation(root->left)；
                return right_Rotation(root);
            }
        }
        else if( bal < -1 )
        {
            if( get_height(root->right) >= get_height(root->left) )
            {
                return left_Rotation(root);
            }
            else
            {   
                root->right = right_Rotation(root->right);
                return left_Rotation(root);
            } 
        }
        return root;
    }

    Node<type>* m_root = nullptr;
    int   m_size = 0;
};
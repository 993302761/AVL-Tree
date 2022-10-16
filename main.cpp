#include <iostream>
using namespace std;

#include "stdio.h"

template<class T>       //类模板

struct treeNode{
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
    int bf; //平衡因子
    T data;
    treeNode(const T& x):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    data(x),
    bf(0){}
};

template<class K>

class AvlTree{

private:

    typedef treeNode<K> node;

    node *root;

    void freeNode(node *s){
        if (s== nullptr)
            return;
        else{
            freeNode(s->left);
            freeNode(s->right);
            delete s;
        }
    }


    void show(node *n){
        if (n== nullptr)
            return;
        cout<<"data: "<<n->data<<"  平衡因子:"<<n->bf<<endl;
        show(n->left);
        show(n->right);
    }


    void addBF(node *n){
        if (n->parent== nullptr){
            return;
        }
        node *parent=n->parent;
        if (parent->left==n){
            (parent->bf)--;
        } else{
            (parent->bf)++;
        }
        if ((parent->bf)==1||(parent->bf)==-1){
            addBF(parent);
        } else if ((parent->bf)==2||(parent->bf)==-2){
            check(parent);
        }
    }

    void delBF(node *n){
        if (n->parent== nullptr){
            return;
        }
        node *parent=n->parent;
        if (parent->left==n){
            (parent->bf)++;
        } else{
            (parent->bf)--;
        }
        if ((parent->bf)==2||(parent->bf)==-2){
            check(parent);
        }
        delBF(parent);
    }

    node *check(node *p) {
        if (p->left!= nullptr&&p->bf==-2&&p->left->bf==-1){
            return RR(p);
        } else if (p->right!= nullptr&&p->bf==2&&p->right->bf==1){
            return LL(p);
        } else if (p->left!= nullptr&&p->bf==-2&&p->left->bf==1){
            return LR(p);
        } else if (p->right!= nullptr&&p->bf==2&&p->right->bf==-1){
            return RL(p);
        }
    }

    //左旋
    node *LL(node *p){
        node *right=p->right;

        //   让 right 的左子树 成为 p 的右子树
        p->right= right->left;
        if (right->left!= nullptr){
            right->left->parent=p;
        }

        // 让 p 成为 right 的左子树
        if (p==root){
            root=right;
            right->parent= nullptr;
        } else{
            if (p->parent->left==p){
                p->parent->left=right;
            } else{
                p->parent->right=right;
            }
            right->parent=p->parent;
        }

        right->left=p;
        p->parent=right;

        p->bf=0;
        right->bf=0;
        return right;
    }

    //右旋
    node *RR(node *p){
        node *left=p->left;

        //  让 left 的右子树 成为 p 的左子树
        p->left=left->right;
        if (left->right!= nullptr){
            left->right->parent=p;
        }

        //        让 p 成为 left 的右子树
        if (p== root){
            root=left;
            left->parent= nullptr;
        } else{
            if (p->parent->left==p){
                p->parent->left=left;
            } else{
                p->parent->right=left;
            }
            left->parent=p->parent;
        }

        left->right=p;
        p->parent=left;

        p->bf=0;
        left->bf=0;

        return left;
    }


    //左旋后右旋
    node *LR(node *p){
        node *left=p->left;
        node *leftR=left->right;
        int bf=leftR->bf;
        LL(p->left);
        RR(p);
        if (bf==1){
            p->bf=1;
            left->bf=0;
            leftR->bf=0;
        } else if (bf==-1){
            p->bf=0;
            left->bf=-1;
            leftR->bf=0;
        } else if (bf==0){
            p->bf=0;
            left->bf=0;
            leftR->bf=0;
        }
        return leftR;
    }

    //右旋后左旋
    node * RL(node *p){
        node *right=p->right;
        node *rightL=right->left;
        int bf=rightL->bf;
        RR(p->right);
        LL(p);
        if (bf==1){
            p->bf=-1;
            right->bf=0;
            rightL->bf=0;
        } else if (bf==-1){
            p->bf=0;
            right->bf=1;
            rightL->bf=0;
        } else if (bf==0){
            p->bf=0;
            right->bf=0;
            rightL->bf=0;
        }
        return rightL;
    }

    int Height(node *p){
        if (p== nullptr){
            return 0;
        }
        int left=Height(p->left);
        int right=Height(p->right);

        return max(left,right)+1;
    }



    int IsBalance2(node * root)
    {
        // 先判断当前树的左、右子树是否平衡，再判断当前树是否平衡
        // 不平衡返回-1，平衡则返回当前树的高度

        // 当前树为空，返回高度0
        if (root == nullptr)
            return 0;

        // 当前树不为空，分别计算左右子树的高度
        int leftHeight = IsBalance2(root->left);
        int rightHeight = IsBalance2(root->right);

        if (rightHeight - leftHeight != root->bf) // 检查当前树的平衡因子是否计算正确
        {
            cout << "平衡因子异常:" << root->data << "  " << root->bf << endl;
        }

        // 左子树高度等于-1、右子树高度等于-1、左右子树高度差的绝对值大于1，说明当前树不平衡
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1)
            return -1;

        // 运行到这里来了，说明当前树是平衡的，返回当前树的高度
        return max(leftHeight, rightHeight) + 1;
    }





public:

    AvlTree():root(nullptr){}

    ~AvlTree(){
        freeNode(root);
    }


    //插入节点
    bool insert(const K& data){
        if(root== nullptr)
        {
            root=new node(data);
        }
        else
        {
            node *head=root;
            node *s=new node(data);
            while (head!= nullptr)
            {
                if (s->data==head->data){
                    return false;
                }
                else if (s->data<head->data)
                {
                    if (head->left!= nullptr)
                    {
                        head= head->left;
                    } else{
                        head->left=s;
                        s->parent=head;
                        (head->bf)--;
                        if (head->bf==1||head->bf==-1)
                        {
                            addBF(head);
                        }
                        return true;
                    }
                } else{
                    if (head->right!= nullptr)
                    {
                        head = head->right;
                    } else{
                        head->right=s;
                        s->parent=head;
                        (head->bf)++;
                        if (head->bf==1||head->bf==-1)
                        {
                            addBF(head);
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }

    //遍历
    void showTree(){
        show(root);
    }

    node *getNode(int data){
        node *p=root;
        while (p!= nullptr){
            if (p->data==data){
                return p;
            } else if (p->data<data){
                p=p->right;
            } else{
                p=p->left;
            }
        }
        return nullptr;
    }


    //获取高度
    int getHeight(){
        return Height(root);
    }

    //是否平衡
    bool IsBalance()
    {
        return IsBalance2(root) != -1;
    }


    bool deleteNode(int data){
        node *p=root;
        while (p!= nullptr){
            if (p->data==data){
                //删除叶子结点。操作：直接删除，然后依次向上调整为AVL树。
                if (p->left== nullptr&&p->right== nullptr){
                    node *parent=p->parent;

                    if (parent->left==p){
                        parent->left= nullptr;
                        (parent->bf)++;
                        if (parent->bf==2){
                            parent=check(parent);
                        }
                        delBF(parent);
                    } else{
                        parent->right= nullptr;
                        (parent->bf)--;
                        if (parent->bf==-2){
                            parent=check(parent);
                        }
                        delBF(parent);
                    }

                    delete p;
                    return true;

                } else if (p->left!= nullptr&&p->right== nullptr){
                    //删除非叶子节点，该节点只有左孩子。操作：该节点的值替换为左孩子节点的值，然后删除左孩子节点
                    node *left=p->left;
                    p->data=left->data;
                    p->left= nullptr;
                    (p->bf)++;
                    delete left;
                    delBF(p);
                    return true;
                } else if (p->left== nullptr&&p->right!= nullptr){
                    //删除非叶子节点，该节点只有右孩子。操作：该节点的值替换为右孩子节点的值，然后删除右孩子节点
                    node *right=p->right;
                    p->data=right->data;
                    p->right= nullptr;
                    (p->bf)--;
                    delete right;
                    delBF(p);
                    return true;
                } else{
                    //删除非叶子节点，该节点既有左孩子，又有右孩子。操作：该节点的值替换为该节点的前驱节点（或者后继节点）然后删除前驱节点（或者后继节点）
                    node *s=p->left;
                    while (s->right!= nullptr){
                        s=s->right;
                    }
                    p->data=s->data;
                    if (s->left!= nullptr){
                        node *sLeft=s->left;
                        s->data=sLeft->data;
                        s->left= nullptr;
                        (s->bf)++;
                        delBF(s);
                        delete sLeft;
                    } else{
                        p->data=s->data;
                        node *parent=s->parent;
                        if (parent->left==s){
                            parent->left= nullptr;
                            (parent->bf)++;
                            if (parent->bf==2){
                                parent=check(parent);
                                delBF(parent);
                            }
                        } else{
                            parent->right= nullptr;
                            (parent->bf)--;
                            if (parent->bf==-2){
                                parent=check(parent);
                                delBF(parent);
                            }
                        }
                        delete s;
                    }
                }
            } else if (p->data<data){
                p=p->right;
            } else{
                p=p->left;
            }
        }
    }

};


int main() {
    AvlTree<int> s;
    s.insert(6);
    s.insert(4);
    s.insert(8);
    s.insert(2);
    s.insert(5);
    s.insert(1);
    s.insert(7);
    s.insert(0);

    s.deleteNode(4);
    cout<<"---------------------"<<endl;
    s.showTree();
    cout<<"---------------------"<<endl;
    cout<<s.IsBalance()<<endl;
}

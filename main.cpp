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


    void getNode(node *n){
        if (n== nullptr)
            return;
        cout<<n->data<<endl;
        getNode(n->left);
        getNode(n->right);
    }


    void updateBF(node *n){
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
            updateBF(parent);
        } else if ((parent->bf)==2||(parent->bf)==-2){
            check(parent);
        }
    }

    void check(node *p) {
        if (p->bf==-2&&p->left->bf==-1){
            RR(p);
        } else if (p->bf==2&&p->right->bf==1){
            LL(p);
        } else if (p->bf==-2&&p->left->bf==1){
            LR(p);
        } else if (p->bf==2&&p->right->bf==-1){
            RL(p);
        }
    }

    //左旋
    void LL(node *p){
        node *right=p->right;

        //   让 right 的左子树 成为 p 的右子树
        p->right= right->left;
        if (right->left!= nullptr){
            right->left->parent=p;
        }

        // 让 p 成为 right 的左子树
        if (p==root){
            root==right;
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
    }

    //右旋
    void RR(node *p){
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
    }


    //左旋后右旋
    void LR(node *p){
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
    }

    //右旋后左旋
    void RL(node *p){
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
            cout << "平衡因子异常:" << root->data << endl;
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
                if (s->data<head->data)
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
                            updateBF(head);
                        }
                        break;
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
                            updateBF(head);
                        }
                        break;
                    }
                }
            }
        }
    }

    void showTree(){
        getNode(root);
    }

    int getHeight(){
        return Height(root);
    }


    bool IsBalance()
    {
        return IsBalance2(root) != -1;
    }



};


int main() {
    AvlTree<int> s;
    s.insert(6);
    s.insert(3);
    s.insert(8);
    s.insert(2);
    s.insert(5);
    s.insert(1);
    s.insert(7);
    s.insert(9);
    s.showTree();
    cout<<"---------------------"<<endl;
    cout<<s.getHeight()<<endl;
    cout<<"---------------------"<<endl;
    cout<<s.IsBalance()<<endl;
}

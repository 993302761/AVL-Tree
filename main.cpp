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
        getNode(n->left);
        cout<<n->data<<endl;
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
            check();
        }
    }

    void check() {

    }

    //左旋
    void LL(node *p){
        node *right=p->right;

        //   让 right 的左子树 成为 p 的右子树
        p->right= right->left;
        right->left->parent=p;

        // 让 p 成为 right 的左子树
        if (p==root){
            root==right;
            right->parent= nullptr;
            right->left=p;
            p->parent=right;
        } else{
            if (p->parent->left==p){
                p->parent->left=right;
            } else{
                p->parent->right=right;
            }
            right->parent=p->parent;
            right->left=p;
            p->parent=right;
        }
        p->bf=0;
        right->bf=0;
    }

    //右旋
    void RR(node *p){
        node *left=p->left;

        //  让 left 的右子树 成为 p 的左子树
        p->left=left->right;
        left->right->parent=p;

        //        让 p 成为 left 的右子树
        if (p== root){
            root=left;
            left->parent= nullptr;
            left->right=p;
            p->parent=left;
        } else{
            if (p->parent->left==p){
                p->parent->left=left;
            } else{
                p->parent->right=left;
            }
            left->parent=p->parent;
            left->right=p;
            p->parent=left;
        }
        p->bf=0;
        left->bf=0;
    }


    //左旋后右旋
    void LR(){

    }

    //右旋后左旋
    void RL(){

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

};


int main() {
    AvlTree<int> s;
    s.insert(6);
    s.insert(3);
    s.insert(2);
    s.insert(5);
    s.insert(8);
    s.insert(7);
    s.insert(9);
    s.showTree();
}

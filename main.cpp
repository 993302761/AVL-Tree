#include <iostream>
using namespace std;

#include "stdio.h"

template<class T>       //类模板

struct treeNode{
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
    int ef; //平衡因子
    T data;
    treeNode(const T& x):
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    data(x),
    ef(0){}
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

public:

    AvlTree():root(nullptr){}

    ~AvlTree(){
        freeNode(root);
    }

    bool insert(const K& data){
        if(root== nullptr){
            root=new node(data);
        } else{
            node *head=root;
            node *s=new node(data);
            while (head!= nullptr){
                if (s->data<head->data){
                    if (head->left!= nullptr){
                        head= head->left;
                    } else{
                        head->left=s;
                        s->parent=head;
                        break;
                    }
                } else{
                    if (head->right!= nullptr) {
                        head = head->right;
                    } else{
                        head->right=s;
                        s->parent=head;
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

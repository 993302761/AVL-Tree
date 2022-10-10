#include <iostream>
using namespace std;
#include "stdio.h"

template<class T>

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

struct node{
    int a;
};


int main() {
//    struct treeNode<int> s= *(struct treeNode<int> *) malloc(sizeof (struct treeNode<int>));
//    cout<<s.ef;

    node s{1};
    cout<<s.a;
}

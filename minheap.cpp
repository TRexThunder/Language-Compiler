/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
    size=0;
    root=NULL;
}

void HeapifyUp(HeapNode* nd) {
    while (nd->par!=NULL) {
        if (nd->val<nd->par->val) {
            int temp=nd->val;
            nd->val=nd->par->val;
            nd->par->val=temp;
            nd=nd->par;
        }
        else break;
    }
}

HeapNode* addtoheap(HeapNode* root, int sz, int lower, int n) {
    if (sz==1) {
        HeapNode* node=new HeapNode(n);
        root->left=node;
        node->par=root;
        HeapifyUp(node);
    }
    else if (sz==2) {
        HeapNode* node=new HeapNode(n);
        root->right=node;
        node->par=root;
        HeapifyUp(node);
    }
    else {
        int upper=2*lower+1;
        if (sz-lower<upper-sz) root->left=addtoheap(root->left, sz-((lower-1)/2+1), (lower-1)/2, n);
        else root->right=addtoheap(root->right, sz-((upper-1)/2+1), (lower-1)/2, n);
    }
    return root;
}

void MinHeap::push_heap(int num){
    if (root==NULL) {
        HeapNode* node=new HeapNode(num);
        root=node;
    }
    else {
        int count=0, x=size+1;
        while (x>1) {
            count++;
            x/=2;
        }
        int l=1;
        for (int i=0; i<count; i++) l*=2;
        l-=1;
        root=addtoheap(root, size, l, num);
    }
    size++;
}

int MinHeap::get_min(){
    if (root==NULL) return -1;
    return root->val;
}

void HeapifyDown(HeapNode* node){
    if (node==NULL) return;
    else if (node->left==NULL) return;
    else if (node->val>node->left->val && node->right==NULL) {
        int temp=node->val;
        node->val=node->left->val;
        node->left->val=temp;
        HeapifyDown(node->left);
    }
    else if (node->val>node->left->val && node->left->val<=node->right->val) {
        int temp=node->val;
        node->val=node->left->val;
        node->left->val=temp;
        HeapifyDown(node->left);
    }
    else if (node->right==NULL) return;
    else if (node->val>node->right->val && node->right->val<node->left->val) {
        int temp=node->val;
        node->val=node->right->val;
        node->right->val=temp;
        HeapifyDown(node->right);
    }
}

int hatao(HeapNode* root, int sz, int lower){
    if (sz==2) {
        int res=root->left->val;
        delete root->left;
        root->left=NULL;
        return res;
    }
    else if (sz==3) {
        int res=root->right->val;
        delete root->right;
        root->right=NULL;
        return res;
    }
    int upper=2*lower+1;
    if (sz-lower<=upper-sz) return hatao(root->left, sz-((lower-1)/2+1), (lower-1)/2);
    else return hatao(root->right, sz-((upper-1)/2+1), (lower-1)/2);
}

void MinHeap::pop(){
    if (root==NULL) return;
    else if (size==1) {
        root=NULL;
        size--;
        return;
    }
    int count=0, x=size;
    while (x>1) {
        count++;
        x/=2;
    }
    int l=1;
    for (int i=0; i<count; i++) l*=2;
    l-=1;
    root->val=hatao(root, size, l);
    HeapifyDown(root);
    size--;
}

void Demolish(HeapNode* node) {
    if (node==NULL) return;
    else {
        Demolish(node->left);
        Demolish(node->right);
        delete node;
    }
}

MinHeap::~MinHeap(){
    size=0;
    Demolish(root);
}
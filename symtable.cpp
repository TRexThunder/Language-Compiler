/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

int ht(SymNode* node){
    if (node==NULL) return -1;
    else return node->height;
}

int balance(SymNode* node){
    if (node==NULL) return 0;
    else return ht(node->left)-ht(node->right);
}

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

SymNode* addtotable(SymNode* root, string k){
    if (k<root->key && root->left==NULL) {
        SymNode* node=new SymNode(k);
        root->left=node;
        node->par=root;
    }
    else if (k>root->key && root->right==NULL) {
        SymNode* node=new SymNode(k);
        root->right=node;
        node->par=root;
    }
    else if (k<root->key) root->left=addtotable(root->left, k);
    else root->right=addtotable(root->right, k);
    root->height=1+max(ht(root->left), ht(root->right));
    int check=balance(root);
    if (check>1 && k<root->left->key) return root->LeftLeftRotation();
    else if (check>1 && k>root->left->key) return root->LeftRightRotation();
    else if (check<-1 && k<root->right->key) return root->RightLeftRotation();
    else if (check<-1 && k>root->right->key) return root->RightRightRotation();
    return root;
}

void SymbolTable::insert(string k){
    size++;
    if (root==NULL) {
        SymNode* node=new SymNode(k);
        root=node;
        return;
    }
    root=addtotable(root, k);
}

SymNode* rem(SymNode* root, string k){
    if (root==NULL) return root;
    else if (k==root->key && root->left==NULL) {
        SymNode* temp=root->right;
        delete root;
        return temp;
    }
    else if (k==root->key && root->right==NULL) {
        SymNode* temp=root->left;
        delete root;
        return temp;
    }
    else if (k<root->key) root->left=rem(root->left, k);
    else if (k>root->key) root->right=rem(root->right, k);
    else {
        SymNode* succ=root->right;
        while (succ->left!=NULL) succ=succ->left;       
        root->key=succ->key;
        root->address=succ->address;
        root->right=rem(root->right, succ->key);
    }
    root->height=1+max(ht(root->left), ht(root->right));
    int check=balance(root);
    if (check>1 && ht(root->left->left)>=ht(root->left->right)) return root->LeftLeftRotation();
    else if (check>1 && ht(root->left->left)<ht(root->left->right)) return root->LeftRightRotation();
    else if (check<-1 && ht(root->right->left)>ht(root->right->right)) return root->RightLeftRotation();
    else if (check<-1 && ht(root->right->left)<=ht(root->right->right)) return root->RightRightRotation();
    return root;
}

void SymbolTable::remove(string k){
    int result=search(k);
    if (result!=-2) {
        size--;
        root=rem(root, k);
    }
}

int where(SymNode* root, string k){
    if (root==NULL) return -2;
    else {
        if (k==root->key) return root->address;
        else if (k<root->key) return where(root->left, k);
        else return where(root->right, k);
    }
}

int SymbolTable::search(string k){
    return where(root, k);
}

void assign(SymNode* root, string k, int idx){
    if (root==NULL) return;
    if (k==root->key) root->address=idx;
    else if (k<root->key) assign(root->left, k, idx);
    else assign(root->right, k, idx);
}

void SymbolTable::assign_address(string k,int idx){
    assign(root, k, idx);
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void Destroy(SymNode* root){
    if (root==NULL) return;
    else {
        Destroy(root->left);
        Destroy(root->right);
        delete root;
    }
}

SymbolTable::~SymbolTable(){
    size=0;
    Destroy(root);
}
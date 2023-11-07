/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="";
    height=-1;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* temp=this->left;
    this->left=temp->right;
    temp->right=this;
    temp->par=this->par;
    this->par=temp;
    if (this->left!=NULL) this->left->par=this;
    if (this->left==NULL && this->right==NULL) this->height=0;
    else if (this->right==NULL) this->height=1+this->left->height;
    else if (this->left==NULL) this->height=1+this->right->height;
    else this->height=1+std::max(this->left->height, this->right->height);
    if (temp->left==NULL && temp->right==NULL) temp->height=0;
    else if (temp->right==NULL) temp->height=1+temp->left->height;
    else if (temp->left==NULL) temp->height=1+temp->right->height;
    else temp->height=1+std::max(temp->left->height, temp->right->height);
    return temp;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* temp=this->right;
    this->right=temp->left;
    temp->left=this;
    temp->par=this->par;
    this->par=temp;
    if (this->right!=NULL) this->right->par=this;
    if (this->left==NULL && this->right==NULL) this->height=0;
    else if (this->right==NULL) this->height=1+this->left->height;
    else if (this->left==NULL) this->height=1+this->right->height;
    else this->height=1+std::max(this->left->height, this->right->height);
    if (temp->left==NULL && temp->right==NULL) temp->height=0;
    else if (temp->right==NULL) temp->height=1+temp->left->height;
    else if (temp->left==NULL) temp->height=1+temp->right->height;
    else temp->height=1+std::max(temp->left->height, temp->right->height);
    return temp;
}

SymNode* SymNode::LeftRightRotation(){
    this->left=this->left->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
    this->right=this->right->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode::~SymNode(){
    par=NULL;
    left=NULL;
    right=NULL;
}
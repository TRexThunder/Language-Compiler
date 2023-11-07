/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="EQ";
    id="";
    num=0;
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    if (t[0]=='(' || t[0]==')') return;
    else if (t[0]=='+') {
        type="ADD";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if (t[0]=='-' && t.length()==1) {
        type="SUB";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if (t[0]=='*') {
        type="MUL";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if (t[0]=='/') {
        type="DIV";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if (t[0]=='%') {
        type="MOD";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if (t[0]==':' && t[1]=='=') {
        type="EQ";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if ((t[0]>='0' && t[0]<='9') || (t.length()>1 && t[0]=='-')) {
        type="VAL";
        id="";
        num=stoi(t);
        left=NULL;
        right=NULL;
    }
    else if (t[0]=='d' && t[1]=='e' && t[2]=='l') {
        type="DEL";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else if (t[0]=='r' && t[1]=='e' && t[2]=='t') {
        type="RET";
        id="";
        num=v;
        left=NULL;
        right=NULL;
    }
    else {
        type="VAR";
        id=t;
        num=v;
        left=NULL;
        right=NULL;
    }
}

ExprTreeNode::~ExprTreeNode(){
    left=NULL;
    right=NULL;
}


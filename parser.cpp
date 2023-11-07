/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    expr_trees={};
    symtable=new SymbolTable();
    last_deleted=-1;
}

ExprTreeNode* maker(vector<string> v, int first, int last) {
    if (first>last) return NULL;
    else {
        if (first==last) {
            ExprTreeNode* ans=new ExprTreeNode(v[first], 0);
            return ans;
        }
        else {
            int count=0, lastofleft, i=2;
            if (v[first+1]=="(") count++;
            while (count!=0) {
                if (v[first+i]=="(") count++;
                else if (v[first+i]==")") count--;
                i++;
            }
            lastofleft=first+i-1;
            ExprTreeNode* l=maker(v, first+1, lastofleft);
            ExprTreeNode* r=maker(v, lastofleft+2, last-1);
            ExprTreeNode* current=new ExprTreeNode(v[lastofleft+1], 0);
            current->left=l;
            current->right=r;
            return current;
        }
    }
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* head=new ExprTreeNode(expression[1], 0);
    ExprTreeNode* lt=new ExprTreeNode(expression[0], 0);
    head->left=lt;
    ExprTreeNode* rt=maker(expression, 2, expression.size()-1);
    head->right=rt;
    expr_trees.push_back(head);
    if (lt->type=="VAR") {
        int check=symtable->search(lt->id);
        if (check==-2) symtable->insert(lt->id);
    }
    else if (lt->type=="DEL") symtable->remove(lt->id);
}

void Destruction(ExprTreeNode* node){
    if (node==NULL) return;
    else {
        Destruction(node->left);
        Destruction(node->right);
        delete node;
    }
}

Parser::~Parser(){
    int sz=expr_trees.size();
    for (int i=0; i<sz; i++) Destruction(expr_trees[i]);
    expr_trees={};
    delete symtable;
    last_deleted=-1;
}
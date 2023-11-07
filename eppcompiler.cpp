/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

ofstream abcd;
EPPCompiler::EPPCompiler(){
    output_file="output";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;
    for (int i=0; i<mem_limit; i++) least_mem_loc.push_heap(i);
}

void EPPCompiler::compile(vector<vector<string>> code){
    int sz=code.size();
    abcd.open(output_file);
    for (int i=0; i<sz; i++) {
        if (code[i][0]=="ret") {
            targ.parse(code[i]);
            vector<string> ans=generate_targ_commands();
            write_to_file(ans);
        }
        else if (code[i][0]=="del") {
            int x=targ.symtable->search(code[i][2]);
            targ.last_deleted=x;
            targ.parse(code[i]);
            least_mem_loc.push_heap(x);
            vector<string> ans=generate_targ_commands();
            write_to_file(ans);
        }
        else {
            targ.parse(code[i]);
            int x=targ.symtable->search(code[i][0]);
            if (x==-1) {
                targ.symtable->assign_address(code[i][0], least_mem_loc.get_min());
                least_mem_loc.pop();
            }
            vector<string> ans=generate_targ_commands();
            write_to_file(ans);
        }
    }
    abcd.close();
}

void generate(ExprTreeNode* node, vector<string> &a, Parser &t) {
    if (node==NULL) return;
    else {
        generate(node->right, a, t);
        generate(node->left, a, t);
        if (node->type=="VAL") {
            string s="PUSH "+to_string(node->num);
            a.push_back(s);
        }
        else if (node->type=="VAR") {
            string s="PUSH mem["+to_string(t.symtable->search(node->id))+"]";
            a.push_back(s);
        }
        else a.push_back(node->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    int n=targ.expr_trees.size();
    ExprTreeNode* root=targ.expr_trees[n-1];
    vector<string> answer={};
    generate(root->right, answer, targ);
    if (root->left->type=="VAR") {
        string s="mem["+to_string(targ.symtable->search(root->left->id))+"] = POP";
        answer.push_back(s);
    }
    else if (root->left->type=="DEL") {
        string s="DEL = mem["+to_string(targ.last_deleted)+"]";
        answer.push_back(s);
    }
    else answer.push_back("RET = POP");
    return answer;
}

void EPPCompiler::write_to_file(vector<string> commands){
    int n=commands.size();
    for (int i=0; i<n; i++) abcd<<commands[i]<<endl;
}

EPPCompiler::~EPPCompiler(){
  
}

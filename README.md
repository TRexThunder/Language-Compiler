# Language-Compiler
Course Project (COL106): Created a compiler for a language of arithmetic infix expressions called E++, which generates code for parse trees in a target language Targ, which is assumed to execute on a stack machine. The project involved using self-implemented AVL trees for storing the addresses of variables and min-heaps for efficient memory management.
## Description of Files
1. symnode.cpp and symtable.cpp: To implement an AVL tree to store the addresses of variables.
2. exprtreenode.cpp and parser.cpp: To convert an input vector of tokenized expressions to a tree structure.
3. heapnode.cpp and minheap.cpp: To map the variable to the least available memory address.
4. eppcompiler.cpp: To parse each input tokenized expression, assign a memory mapping if the expression is a variable assignment or free up the memory address if it’s a delete statement and finally compile the code i.e generate and write all the Targ commands to the output file.

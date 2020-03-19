#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__
#include <string>
#include <iostream>
class Scope;
class GlobalScope;
class Symbol;
class Semantic {
    public:
        static Scope* globleScope;
        static Scope* top_scope;
        static void PrintSymbolTable();
};
#endif 

#ifndef __SEMANTIC_DECL_H__
#define __SEMANTIC_DECL_H__
#include "../semantic/semantic.h"
#include <utility> 
class Decl;
class VarDecl;
class ClassDecl;
class InterfaceDecl;
class FnDecl;

class SemanticDecl : public Semantic {
    public:
        static void handle(Decl*);
        static void handle(VarDecl*);
        static void handle(ClassDecl*);
        static void handle(InterfaceDecl *);
        static void handle(FnDecl *);
};
#endif 
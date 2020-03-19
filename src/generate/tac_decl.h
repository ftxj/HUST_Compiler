#ifndef __GENERATE_DECL_H__
#define __GENERATE_DECL_H__
#include "../generate/tac.h"
#include <utility> 
class Decl;
class VarDecl;
class ClassDecl;
class InterfaceDecl;
class FnDecl;
class Scope;

class TACDecl : public TAC {
    public:
        static void handle(Decl*, Scope*);
        static void handle(VarDecl*, Scope*);
        static void handle(ClassDecl*, Scope*);
        static void handle(InterfaceDecl *, Scope*);
        static void handle(FnDecl *, Scope*);
};
#endif 
#include "../generate/rw.h"
#include "../ast/ast_expr.h"
#include "../generate/codegen.h"
#include "../symbol/Scope.h"
#include "../symbol/ClassSymbol.h"
#include "../tools/utility.h"

#include "../generate/tac.h"
#include "../generate/tac_expr.h"

Location* RW::read(Expr* e, Scope* s) {
    if(e->getVarLocation() == nullptr) {
        return e->Emit(s);
    }
    return e->getVarLocation();
}

void RW::store(Expr* e, Scope* s,Location* dst) {

}

Location* RW::read(FieldAccess* exp, Scope* curScope) {
    Location* varP = nullptr; 
    varP = exp->Emit(curScope);
    ClassSymbol* cScope = nullptr;
    cScope = curScope->getClassScope();
    if(exp->base != nullptr || 
        (cScope != nullptr && 
            cScope->getSymbol(exp->field->getName(), false) == curScope->getSymbol(exp->field->getName(), true))) {
            return TAC::generator->GenLoad(varP);
    }
    return varP;
}

void RW::store(FieldAccess* exp, Scope* curScope, Location* src) {
    Location* varP = exp->getVarLocation(); 
    if(varP == nullptr) {
        varP = exp->Emit(curScope);
    }
    ClassSymbol* cScope = nullptr;
    cScope = curScope->getClassScope();
    if(exp->base != nullptr || 
        (cScope != nullptr && cScope->getSymbol(exp->field->getName(), false) == curScope->getSymbol(exp->field->getName(), true))) {
        TAC::generator->GenStore(varP, src);
    }
    else {
        TAC::generator->GenAssign(varP, src);
    }
}

Location* RW::read(ArrayAccess* exp, Scope* curScope) {
    Location *curr_loc = exp->getVarLocation();
    if(curr_loc == nullptr) curr_loc = exp->Emit(curScope); 
    return TAC::generator->GenLoad(curr_loc); 
}

void RW::store(ArrayAccess* exp, Scope* curScope, Location* src) {
    Location *curr_loc = exp->getVarLocation();
    if(curr_loc == nullptr) curr_loc = exp->Emit(curScope); 
    TAC::generator->GenStore(curr_loc, src);
}
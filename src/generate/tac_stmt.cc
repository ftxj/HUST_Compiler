#include "../ast/ast_stmt.h"
#include "../generate/tac_stmt.h"
#include "../ast/ast_decl.h"
#include "../ast/ast_expr.h"
#include "../symbol/Scope.h"
#include "../symbol/InternalType.h"
#include "../symbol/LocalScope.h"
#include "../symbol/FunctionSymbol.h"
#include "../tools/utility.h"
#include "../error/errors.h"
#include "../ast/ast_type.h"
#include "../semantic/semantic.h"

#include "../generate/codegen.h"
#include "../symbol/SymbolType.h"
void TACStmt::handle(Stmt* s, Scope*) {
}

void TACStmt::handle(Expr* s, Scope* curScope) {
    stdOutput(">???");
    s->Emit(curScope);
}

void TACStmt::handle(Program* p, Scope*) {
    Symbol* mainSym = Semantic::globleScope->getFncSymbol("main");
    if (mainSym == nullptr) {
        return; 
    }
    for (auto iter : *(p->decls)) {
        iter->Emit(Semantic::globleScope); 
    }
    generator->DoFinalCodeGen();
}

void TACStmt::handle(StmtBlock* stmt, Scope* cuScope){
    std::list<VarDecl*> *decls = stmt->decls;
	std::list<Stmt*> *stmts = stmt->stmts;
    for(auto iter : *decls) {
        iter->Emit(stmt->forTAC);
    }
    for(auto iter : *stmts) {
        iter->Emit(stmt->forTAC);
    }
}

void TACStmt::handle(ConditionalStmt* stmt_con, Scope*) {
}

void TACStmt::handle(LoopStmt* loop_stmt, Scope*) {
}

void TACStmt::handle(ForStmt* stmt_for, Scope* s) {
    stdOutput("for");
    Expr* init = stmt_for->init;
    Expr* test = stmt_for->test;
    Stmt* body = stmt_for->body;
    Expr* step = stmt_for->step;
    std::string condition_label = generator->NewLabel(); 
    std::string after_label = generator->NewLabel(); 
    stdOutput("for init");
    init->Emit(s); 
    generator->GenLabel(condition_label); 
    Location *condition = test->ReadValue(s);
    generator->GenIfZ(condition, after_label); 
    stdOutput("for body");
    body->Emit(body->forTAC); 
    stdOutput("for step");
    step->Emit(s); 
    generator->GenGoto(condition_label); 
    generator->GenLabel(after_label);
    stdOutput("for end");
}

void TACStmt::handle(WhileStmt* while_stmt, Scope* s) {
    Expr* test = while_stmt->test;
    Stmt* body = while_stmt->body;
    std::string condition_label = generator->NewLabel(); 
    std::string after_label = generator->NewLabel(); 
    generator->GenLabel(condition_label);
    Location *condition = test->ReadValue(s);
    generator->GenIfZ(condition, after_label); 
    body->Emit(body->forTAC);
    generator->GenGoto(condition_label); 
    generator->GenLabel(after_label); 
}

void TACStmt::handle(IfStmt* if_stmt, Scope* curScope) {
    Expr* test = if_stmt->test;
    Stmt* body = if_stmt->body;
    Stmt* elsebody = if_stmt->elseBody;
    Location *condition = test->ReadValue(curScope);
    std::string after_label = generator->NewLabel(); 
    std::string else_label = generator->NewLabel(); 
    if (elsebody != nullptr) {
        generator->GenIfZ(condition, else_label); 
        body->Emit(body->forTAC);
        generator->GenGoto(after_label); 
        generator->GenLabel(else_label);
        elsebody->Emit(elsebody->forTAC);
    }
    else { 
        generator->GenIfZ(condition, after_label); 
        body->Emit(body->forTAC); 
        generator->GenGoto(after_label);
    }
    generator->GenLabel(after_label); 
}

void TACStmt::handle(BreakStmt* t, Scope*) {

}

void TACStmt::handle(ReturnStmt* re_stmt, Scope* s) {
    Expr* expr = re_stmt->expr;
    if (expr != nullptr) {
        Location *toReturn = expr->ReadValue(s); 
        generator->GenReturn(toReturn); 
    }
    else
        generator->GenReturn();
}

void TACStmt::handle(PrintStmt* stmt_print, Scope* s) {
    FunctionSymbol* fnScope = s->getFncScope();
    std::list<Expr*>* args = stmt_print->args;
    for (auto e : *args) {
        ArrayAccess *a = dynamic_cast<ArrayAccess*>(e); 
        Location *l = e->ReadValue(s);
        Assert(l != nullptr);
        SymbolType* t = e->type;
        if (t->IsEquivalentTo(InternalType::intType)) {
            generator->GenBuiltInCall(PrintInt, l);
        }
        if (t->IsEquivalentTo(InternalType::boolType)) {
            generator->GenBuiltInCall(PrintBool, l); 
        }
        if (t->IsEquivalentTo(InternalType::stringType)) {
            generator->GenBuiltInCall(PrintString, l); 
        }
    }
}

#include <iostream>
#include <list>
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "../tools/utility.h"
#include "../semantic/semantic_stmt.h"

#include "../generate/codegen.h"
#include "../generate/tac.h"
#include "../generate/tac_stmt.h"

Program::Program(std::list<Decl*> *d) {
    Assert(d != NULL);
    for(auto iter : *d) {
        iter->SetParent(this);
    }
    decls = d;
}

void Program::Emit() {
    stdOutput("tac program");
    TACStmt::handle(this, nullptr);
}

void Program::PrintChildren(int indentLevel) {
    for (auto iter : *decls) {
        iter->PrintAST(indentLevel + 1);
    }
    std::cout << std::endl;
}

void Program::SemanticAnalysis() {
    SemanticStmt::handle(this);
}

void Stmt::SemanticAnalysis() {
    this->setSem();
    StmtBlock* d1 = dynamic_cast<StmtBlock*>(this);
    ConditionalStmt* d2 = dynamic_cast<ConditionalStmt*>(this);
    LoopStmt* d3 = dynamic_cast<LoopStmt*>(this);
    ForStmt* d4 = dynamic_cast<ForStmt*>(this);
    WhileStmt* d5 = dynamic_cast<WhileStmt*>(this);
    IfStmt* d6 = dynamic_cast<IfStmt*>(this);
    BreakStmt* d7 = dynamic_cast<BreakStmt*>(this);
    ReturnStmt* d8 = dynamic_cast<ReturnStmt*>(this);
    PrintStmt* d9 = dynamic_cast<PrintStmt*>(this);
    Expr* d10 = dynamic_cast<Expr*>(this);
    if(d1) SemanticStmt::handle(d1);
    else if(d4) SemanticStmt::handle(d4);
    else if(d5) SemanticStmt::handle(d5);
    else if(d6) SemanticStmt::handle(d6);
    else if(d7) SemanticStmt::handle(d7);
    else if(d8) SemanticStmt::handle(d8);
    else if(d9) SemanticStmt::handle(d9);
    else if(d10) SemanticStmt::handle(d10);
    else if(d2) SemanticStmt::handle(d2);
    else if(d3) SemanticStmt::handle(d3);
    else SemanticStmt::handle(this);
    is_sem = true;
}

Location* Stmt::Emit(Scope* curScope) {
    stdOutput("tac Stmt");
    TACStmt::handle(this, curScope);
    return nullptr;
}

StmtBlock::StmtBlock(std::list<VarDecl*> *d, std::list<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    for(auto iter : *d) {
        iter->SetParent(this);
    }
    decls=d;
    for(auto iter : *s) {
        iter->SetParent(this);
    }
    stmts = s;
}

Location* StmtBlock::Emit(Scope* curScope) {
    stdOutput("tac StmtBlock");
    TACStmt::handle(this, curScope);
    return nullptr;
}

void StmtBlock::PrintChildren(int indentLevel) {
    for(auto iter : *decls) {
        iter->PrintAST(indentLevel + 1);
    }
    for(auto iter : *stmts) {
        iter->PrintAST(indentLevel + 1);
    }
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

Location* ConditionalStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}

LoopStmt::LoopStmt(Expr *testExpr, Stmt *body) : ConditionalStmt(testExpr, body) {

}

Location* LoopStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}

WhileStmt::WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {

}

Location* WhileStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}

void WhileStmt::PrintChildren(int indentLevel) {
    test->PrintAST(indentLevel+1, "(test) ");
    body->PrintAST(indentLevel+1, "(body) ");
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

Location* ForStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}


void ForStmt::PrintChildren(int indentLevel) {
    init->PrintAST(indentLevel+1, "(init) ");
    test->PrintAST(indentLevel+1, "(test) ");
    step->PrintAST(indentLevel+1, "(step) ");
    body->PrintAST(indentLevel+1, "(body) ");
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

Location* IfStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}

void IfStmt::PrintChildren(int indentLevel) {
    test->PrintAST(indentLevel+1, "(test) ");
    body->PrintAST(indentLevel+1, "(then) ");
    if (elseBody) {
        elseBody->PrintAST(indentLevel+1, "(else) ");
    }
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}
Location* ReturnStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}
void ReturnStmt::PrintChildren(int indentLevel) {
    expr->PrintAST(indentLevel+1);
}

BreakStmt::BreakStmt(yyltype loc) : Stmt(loc) {

}
Location* BreakStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}
PrintStmt::PrintStmt(std::list<Expr*> *a) {    
    Assert(a != NULL);
    for(auto iter : *a) {
        iter->SetParent(this);
    }
    args = a;
}
Location* PrintStmt::Emit(Scope* curScope) {
    TACStmt::handle(this, curScope);
    return nullptr;
}
void PrintStmt::PrintChildren(int indentLevel) {
    for(auto iter : *args) {
        iter->PrintAST(indentLevel+1, "(args) ");
    }
}
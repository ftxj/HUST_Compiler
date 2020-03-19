#include "../ast/ast_stmt.h"
#include "../semantic/semantic_stmt.h"
#include "../ast/ast_decl.h"
#include "../ast/ast_expr.h"
#include "../symbol/Scope.h"
#include "../symbol/InternalType.h"
#include "../symbol/LocalScope.h"
#include "../symbol/FunctionSymbol.h"
#include "../tools/utility.h"
#include "../error/errors.h"
#include "../ast/ast_type.h"

void SemanticStmt::handle(Stmt* s) {
	Assert(1 == 2);
}

void SemanticStmt::handle(Expr* s) {
	stdOutput("decl expr begin");
	s->forTAC = top_scope;
	s->testAndReturnType();
	stdOutput("decl expr end");
}

void SemanticStmt::handle(Program* p) {
	/*
    *   1. set globle scope
    *   2. add all globle decl to scope
    *   3. for each decl, generate its table then check
    */
	stdOutput("Program SemanticStmt begin");
	std::list<Decl*>* all_decls = p->decls;
	top_scope = globleScope;
	top_scope->setParentScope(nullptr);
	for (auto iter : *all_decls) {
		Symbol* sm = iter->Generate();
		Symbol* conf = top_scope->addSymbol(sm); 
		if(conf != nullptr) {
			ReportError::DeclConflict(dynamic_cast<Decl*>(sm->getAstNode()), 
				dynamic_cast<Decl*>(conf->getAstNode()));
		}
	}
	for (auto iter : *all_decls) {
		if(!iter->getIsSematicFinished())
			iter->SemanticAnalysis();
	}
	stdOutput("Program SemanticStmt success");
	globleScope->PrintSymbolTable(nullptr, "Global");
}

void SemanticStmt::handle(StmtBlock* stmt_block){
	/*
    *  	stmt block : "{ decls; stmts; }"
    *   1. new a local scope
    *   2. scan all decls, add to scope
    *   3. scan stmt body, check each stmt
    *   4. local scope is nested with parent, add this scope to parent
    */
	std::list<VarDecl*>* delcs = stmt_block->decls;
	std::list<Stmt*>* stmts = stmt_block->stmts;
   	stdOutput("stmt block begin");
	LocalScope* local_scope = new LocalScope(top_scope);
	stmt_block->forTAC = local_scope;
	local_scope->setParentScope(top_scope);
	top_scope = local_scope;
	for(auto iter : *delcs) {
		stdOutput(iter->getName());
		Symbol* sm = iter->Generate();
		Symbol* conf = top_scope->addSymbol(sm);
		if (conf != nullptr) {
			ReportError::DeclConflict(dynamic_cast<Decl*>(conf->getAstNode()), 
				dynamic_cast<Decl*>(sm->getAstNode()));
		}
	}
	stdOutput("stmt block decls");
	for(auto iter : *delcs) {
		if(!iter->getIsSematicFinished())
			iter->SemanticAnalysis();
	}
	stdOutput("stmt block decls end");
	stdOutput("stmt block stmts");
	for(auto iter : *stmts) {
		iter->SemanticAnalysis();
    }
	stdOutput("stmt block stmts end");
	Scope* parent_scope = top_scope->getParentScope();
	parent_scope->addNested(local_scope);
	top_scope = parent_scope;
	stdOutput("stmt block end");
}

void SemanticStmt::handle(ConditionalStmt* stmt_con) {
	/*
	* ConditionalStmt: if(Expr) { Stmt; }
	*/
	stmt_con->forTAC = top_scope;
	stdOutput("condition begin");
	Expr* test = stmt_con->test;
	Stmt* body = stmt_con->body;
	pair<int, SymbolType*> exp_ = test->testAndReturnType();
	if(exp_.second != nullptr && !exp_.second->IsEquivalentTo(InternalType::boolType)) {
		ReportError::TestNotBoolean(test);
	}
	body->SemanticAnalysis();
	stdOutput("condition end");
}

void SemanticStmt::handle(LoopStmt* loop_stmt) {
	/*
	* LoopStmt: while(Expr) { Stmt; }
	*/
	loop_stmt->forTAC = top_scope;
	stdOutput("loop stmt begin");
	top_scope->setLoop(true);
	handle((ConditionalStmt*)(loop_stmt));
	stdOutput("loop stmt end");
}

void SemanticStmt::handle(ForStmt* stmt_for) {
    /*
	*	for(Expr* init; LoopStmt::Expr* test; Expr* step;) {LoopStmt::body }
    *   1. init may be assign or empty
    *   2. step may be assign or empty
    */
   	stdOutput("for stmt begin");
	stmt_for->forTAC = top_scope;
   	Expr* init = stmt_for->init;
	Expr* step = stmt_for->step;
	pair<int, SymbolType*> exp_init = init->testAndReturnType();
	if(exp_init.first != Expr::assisgnExpr && exp_init.first != Expr::emptyExpr) {
		ReportError::ForStmtInitMissFormat();
	}
	handle((LoopStmt*)(stmt_for));
    pair<int, SymbolType*> exp_step = step->testAndReturnType();
	if(exp_step.first != Expr::assisgnExpr && exp_step.first != Expr::emptyExpr) {
		ReportError::ForStmtStepMissFormat();
	}
	stdOutput("for stmt end");
}

void SemanticStmt::handle(WhileStmt* while_stmt) {
	while_stmt->forTAC = top_scope;
	stdOutput("while stmt begin");
	handle((LoopStmt*)(while_stmt));
	stdOutput("while stmt end");
}

void SemanticStmt::handle(IfStmt* if_stmt) {
	stdOutput("if stmt begin");
    /*test condition stmt and test else body*/
	if_stmt->forTAC = top_scope;
	Stmt* else_body = if_stmt->elseBody;
	handle((ConditionalStmt*)(if_stmt));
    if(else_body) else_body->SemanticAnalysis();
	stdOutput("if stmt end");
}

void SemanticStmt::handle(BreakStmt* t) { 
	 /* occur only in loop nested */
	t->forTAC = top_scope;
	stdOutput("break stmt begin");
    if(top_scope->getLoopedScope() == nullptr) {
		ReportError::BreakOutsideLoop(t);
    }
	stdOutput("break stmt end");
}

void SemanticStmt::handle(ReturnStmt* re_stmt) {
	/* just check if return type is correct, although "return" can only occur
    *  in function decl, but only function decl has stmt. IF return position error, parse fail  
    */
   	re_stmt->forTAC = top_scope;
   	stdOutput("return stmt begin");
	Expr* expr = re_stmt->expr;
	FunctionSymbol* fn_symbol = top_scope->getFncScope();
    if(fn_symbol == nullptr) {
		Assert(1 == 2);
    }
    else {
        /* first, check if expr has conflict */
		pair<int, SymbolType*> exp_return {Expr::emptyExpr, InternalType::voidType};
		if(expr) exp_return = expr->testAndReturnType();
        /* second, check if expr type is expected */
		SymbolType* given_type = exp_return.second;
		SymbolType* expected_type = fn_symbol->getReturnType();
		if(given_type != nullptr) {
			if(!expected_type->IsEquivalentTo(given_type)) {
				ReportError::ReturnMismatch(re_stmt, 
					new AstType(given_type->getName()), new AstType(expected_type->getName()));
			}
		}
		
    }
	stdOutput("return stmt end");
}

void SemanticStmt::handle(PrintStmt* stmt_print) {
	stmt_print->forTAC = top_scope;
	stdOutput("print stmt begin");
	std::list<Expr*> *args = stmt_print->args;
    for(auto iter : *args) {
		iter->testAndReturnType();
    }
	stdOutput("print stmt end");
}
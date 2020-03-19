#ifndef _H_ast_stmt__
#define _H_ast_stmt__
#include "ast.h"
#include <list>

class Decl;
class VarDecl;
class Expr;
class Scope;
class Location;

class Program : public Node {
	public:
		std::list<Decl*> *decls;
	public:
		Program(std::list<Decl*> *declList);
		void SemanticAnalysis();
		friend class SemanticStmt;
		friend class TACStmt;
		void Emit();
		std::string GetPrintNameForNode() { return "Program"; }
     	void PrintChildren(int indentLevel);
};

class Stmt : public Node {
	public:
		Stmt() : Node(), forTAC(nullptr) {}
		Stmt(yyltype loc) : Node(loc) , forTAC(nullptr) {}
		Scope* forTAC;
		void SemanticAnalysis();
		virtual Location* Emit(Scope* );
		friend class SemanticStmt;
		friend class TACStmt;
};

class StmtBlock : public Stmt {
	public:
		std::list<VarDecl*> *decls;
		std::list<Stmt*> *stmts;
	public:
		StmtBlock(std::list<VarDecl*> *variableDeclarations, std::list<Stmt*> *statements);
		friend class SemanticStmt;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "StmtBlock"; }
    	void PrintChildren(int indentLevel);
		friend class TACStmt;
};


class ConditionalStmt : public Stmt {
	public:
		Expr * test;
		Stmt *body;
	public:
		ConditionalStmt(Expr *testExpr, Stmt *body);
		bool type_check();
		Location* Emit(Scope* );
		friend class SemanticStmt;
		friend class TACStmt;
};

class LoopStmt : public ConditionalStmt {
	public:
		LoopStmt(Expr *testExpr, Stmt *body);
		Location* Emit(Scope* );
		friend class SemanticStmt;
		friend class TACStmt;
};

class ForStmt : public LoopStmt {
	public:
		Expr * init, *step;
	public:
		ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
		friend class SemanticStmt;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "ForStmt"; }
    	void PrintChildren(int indentLevel);
		friend class TACStmt;
};

class WhileStmt : public LoopStmt {
	public:
		WhileStmt(Expr *test, Stmt *body);
		friend class SemanticStmt;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "WhileStmt"; }
    	void PrintChildren(int indentLevel);
		friend class TACStmt;
};

class IfStmt : public ConditionalStmt {
	public:
		Stmt * elseBody;
	public:
		IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
		friend class SemanticStmt;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "IfStmt"; }
    	void PrintChildren(int indentLevel);
		friend class TACStmt;
};

class BreakStmt : public Stmt {
	public:
		BreakStmt(yyltype loc);
		friend class SemanticStmt;
		Location* Emit(Scope* );
    	std::string GetPrintNameForNode() { return "BreakStmt"; }
		friend class TACStmt;
};

class ReturnStmt : public Stmt {
	public:
		Expr * expr;
	public:
		ReturnStmt(yyltype loc, Expr *expr);
		friend class SemanticStmt;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "ReturnStmt"; }
    	void PrintChildren(int indentLevel);
		friend class TACStmt;
};

class PrintStmt : public Stmt {
	public:
		std::list<Expr*> *args;
	public:
		PrintStmt(std::list<Expr*> *arguments);
		friend class SemanticStmt;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "PrintStmt"; }
    	void PrintChildren(int indentLevel);
		friend class TACStmt;
};

#endif
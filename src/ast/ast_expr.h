#ifndef _H_ast_expr
#define _H_ast_expr

#include "../ast/ast.h"
#include "../ast/ast_stmt.h"

#include <list>

class AstNamedType; // for new
class AstType; // for NewArray
class SymbolType;

class Location;
class Scope;

class Expr : public Stmt {
	public:
		static int 
			assisgnExpr, emptyExpr, intConstant, doubleConstant, boolConstant,
			stringConstant, nullConstant, arithmeticExpr, relationalExpr, logicalExpr;
	public:
		Expr(yyltype loc);
		Expr();
		SymbolType* type;
		pair<int, SymbolType*> testAndReturnType();
		virtual Location* Emit(Scope* );
		virtual void StoreValue(Scope* , Location* src);
		virtual Location* ReadValue(Scope*);
		friend class SemanticExpr;
		friend class SemanticStmt;
};

class EmptyExpr : public Expr {
	public:
		friend class SemanticExpr;
		Location* Emit(Scope* );
		
		std::string GetPrintNameForNode() { return "Empty"; }
};

class IntConstant : public Expr {
	public:
		int value;
	public:
		IntConstant(yyltype loc, int val);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "IntConstant"; }
    	void PrintChildren(int indentLevel);
};

class DoubleConstant : public Expr {
	public:
		double value;
	public:
		DoubleConstant(yyltype loc, double val);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "DoubleConstant"; }
    	void PrintChildren(int indentLevel);
};

class BoolConstant : public Expr {
	public:
		bool value;
	public:
		BoolConstant(yyltype loc, bool val);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "BoolConstant"; }
    	void PrintChildren(int indentLevel);
};

class StringConstant : public Expr {
	public:
		std::string value;
	public:
		StringConstant(yyltype loc, std::string val);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "StringConstant"; }
    	void PrintChildren(int indentLevel);
};

class NullConstant : public Expr {
	public:
		NullConstant(yyltype loc);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "NullConstant"; }
};

class Operator : public Node {
	public:
		char tokenString[4];

	public:
		Operator(yyltype loc, const char *tok);
		friend ostream& operator<<(ostream& out, Operator *o) { return out << o->tokenString; }
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "Operator"; }
    	void PrintChildren(int indentLevel);
};

class CompoundExpr : public Expr {
	public:
		Operator * op;
		Expr *left, *right; // left will be NULL if unary

	public:
		CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
		CompoundExpr(Operator *op, Expr *rhs);             // for unary
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		bool isUnaryOp();
		void PrintChildren(int indentLevel);
};

class ArithmeticExpr : public CompoundExpr {
	public:
		ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs);
		ArithmeticExpr(Operator *op, Expr *rhs);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "ArithmeticExpr"; }
};

class RelationalExpr : public CompoundExpr {
	public:
		RelationalExpr(Expr *lhs, Operator *op, Expr *rhs);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "RelationalExpr"; }
};

class EqualityExpr : public CompoundExpr {
	public:
		EqualityExpr(Expr *lhs, Operator *op, Expr *rhs);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "EqualityExpr"; }		
};

class LogicalExpr : public CompoundExpr {
	public:
		LogicalExpr(Expr *lhs, Operator *op, Expr *rhs);
		LogicalExpr(Operator *op, Expr *rhs);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "LogicalExpr"; }
};

class AssignExpr : public CompoundExpr {
	public:
		AssignExpr(Expr *lhs, Operator *op, Expr *rhs);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "AssignExpr"; }
};

class LValue : public Expr {
	public:
		LValue(yyltype loc);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
};

class This : public Expr {
	public:
		This(yyltype loc);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "This"; }
};

class ArrayAccess : public LValue {
	public:
		Expr * base, *subscript;
	public:
		ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		void StoreValue(Scope* , Location* src);
		Location* ReadValue(Scope*);
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "ArrayAccess"; }
    	void PrintChildren(int indentLevel);
};

class FieldAccess : public LValue {
	public:
		Expr * base;	// will be NULL if no explicit base
		Identifier *field;
	public:
		FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
		friend class SemanticExpr;
		friend class TACExpr;

		Location* Emit(Scope* );
		void StoreValue(Scope* , Location* src);
		Location* ReadValue(Scope*);
		
		std::string GetPrintNameForNode() { return "FieldAccess"; }
    	void PrintChildren(int indentLevel);
};

class Call : public Expr {
	public:
		Expr * base;	// will be NULL if no explicit base
		Identifier *field;
		std::list<Expr*> *actuals;
	public:
		Location* Emit(Scope* );
		Call(yyltype loc, Expr *base, Identifier *field, std::list<Expr*> *args);
		friend class SemanticExpr;
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "Call"; }
    	void PrintChildren(int indentLevel);
};

class NewExpr : public Expr {
	public:
		AstNamedType * cType;
	public:
		NewExpr(yyltype loc, AstNamedType *clsType);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "NewExpr"; }
    	void PrintChildren(int indentLevel);
};

class NewArrayExpr : public Expr {
	public:
		Expr * size;
		AstType *elemType;
	public:
		NewArrayExpr(yyltype loc, Expr *sizeExpr, AstType *elemType);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "NewArrayExpr"; }
    	void PrintChildren(int indentLevel);
};

class ReadIntegerExpr : public Expr {
	public:
		ReadIntegerExpr(yyltype loc);
		friend class SemanticExpr;
		Location* Emit(Scope* );
		friend class TACExpr;
		std::string GetPrintNameForNode() { return "ReadIntegerExpr"; }
};

class ReadLineExpr : public Expr {
	public:
		ReadLineExpr(yyltype loc);
		friend class SemanticExpr;
		friend class TACExpr;
		Location* Emit(Scope* );
		std::string GetPrintNameForNode() { return "ReadLineExpr"; }
};

#endif
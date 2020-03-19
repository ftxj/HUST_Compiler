#ifndef _H_ast_decl__
#define _H_ast_decl__
#include <iostream>
#include <list>
#include <string>
#include "../ast/ast.h"
#include "../generate/codegen.h"

class AstType;
class AstNamedType;
class Stmt;

class Scope;
class Symbol;


extern int out_put_level;
extern void out_put_tabs();

class Decl : public Node {
	protected:
		Identifier * id;
	public:
		Decl(Identifier *name);
		std::string getName();
		friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id; }
		virtual Symbol* Generate();
		virtual Location* Emit(Scope*);
		void SemanticAnalysis();
		int getOffset();
		friend class SemanticDecl;
		friend class Generate;
		friend class TACDecl;
};

class VarDecl : public Decl {
	protected:
		AstType * type;
	public:
		VarDecl(Identifier *name, AstType *type);
		Symbol* Generate();
		void SemanticAnalysis();
		friend class SemanticDecl;
		Location* Emit(Scope*);
		std::string GetPrintNameForNode() { return "VarDecl"; }
   		void PrintChildren(int indentLevel);
		friend class TACDecl;
};

class ClassDecl : public Decl {
	protected:
		std::list<Decl*> *members;
		AstNamedType *extends;
		std::list<AstNamedType*> *implements;

	public:
		ClassDecl(Identifier *name, AstNamedType *extends,
			std::list<AstNamedType*> *implements, std::list<Decl*> *members);
		Symbol* Generate();
		void SemanticAnalysis();
		friend class SemanticDecl;
		Location* Emit(Scope*);
		std::string GetPrintNameForNode() { return "ClassDecl"; }
    	void PrintChildren(int indentLevel);
		friend class TACDecl;
};

class InterfaceDecl : public Decl {
	protected:
		std::list<Decl*> *members;

	public:
		InterfaceDecl(Identifier *name, std::list<Decl*> *members);
		Symbol* Generate();
		void SemanticAnalysis();
		friend class SemanticDecl;
		Location* Emit(Scope*);
		std::string GetPrintNameForNode() { return "InterfaceDecl"; }
    	void PrintChildren(int indentLevel);
		friend class TACDecl;
};

class FnDecl : public Decl {
	protected:
		std::list<VarDecl*> *formals;
		AstType *returnType;
		Stmt *body;
	public:
		FnDecl(Identifier *name, AstType *returnType, std::list<VarDecl*> *formals);
		void SetFunctionBody(Stmt *b);
		Symbol* Generate();
		void SemanticAnalysis();
		Location* Emit(Scope*);
		friend class SemanticDecl;
		friend class TACDecl;
		std::string GetPrintNameForNode() { return "FnDecl"; }
    	void PrintChildren(int indentLevel);
};
#endif
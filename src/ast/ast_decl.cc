
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "../symbol/Generate.h"
#include "../semantic/semantic_decl.h"
#include "../tools/utility.h"

#include "../generate/tac.h"
#include "../generate/codegen.h"
#include "../generate/tac_decl.h"

Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
	Assert(n != NULL);
	(id = n)->SetParent(this);
}

std::string	Decl::getName() {
	return id->getName();
}

Location* Decl::Emit(Scope* curScope) {
	stdOutput("tac Decl");
	Assert(1 == 2);
	TACDecl::handle(this, curScope);
	return nullptr;
}

Symbol* Decl::Generate() {
	return Generate::geneSymbol(this);
}

void Decl::SemanticAnalysis() {
	this->setSem();
	FnDecl* d1 = dynamic_cast<FnDecl*>(this);
	VarDecl* d2 = dynamic_cast<VarDecl*>(this);
	InterfaceDecl* d3 = dynamic_cast<InterfaceDecl*>(this);
	ClassDecl* d4 = dynamic_cast<ClassDecl*>(this);
	if(d1) return SemanticDecl::handle(d1);
	if(d2) return SemanticDecl::handle(d2);
	if(d3) return SemanticDecl::handle(d3);
	if(d4) return SemanticDecl::handle(d4);
	return SemanticDecl::handle(this);
}

VarDecl::VarDecl(Identifier *n, AstType *t) : Decl(n) {
	Assert(n != NULL && t != NULL);
	(type = t)->SetParent(this);
}

void VarDecl::PrintChildren(int indentLevel) { 
   type->PrintAST(indentLevel+1);
   id->PrintAST(indentLevel+1);
}

Location* VarDecl::Emit(Scope* curScope) {
	stdOutput("tac VarDecl");
	TACDecl::handle(this, curScope);
	return nullptr;
}


Symbol* VarDecl::Generate() {
	return Generate::geneSymbol(this);
}

void VarDecl::SemanticAnalysis() {
	return SemanticDecl::handle(this);
}

ClassDecl::ClassDecl(Identifier *n, AstNamedType *ex, std::list<AstNamedType*> *imp, std::list<Decl*> *m) : Decl(n) {
	// extends can be NULL, impl & mem may be empty std::lists but cannot be NULL
	Assert(n != NULL && imp != NULL && m != NULL);
	extends = ex;
	if (extends) extends->SetParent(this);
	for(auto iter : *imp) {
		iter->SetParent(this);
	}
	implements = imp;
	for(auto iter : *m) {
		iter->SetParent(this);
	}
	members = m;
}

Location* ClassDecl::Emit(Scope* curScope) {
	stdOutput("tac ClassDecl");
	TACDecl::handle(this, curScope);
	return nullptr;
}


Symbol* ClassDecl::Generate() {
	return Generate::geneSymbol(this);
}

void ClassDecl::SemanticAnalysis() {
	return SemanticDecl::handle(this);
}

void ClassDecl::PrintChildren(int indentLevel) {
    id->PrintAST(indentLevel+1);
    if (extends) extends->PrintAST(indentLevel+1, "(extends) ");
	for(auto iter : *implements) {
    	iter->PrintAST(indentLevel+1, "(implements) ");
	}
	for(auto iter : *members) {
    	iter->PrintAST(indentLevel+1);
	}
}

InterfaceDecl::InterfaceDecl(Identifier *n, std::list<Decl*> *m) : Decl(n) {
	Assert(n != NULL && m != NULL);
	for(auto iter : *m) {
		iter->SetParent(this);
	}
	members = m;
}

Symbol* InterfaceDecl::Generate() {
	return Generate::geneSymbol(this);
}

Location* InterfaceDecl::Emit(Scope* curScope) {
	stdOutput("tac InterfaceDecl");
	Assert(1 == 2);
	TACDecl::handle(this, curScope);
	return nullptr;
}

void InterfaceDecl::SemanticAnalysis() {
	return SemanticDecl::handle(this);
}

void InterfaceDecl::PrintChildren(int indentLevel) {
    id->PrintAST(indentLevel+1);
	for(auto iter : *members) {
		iter->PrintAST(indentLevel + 1);
	}
}

FnDecl::FnDecl(Identifier *n, AstType *r, std::list<VarDecl*> *d) : Decl(n) {
	Assert(n != NULL && r != NULL && d != NULL);
	(returnType = r)->SetParent(this);
	for(auto iter : *d) {
		iter->SetParent(this);
	}
	formals = d;
	body = NULL;
}

Location* FnDecl::Emit(Scope* curScope) {
	stdOutput("tac FnDecl");
	TACDecl::handle(this, curScope);
	return nullptr;
}

Symbol* FnDecl::Generate() {
	return Generate::geneSymbol(this);
}

void FnDecl::SetFunctionBody(Stmt *b) {
	(body = b)->SetParent(this);
}

void FnDecl::SemanticAnalysis() {
	return SemanticDecl::handle(this);
}

void FnDecl::PrintChildren(int indentLevel) {
    returnType->PrintAST(indentLevel + 1, "(return type) ");
    id->PrintAST(indentLevel+1);
	for(auto iter : *formals) {
		iter->PrintAST(indentLevel + 1, "(formals) ");
	}
    if (body) body->PrintAST(indentLevel+1, "(body) ");
}

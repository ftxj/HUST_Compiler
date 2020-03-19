#include "../semantic/semantic_decl.h"
#include "../semantic/semantic.h"

#include "../symbol/Symbol.h"
#include "../symbol/ClassSymbol.h"
#include "../symbol/VariableSymbol.h"
#include "../symbol/InterfaceSymbol.h"

#include "../tools/utility.h"
#include "../error/errors.h"
#include "../ast/ast_decl.h"
#include "../ast/ast_type.h"
#include "../ast/ast_stmt.h"
#include <map>

void SemanticDecl::handle(Decl* decl){
	Assert(1 == 2);
}

void SemanticDecl::handle(VarDecl* decl){
	stdOutput("VarDecl begin");
	decl->setSem();
	Assert(decl != nullptr);
	Symbol* sym = top_scope->getSymbol(decl->getName(), true);
	if(sym->Symbol::getAstNode() != decl) return;
	AstType* nodeType = decl->type;
	SymbolType* type = nullptr;
	if(nodeType) type = nodeType->Generate();	
	VariableSymbol* symbol = dynamic_cast<VariableSymbol*>(sym);
	if(type == nullptr) {
		AstNamedType* className = dynamic_cast<AstNamedType*>(decl->type);
		AstArrayType* aName =  dynamic_cast<AstArrayType*>(decl->type);
		if(aName != nullptr) {
			className = dynamic_cast<AstNamedType*>(aName->elemType);
		}
		ReportError::IdentifierNotDeclared(className->id, reasonT::LookingForClass);
	}
	symbol->setType(type);
	stdOutput("VarDecl begin set type: " + symbol->getName());
	stdOutput("VarDecl end");
}

void SemanticDecl::handle(ClassDecl* decl){
	/*
	*   1. get symbol table of this from parent scope
	*   2. link all inherit (extends, interfaces) symbol table
	*   3. generate a new scope and set it be the top
	*   4. scan the class body, insert all symbol to this scope (also to SymbolTable)
	*   5. scan the class body, set and check for chindrens
	*   6. check if all interface be imply
	*/
	/* get this class symbol table */
	decl->setSem();
	stdOutput("check class begin");
	std::list<Decl*> *members = decl->members;
	AstNamedType *extends = decl->extends;
	std::list<AstNamedType*> *implements = decl->implements;
	std::map<std::string, AstNamedType*> nameToNode;
	
	ClassSymbol* thisScope = dynamic_cast<ClassSymbol*>(top_scope->getSymbol(decl->getName(), true));
	if(thisScope->Symbol::getAstNode() != decl) return;
	thisScope->setParentScope(top_scope);
	Assert(thisScope != nullptr);
	/* link the extends symbol table */
	string extendsName;
	ClassSymbol* superScope = nullptr;
	if (extends != nullptr && !(extendsName = extends->getName()).empty()) {
		/* need extends class */
		if ((superScope = top_scope->getClassSymbol(extendsName)) == nullptr) {
			/* the class identifier isn't exists, this id don't exist or id is function/interface/var */
			ReportError::IdentifierNotDeclared(extends->id, reasonT::LookingForClass);
		}
		else if (superScope == thisScope) {
			/* self inherit */
			ReportError::InheritSelf();
		}
		else {
			int fnNum = superScope->getFunNum();
			thisScope->setSuperFnNum(fnNum);
			// extends is a class name, is_generated should look up globle_scope(no nested inherit)
			/* make sure the extends class symbol table generated */
			ClassDecl* astNode = dynamic_cast<ClassDecl*>(superScope->Symbol::getAstNode());
			Assert(astNode != nullptr);
			if (!(astNode->getIsSematicFinished())) {
				astNode->SemanticAnalysis();
			}
			thisScope->setSuperClass(extendsName, superScope);
		}
	}
	/* link the interface symbol table */
	InterfaceSymbol* interface_symbol = nullptr;
	for(auto iter : *implements) {
		/* iter each interface */
		std::string interface_name = iter->getName();
		nameToNode[interface_name] = iter;
		if ((interface_symbol = top_scope->getInterfaceSymbol(interface_name)) == nullptr) {
			/* id isn't exist or isn't a interface */
			ReportError::IdentifierNotDeclared(iter->id, reasonT::LookingForInterface);
		}
		else {
			/* generate interface symbol table first */
			Node* ast_node = interface_symbol->Symbol::getAstNode();
			if (!(ast_node->getIsSematicFinished())) {
				dynamic_cast<InterfaceDecl*>(ast_node)->SemanticAnalysis();
			}
			InterfaceSymbol* conflict_interface = nullptr;
			if ((conflict_interface = thisScope->addInterfaces(interface_name, interface_symbol)) != nullptr) {
				/* can't inherit two interface which have same function */
				ReportError::InterfaceConflict(decl, dynamic_cast<Decl*>(interface_symbol->Symbol::getAstNode()), 
					dynamic_cast<Decl*>(conflict_interface->Symbol::getAstNode()));
			}
		}
	}
	/* scan the class body */
	Symbol* member_symbol = nullptr;
	for (auto iter : *members) {
		/* insert all id to this scope */
		member_symbol = iter->Generate();
		std::cout << member_symbol << " " << iter->getName() << std::endl;
		Symbol* confe = nullptr;
		if ((confe = thisScope->addSymbol(member_symbol)) != nullptr) {
			ReportError::DeclConflict(dynamic_cast<Decl*>(confe->getAstNode()), 
				dynamic_cast<Decl*>(member_symbol->getAstNode()));
		}
	}
	/* change top scope */
	thisScope->setParentScope(top_scope);
	top_scope = thisScope;
	/* generate all member's SymbolTable in this scope */
	for (auto iter : *members) {
		Symbol* in = thisScope->getSymbol(iter->getName(), false);
		if(in->getAstNode() != iter) continue;
		if (!(iter->getIsSematicFinished())) {
			iter->SemanticAnalysis();
		}
	}
	/* check if all interface function imply */
	std::map<std::string, InterfaceSymbol*>* infList = thisScope->getAllInterfaces();
	for (auto iter : *infList) {
		std::list<FunctionSymbol*>* fnList = iter.second->getAllMethods();
		for(auto fnIter : *fnList) {
			/*each function need imply */
			FunctionSymbol* tt;
			if ((tt = thisScope->getMemberFunction(fnIter)) == nullptr) {
				ReportError::InterfaceNotImplemented(decl, nameToNode[iter.first]);
			}
			else if(!tt->IsEquivalentTo(fnIter)) {
				ReportError::OverrideMismatch(dynamic_cast<Decl*>(tt->Symbol::getAstNode()));
			}
		}
	}
	top_scope = top_scope->getParentScope();
	stdOutput("check class end");
}

void SemanticDecl::handle(InterfaceDecl* decl){
	/*
	*   1. get interface symbol
	*   2. scan body, set all virtual function in this scope (don't need continue generate)
	*/
	decl->setSem();
	stdOutput("interface begin");
	std::list<Decl*> *members = decl->members;
	InterfaceSymbol* symbol = top_scope->getInterfaceSymbol(decl->getName());
	if(symbol->Symbol::getAstNode() != decl) return;
	symbol->setParentScope(top_scope);
	top_scope = symbol;
	for(auto iter : *members) {
		Symbol* fnc = iter->Generate();
		Symbol* conf =  top_scope->addSymbol(fnc);
		if (conf != nullptr) {
			ReportError::DeclConflict(dynamic_cast<Decl*>(fnc->Symbol::getAstNode()), 
				dynamic_cast<Decl*>(conf->getAstNode()));
		}
		else {
			iter->SemanticAnalysis();
		}
	}
	top_scope = top_scope->getParentScope();
	stdOutput("interface end");
}

void SemanticDecl::handle(FnDecl* decl){
	/*
	*   1. get symbol table of this from parent scope
	*   2. generate a new scope and set it be the top
	*   3. scan parameter, set it in scope
	*   4. scan body, for each stmt block, set a symbol table and a scope link to parent
	*/
	decl->setSem();
	stdOutput("check function begin");
	/* change top scope */
	FunctionSymbol* thisScope = top_scope->getFncSymbol(decl->getName());
	if(thisScope->Symbol::getAstNode() != decl) return;
	thisScope->setParentScope(top_scope);
	top_scope = thisScope;

	AstType* reAstType = decl->returnType;
	std::list<VarDecl*> *formals = decl->formals;
	Stmt *body = decl->body;
	/*scan return type*/
	SymbolType *returnType = nullptr;
	if(reAstType != nullptr) returnType = reAstType->Generate();
	thisScope->setReturnType(returnType);
	/* scan parameters */
	stdOutput("scan parameter");
	for (auto paraDecl : *formals) {
		Symbol* sym = paraDecl->Generate();
		Symbol* conf = top_scope->addSymbol(sym);
		paraDecl->SemanticAnalysis();
		thisScope->addArgType(sym->getType());
		if (conf != nullptr) {
			ReportError::DeclConflict(dynamic_cast<Decl*>(conf->getAstNode()), 
				dynamic_cast<Decl*>(sym->getAstNode()));
		}
	}
	stdOutput("scan parameter end");
	/* scan the fun stmt */
	stdOutput("scan body");
	if(body != nullptr) body->SemanticAnalysis();
	stdOutput("scan body end");
	top_scope = top_scope->getParentScope();
	stdOutput("check function end");
}
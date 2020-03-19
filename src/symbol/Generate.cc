#include "../symbol/Generate.h"
#include "../symbol/Symbol.h"
#include "../symbol/Generate.h"
#include "../symbol/VariableSymbol.h"
#include "../symbol/InterfaceSymbol.h"
#include "../symbol/FunctionSymbol.h"
#include "../symbol/InternalType.h"
#include "../symbol/SymbolType.h"
#include "../ast/ast_decl.h"
#include "../ast/ast_type.h"
#include "../symbol/ArrayType.h"
#include "../symbol/ClassSymbol.h"
#include "../tools/utility.h"
#include "../ast/ast.h"
#include "../semantic/semantic.h"

Symbol* Generate::geneSymbol(Decl* decl) {
    Assert(1 == 2);
	return nullptr;
}

Symbol* Generate::geneSymbol(VarDecl* decl) {
    stdOutput("Generate VarDecl");
	VariableSymbol* symbol = new VariableSymbol(decl->getName());
	symbol->Symbol::setASTNode(decl);
    stdOutput("Generate VarDecl end");
	return symbol;
}
		
Symbol* Generate::geneSymbol(ClassDecl* decl) {
    stdOutput("Generate ClassDecl");
	ClassSymbol* symbol = new ClassSymbol(std::string(decl->getName()));
	symbol->Symbol::setASTNode(decl);
    symbol->SymbolType::setAstNode(new AstNamedType(decl->id));
    stdOutput("Generate ClassDecl end");
	return symbol;
}
		
Symbol* Generate::geneSymbol(InterfaceDecl* decl) {
    stdOutput("Generate InterfaceDecl");
    InterfaceSymbol* symbol = new InterfaceSymbol(decl->getName());
    symbol->Symbol::setASTNode(decl);
    symbol->SymbolType::setAstNode(new AstNamedType(decl->id));
    stdOutput("Generate InterfaceDecl end");
    return symbol;
}

Symbol* Generate::geneSymbol(FnDecl* decl) {
    stdOutput("Generate FnDecl");
    FunctionSymbol* symbol = new FunctionSymbol(std::string(decl->getName()));
    symbol->Symbol::setASTNode(decl);
    symbol->SymbolType::setAstNode(new AstType("function: " + decl->getName()));
    stdOutput("Generate FnDecl end");
    return symbol;
}

SymbolType* Generate::geneType(AstArrayType* type) {
    stdOutput("Generate AstArrayType");
    AstType* elemType = type->elemType;
    SymbolType* tt = elemType->Generate();
    ArrayType* res = nullptr;
    if(tt != nullptr)
        res = new ArrayType(tt, elemType);
    stdOutput("Generate AstArrayType end");
    return res;
}

SymbolType* Generate::geneType(AstNamedType* type) {
    SymbolType* res = nullptr;
    std::string cname = type->getName();
    ClassSymbol* csymbol = dynamic_cast<ClassSymbol*>(Semantic::top_scope->getSymbol(cname, true));
    InterfaceSymbol* insym = dynamic_cast<InterfaceSymbol*>(Semantic::top_scope->getSymbol(cname, true));
    if(csymbol != nullptr && !csymbol->Symbol::getAstNode()->getIsSematicFinished()) {
        ClassDecl* cc = dynamic_cast<ClassDecl*>(csymbol->Symbol::getAstNode());
        Assert(cc != nullptr);
        cc->SemanticAnalysis();
    } else if(insym != nullptr  && !insym->Symbol::getAstNode()->getIsSematicFinished()){
        InterfaceDecl* cc = dynamic_cast<InterfaceDecl*>(insym->Symbol::getAstNode());
        Assert(cc != nullptr);
        cc->SemanticAnalysis();
    }
    if(csymbol != nullptr) res = csymbol;
    if(insym != nullptr) res = insym;
    return res;
}

SymbolType* Generate::geneType(AstType* type) {
    stdOutput("Generate AstType");
    if(type->IsEquivalentTo(AstType::intType)) {
        stdOutput("Generate AstType int end");
        SymbolType* res = new SymbolType("int", type);
        Assert(res->getAstNode() != nullptr);
        Assert(type != nullptr);
        return res;
    }
    if(type->IsEquivalentTo(AstType::boolType)) {
        stdOutput("Generate AstType end");
        return InternalType::boolType;
    }
    if(type->IsEquivalentTo(AstType::doubleType)) {
        stdOutput("Generate AstType double end");
        SymbolType* res = new SymbolType("double", type);
        Assert(res->getAstNode() != nullptr);
        Assert(type != nullptr);
        return res;
    }
    if(type->IsEquivalentTo(AstType::voidType)) {
        stdOutput("Generate AstType end");
        return InternalType::voidType;
    }
    if(type->IsEquivalentTo(AstType::nullType)) {
        stdOutput("Generate AstType end");
        return InternalType::nullType;
    }
    if(type->IsEquivalentTo(AstType::stringType)) {
        stdOutput("Generate AstType end");
        return InternalType::stringType;
    }
    if(type->IsEquivalentTo(AstType::errorType)) {
        stdOutput("Generate AstType end");
        return InternalType::errorType;
    }
    stdOutput("Generate AstType ??? end");
    return nullptr;
}
#include "../semantic/semantic_type.h"
#include "../symbol/SymbolType.h"
#include "../ast/ast_type.h"
#include "../symbol/InternalType.h"
#include "../symbol/Symbol.h"
#include "../symbol/ClassSymbol.h"
#include "../symbol/ArrayType.h"

SymbolType* SemanticType::handle(AstType* ast){
	SymbolType* n = ast->Generate();
	if(n->IsEquivalentTo(InternalType::intType)) {
		return InternalType::intType;
	}
	if(n->IsEquivalentTo(InternalType::boolType)) {
		return InternalType::boolType;
	}
	if(n->IsEquivalentTo(InternalType::doubleType)) {
		return InternalType::doubleType;
	}
	if(n->IsEquivalentTo(InternalType::voidType)) {
		return InternalType::voidType;
	}
	if(n->IsEquivalentTo(InternalType::nullType)) {
		return InternalType::nullType;
	}
	if(n->IsEquivalentTo(InternalType::stringType)) {
		return InternalType::stringType;
	}
	if(n->IsEquivalentTo(InternalType::errorType)) {
		return InternalType::errorType;
	}
	return nullptr;
}

SymbolType* SemanticType::handle(AstNamedType* ast){
	std::string name = ast->id->getName();
	ClassSymbol* res = top_scope->getClassSymbol(name);
	return res;
}

SymbolType* SemanticType::handle(AstArrayType* ast){
	AstType* ast_base = ast->elemType;
	SymbolType* sem_base = ast_base->Generate();
	ArrayType* type = new ArrayType(sem_base);
	return type;
}
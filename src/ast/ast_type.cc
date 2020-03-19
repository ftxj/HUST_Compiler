#include <string.h>
#include <iostream>
#include <string>
#include "ast_type.h"
#include "ast_decl.h"
#include "../tools/utility.h"
#include "../symbol/Generate.h"
AstType *AstType::intType    = new AstType("int");
AstType *AstType::doubleType = new AstType("double");
AstType *AstType::voidType   = new AstType("void");
AstType *AstType::boolType   = new AstType("bool");
AstType *AstType::nullType   = new AstType("null");
AstType *AstType::stringType = new AstType("string");
AstType *AstType::errorType  = new AstType("error"); 

AstType::AstType(std::string n) {
    Assert(!n.empty());
    typeName = n;
}

AstType::AstType(yyltype loc) : Node(loc) {

}

bool AstType::IsEquivalentTo(AstType *other) {
	Assert(this != nullptr);
	Assert(!typeName.empty());
	if(other == nullptr || other->typeName.empty()) return false;
	return this->typeName == other->typeName;
}

void AstType::PrintToStream(ostream& out) {
	out << typeName;
}

void AstType::PrintChildren(int indentLevel) {
    std::cout << typeName;
}

std::string AstType::getName() {
	return typeName;
}

SymbolType* AstType::Generate() {
	this->setSem();
	AstArrayType* d1 = dynamic_cast<AstArrayType*>(this);
	AstType* d2 = dynamic_cast<AstType*>(this);
	AstNamedType* d3 = dynamic_cast<AstNamedType*>(this);
	if(d1) return Generate::geneType(d1);
	if(d3) return Generate::geneType(d3);
	return Generate::geneType(d2);
}

AstNamedType::AstNamedType(Identifier *i) : AstType(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
}

std::string AstNamedType::getName() {
	return id->getName();
}

void AstNamedType::PrintToStream(ostream& out) {
	out << id;
}

void AstNamedType::PrintChildren(int indentLevel) {
    id->PrintAST(indentLevel+1);
}

bool AstNamedType::IsEquivalentTo(AstType *other) {
	Assert(this != nullptr);
	Assert(id != nullptr);
	if(other == nullptr || !other->getName().empty()) return false;
	return id->getName() == other->getName();
}

AstArrayType::AstArrayType(yyltype loc, AstType *et) : AstType(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}

std::string AstArrayType::getName() {
	return elemType->getName();
}

bool AstArrayType::IsEquivalentTo(AstType *other) {
	AstArrayType* oo = dynamic_cast<AstArrayType*>(other);
	if(oo == nullptr) {
		return false;
	}
	return elemType->IsEquivalentTo(oo->elemType);
}

void AstArrayType::PrintChildren(int indentLevel) {
    elemType->PrintAST(indentLevel+1);
}

void AstArrayType::PrintToStream(ostream& out) {
	out << elemType << "[]";
}
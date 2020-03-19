#include <string.h>
#include <iostream>
#include <utility>
#include "../ast/ast_expr.h"
#include "../ast/ast_type.h"
#include "../ast/ast_decl.h"
#include "../semantic/semantic_expr.h"
#include "../tools/utility.h"

#include "../symbol/Scope.h"
#include "../generate/codegen.h"
#include "../generate/tac.h"
#include "../generate/tac_expr.h"

#include "../generate/rw.h"
class SymbolType;

int Expr::assisgnExpr = 1;
int Expr::emptyExpr = 2;
int Expr::intConstant = 3;
int Expr::doubleConstant = 4;
int Expr::boolConstant = 5;
int Expr::stringConstant = 6;
int Expr::nullConstant = 7;
int Expr::arithmeticExpr = 8;
int Expr::relationalExpr = 9;
int Expr::logicalExpr = 10;

Location* EmptyExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}

pair<int, SymbolType*> Expr::testAndReturnType() {
	this->setSem();
	EmptyExpr* d2 = dynamic_cast<EmptyExpr*>(this);
	IntConstant* d3 = dynamic_cast<IntConstant*>(this);
	DoubleConstant* d4 = dynamic_cast<DoubleConstant*>(this);
	BoolConstant* d5 = dynamic_cast<BoolConstant*>(this);
	StringConstant* d6 = dynamic_cast<StringConstant*>(this);
	NullConstant* d7 = dynamic_cast<NullConstant*>(this);
	ArithmeticExpr* d10 = dynamic_cast<ArithmeticExpr*>(this);
	RelationalExpr* d11 = dynamic_cast<RelationalExpr*>(this);
	EqualityExpr* d12 = dynamic_cast<EqualityExpr*>(this);
	LogicalExpr* d13 = dynamic_cast<LogicalExpr*>(this);
	AssignExpr* d14 = dynamic_cast<AssignExpr*>(this);
	This* d16 = dynamic_cast<This*>(this);
	ArrayAccess* d17 = dynamic_cast<ArrayAccess*>(this);
	FieldAccess* d18 = dynamic_cast<FieldAccess*>(this);
	Call* d19 = dynamic_cast<Call*>(this);
	NewExpr* d20 = dynamic_cast<NewExpr*>(this);
	NewArrayExpr* d21 = dynamic_cast<NewArrayExpr*>(this);
	ReadIntegerExpr* d22 = dynamic_cast<ReadIntegerExpr*>(this);
	ReadLineExpr* d23 = dynamic_cast<ReadLineExpr*>(this);
	CompoundExpr* d9 = dynamic_cast<CompoundExpr*>(this);
	Operator* d8 = dynamic_cast<Operator*>(this);
	LValue* d15 = dynamic_cast<LValue*>(this);
	
	if(d2) return SemanticExpr::handle(d2);
	if(d3) return SemanticExpr::handle(d3);
	if(d4) return SemanticExpr::handle(d4);
	if(d5) return SemanticExpr::handle(d5);
	if(d6) return SemanticExpr::handle(d6);
	if(d7) return SemanticExpr::handle(d7);
	if(d10) return SemanticExpr::handle(d10);
	if(d11) return SemanticExpr::handle(d11);
	if(d12) return SemanticExpr::handle(d12);
	if(d13) return SemanticExpr::handle(d13);
	if(d14) return SemanticExpr::handle(d14);
	if(d16) return SemanticExpr::handle(d16);
	if(d17) return SemanticExpr::handle(d17);
	if(d18) return SemanticExpr::handle(d18);
	if(d19) return SemanticExpr::handle(d19);
	if(d20) return SemanticExpr::handle(d20);
	if(d21) return SemanticExpr::handle(d21);
	if(d22) return SemanticExpr::handle(d22);
	if(d23) return SemanticExpr::handle(d23);
	if(d9) return SemanticExpr::handle(d9);
	if(d8) return SemanticExpr::handle(d8);
	if(d15) return SemanticExpr::handle(d15);	
	return SemanticExpr::handle(this);
}

Location* Expr::Emit(Scope* curScope) {
	stdOutput("expr");
	return TACExpr::handle(this, curScope);
}

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

Location* IntConstant::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}

void IntConstant::PrintChildren(int indentLevel) {
	std::cout << value;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}
Location* DoubleConstant::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void DoubleConstant::PrintChildren(int indentLevel) { 
    printf("%g", value);
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}
Location* BoolConstant::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void BoolConstant::PrintChildren(int indentLevel) { 
    printf("%s", value ? "true" : "false");
}

StringConstant::StringConstant(yyltype loc, std::string val) : Expr(loc) {
    Assert(!val.empty());
    value = val;
}
Location* StringConstant::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void StringConstant::PrintChildren(int indentLevel) { 
	std::cout << value;
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
Location* Operator::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void Operator::PrintChildren(int indentLevel) {
    printf("%s",tokenString);
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
Location* ArrayAccess::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void ArrayAccess::PrintChildren(int indentLevel) {
    base->PrintAST(indentLevel+1);
    subscript->PrintAST(indentLevel+1, "(subscript) ");
}

FieldAccess::FieldAccess(Expr *b, Identifier *f)
	: LValue(b ? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
	Assert(f != NULL); // b can be be NULL (just means no explicit base)
	base = b;
	if (base) base->SetParent(this);
	(field = f)->SetParent(this);
}
Location* FieldAccess::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void FieldAccess::PrintChildren(int indentLevel) {
	if (base) base->PrintAST(indentLevel+1);
	field->PrintAST(indentLevel+1);
}

Call::Call(yyltype loc, Expr *b, Identifier *f, std::list<Expr*> *a) : Expr(loc) {
	Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
	base = b;
	if (base) base->SetParent(this);
	(field = f)->SetParent(this);
	for(auto iter : *a) {
		iter->SetParent(this);
	}
	actuals = a;
}
Location* Call::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void Call::PrintChildren(int indentLevel) {
	if (base) base->PrintAST(indentLevel+1);
	field->PrintAST(indentLevel+1);
	for(auto iter : *actuals) {
		iter->PrintAST(indentLevel+1, "(actuals) ");
	}
}

NewExpr::NewExpr(yyltype loc, AstNamedType *c) : Expr(loc) {
	Assert(c != NULL);
	(cType = c)->SetParent(this);
}
Location* NewExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void NewExpr::PrintChildren(int indentLevel) {	
    cType->PrintAST(indentLevel+1);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, AstType *et) : Expr(loc) {
	Assert(sz != NULL && et != NULL);
	(size = sz)->SetParent(this);
	(elemType = et)->SetParent(this);
}
Location* NewArrayExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
void NewArrayExpr::PrintChildren(int indentLevel) {
    size->PrintAST(indentLevel+1);
    elemType->PrintAST(indentLevel+1);
}

Expr::Expr() : Stmt() {
	type = nullptr;
}

Expr::Expr(yyltype loc) : Stmt(loc) {

}

NullConstant::NullConstant(yyltype loc) : Expr(loc) {

}
Location* NullConstant::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
ArithmeticExpr::ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op, rhs) {

}
Location* ArithmeticExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
ArithmeticExpr::ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs, op, rhs) {

}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r)
	: Expr(Join(l->GetLocation(), r->GetLocation())) {
	Assert(l != NULL && o != NULL && r != NULL);
	(op = o)->SetParent(this);
	(left = l)->SetParent(this);
	(right = r)->SetParent(this);
}
Location* CompoundExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
CompoundExpr::CompoundExpr(Operator *o, Expr *r)
	: Expr(Join(o->GetLocation(), r->GetLocation())) {
	Assert(o != NULL && r != NULL);
	left = NULL;
	(op = o)->SetParent(this);
	(right = r)->SetParent(this);
}

bool CompoundExpr::isUnaryOp() {
	return left == NULL;
}

void CompoundExpr::PrintChildren(int indentLevel) {
   if (left) left->PrintAST(indentLevel+1);
   op->PrintAST(indentLevel+1);
   right->PrintAST(indentLevel+1);
}

RelationalExpr::RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs, op, rhs) {

}
Location* RelationalExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}

EqualityExpr::EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs, op, rhs) {

}
Location* EqualityExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
LogicalExpr::LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op, rhs) {

}
Location* LogicalExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
LogicalExpr::LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs, op, rhs) {

}

AssignExpr::AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs, op, rhs) {

}

Location* AssignExpr::Emit(Scope* curScope) {
	stdOutput("Assign");
	return TACExpr::handle(this, curScope);
}

LValue::LValue(yyltype loc) : Expr(loc) {

}
Location* LValue::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
This::This(yyltype loc) : Expr(loc) {

}
Location* This::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
ReadIntegerExpr::ReadIntegerExpr(yyltype loc) : Expr(loc) {

}
Location* ReadIntegerExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}
ReadLineExpr::ReadLineExpr(yyltype loc) : Expr(loc) {

}
Location* ReadLineExpr::Emit(Scope* curScope) {
	return TACExpr::handle(this, curScope);
}

Location* Expr::ReadValue(Scope* curs) {
	return RW::read(this, curs);
}
void Expr::StoreValue(Scope* curs, Location* src) {
	RW::store(this, curs, src);
}

Location* FieldAccess::ReadValue(Scope* curs) {
	return RW::read(this, curs);
}
void FieldAccess::StoreValue(Scope* curs, Location* src) {
	RW::store(this, curs, src);
}

Location* ArrayAccess::ReadValue(Scope* curs) {
	return RW::read(this, curs);
}
void ArrayAccess::StoreValue(Scope* curs, Location* src) {
	RW::store(this, curs, src);
}
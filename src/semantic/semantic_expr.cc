#include "../symbol/SymbolType.h"
#include "../symbol/InternalType.h"
#include "../symbol/ClassSymbol.h"
#include "../symbol/ArrayType.h"
#include "../ast/ast_decl.h"
#include "../ast/ast_expr.h"
#include "../ast/ast_type.h"
#include "../ast/ast.h"
#include "../semantic/semantic_expr.h"
#include "../tools/utility.h"
#include "../error/errors.h"
#include <utility>
std::pair<int, SymbolType*> SemanticExpr::handle(Expr* exp) {
	Assert(1 == 2);
	return {0, nullptr};
}

std::pair<int, SymbolType*> SemanticExpr::handle(EmptyExpr* exp){
	return {Expr::emptyExpr, nullptr};
}

std::pair<int, SymbolType*> SemanticExpr::handle(IntConstant* exp){
	exp->type = InternalType::intType;
	return {Expr::intConstant,  InternalType::intType};
}

std::pair<int, SymbolType*> SemanticExpr::handle(DoubleConstant* exp){
	exp->type = InternalType::doubleType;
	return {Expr::doubleConstant,  InternalType::doubleType};
}

std::pair<int, SymbolType*> SemanticExpr::handle(BoolConstant* exp){
	exp->type = InternalType::boolType;
	return {Expr::boolConstant, InternalType::boolType};
}

std::pair<int, SymbolType*> SemanticExpr::handle(StringConstant* exp){
	exp->type = InternalType::stringType;
	return {Expr::stringConstant, InternalType::stringType};
}

std::pair<int, SymbolType*> SemanticExpr::handle(NullConstant* exp){
	exp->type = InternalType::nullType;
	return {Expr::nullConstant, InternalType::nullType};
}

std::pair<int, SymbolType*> SemanticExpr::handle(Operator* exp){
	return {-1, nullptr};
}

std::pair<int, SymbolType*> SemanticExpr::handle(CompoundExpr* exp){
	stdOutput("CompoundExpr begin");
	Operator* op = exp->op;
	Expr* left = exp->left;
	Expr* right = exp->right;
	std::pair<int, SymbolType*> exp_left {Expr::emptyExpr, nullptr};
	if(left != nullptr) exp_left = left->testAndReturnType();
	std::pair<int, SymbolType*> exp_right {Expr::emptyExpr, nullptr};
	if(right != nullptr) exp_right = right->testAndReturnType();
	SymbolType* res_type = nullptr;
	if(exp_left.first == Expr::emptyExpr) {
		res_type = exp_right.second;
	}
	else if(exp_right.first == Expr::emptyExpr) {
		res_type = exp_left.second;
	}
	else if(exp_left.second == nullptr || exp_right.second == nullptr) {
		res_type = nullptr;
	}
	else if(exp_left.second->IsEquivalentTo(exp_right.second)) {
		res_type = exp_left.second;
	}
	else {
		Assert(exp_left.second->getAstNode() != nullptr);
		Assert(exp_right.second->getAstNode() != nullptr);
		ReportError::IncompatibleOperands(exp->op, dynamic_cast<AstType*>(exp_left.second->getAstNode()), 
			dynamic_cast<AstType*>(exp_right.second->getAstNode()));
	}
	stdOutput("CompoundExpr end");
	exp->type = res_type;
	return {-2, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(ArithmeticExpr* exp){
	/* only int or double can using math expr */
	stdOutput("ArithmeticExpr begin");
	std::pair<int, SymbolType*> exp_com = handle((CompoundExpr*)exp);
	SymbolType* equal_type = exp_com.second;
	SymbolType* res_type = nullptr;
	if(equal_type != nullptr) {
		if(equal_type->IsEquivalentTo(InternalType::intType) || 
			equal_type->IsEquivalentTo(InternalType::doubleType)){
			res_type = equal_type;
		}
		else {
			if(exp->isUnaryOp()) {
				ReportError::IncompatibleOperand(exp->op, dynamic_cast<AstType*>(equal_type->getAstNode()));
			}
			else {
				ReportError::IncompatibleOperands(exp->op, dynamic_cast<AstType*>(equal_type->getAstNode()), 
								dynamic_cast<AstType*>(equal_type->getAstNode()));
			}
		}
	}
	stdOutput("ArithmeticExpr end");
	exp->type = res_type;
	return {Expr::arithmeticExpr, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(RelationalExpr* exp){
	stdOutput("RelationalExpr begin");
	std::pair<int, SymbolType*> exp_com = handle((CompoundExpr*)exp);
	SymbolType* equal_type = exp_com.second;
	SymbolType* res_type = nullptr;
	if(equal_type != nullptr) {
		if(equal_type->IsEquivalentTo(InternalType::intType) || 
			equal_type->IsEquivalentTo(InternalType::doubleType)) {
			res_type = InternalType::boolType;
		}
		else {
			ReportError::IncompatibleOperands(exp->op, dynamic_cast<AstType*>(equal_type->getAstNode()), 
				dynamic_cast<AstType*>(equal_type->getAstNode()));
		}
	}
	stdOutput("RelationalExpr end");
	exp->type = res_type;
	return {Expr::relationalExpr, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(EqualityExpr* exp) {
	stdOutput("EqualityExpr begin");
	std::pair<int, SymbolType*> exp_com = handle((CompoundExpr*)exp);
	SymbolType* res_type = nullptr;
	if(exp_com.second != nullptr) {
		res_type = InternalType::boolType;
	}
	stdOutput("EqualityExpr end");
	exp->type = res_type;
	return {-3, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(LogicalExpr* exp) {
	/* only bool can using math expr */
	stdOutput("LogicalExpr begin");
	std::pair<int, SymbolType*> exp_com = handle((CompoundExpr*)exp);
	SymbolType* equal_type = exp_com.second;
	SymbolType* res_type = nullptr;
	if(equal_type != nullptr) {
		if (equal_type->IsEquivalentTo(InternalType::boolType)) {
			res_type = InternalType::boolType;
		}
		else {
			if(exp->isUnaryOp()) { 
				ReportError::IncompatibleOperand(exp->op, new AstType(equal_type->getName()));
			}
			else {
				ReportError::IncompatibleOperands(exp->op, new AstType(equal_type->getName()), 
									new AstType(equal_type->getName()));
			}
		}
	}
	stdOutput("LogicalExpr end");
	exp->type = res_type;
	return {Expr::logicalExpr, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(AssignExpr* exp){
	/* any equality type or objects and null can using Assign expr */
	stdOutput("AssignExpr begin");
	std::pair<int, SymbolType*> exp_com = handle((CompoundExpr*)exp);
	stdOutput("AssignExpr end");
	exp->type = exp_com.second;
	return {Expr::assisgnExpr, exp_com.second};
}

std::pair<int, SymbolType*> SemanticExpr::handle(LValue* exp) {
	Assert(1 == 2);
	return {-34, nullptr};
}

std::pair<int, SymbolType*> SemanticExpr::handle(This* exp) {
	stdOutput("This begin");
	ClassSymbol* class_symbol = top_scope->getClassScope();
	SymbolType* res_type = class_symbol;
	if(class_symbol == nullptr) {
		ReportError::ThisOutsideClassScope(exp);
	}
	stdOutput("This end");
	exp->type = res_type;
	return {-33, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(ArrayAccess* exp){
	/* check base is Lvalue and base type is array, subscript is int */
	stdOutput("ArrayAccess begin");
	std::pair<int, SymbolType*> exp_base {Expr::emptyExpr, nullptr};
	std::pair<int, SymbolType*> exp_sub {Expr::emptyExpr, nullptr};
	SymbolType* res_type = nullptr;
	if (exp->base) 
		exp_base = exp->base->testAndReturnType();
	if (exp->subscript) 
		exp_sub = exp->subscript->testAndReturnType();
	if (exp_sub.second != nullptr && exp_base.second != nullptr) {
		if (!exp_sub.second->IsEquivalentTo(InternalType::intType)) {
			ReportError::SubscriptNotInteger(exp);
		}
		if (!exp_base.second->isArray()) {
			//emmm...
		}
		else {
			ArrayType* arrType = dynamic_cast<ArrayType*>(exp_base.second);
			Assert(arrType != nullptr);
			res_type = arrType->getElmType();
		}
	}
	stdOutput("ArrayAccess end");
	exp->type = res_type;
	return {-22, res_type};
}

std::pair<int, SymbolType*> SemanticExpr::handle(FieldAccess* exp) {
	/*may be this.Id, ClassName.id(nested), (new	 ClassName).id, or just id */
	stdOutput("FieldAccess begin");
	std::pair<int, SymbolType*> exp_base {Expr::emptyExpr, nullptr};
	stdOutput("FieldAccess base begin");
	if(exp->base != nullptr) 
		exp_base = exp->base->testAndReturnType();
	stdOutput("FieldAccess base end");
	Symbol* res = nullptr;
	Identifier* field = exp->field;
	if(exp_base.first == Expr::emptyExpr) {
		stdOutput("FieldAccess field A begin: " + field->getName());
		res = top_scope->getSymbol(field->getName(), true);
		if(res == nullptr) {
			ReportError::IdentifierNotDeclared(field, reasonT::LookingForVariable);
		}
		else {
			stdOutput("FieldAccess field : " + field->getName() + " find " + res->getName());
		}
	}
	else {
		stdOutput("FieldAccess field A.b begin");
		if(exp_base.second != nullptr) {
			ClassSymbol* class_type = dynamic_cast<ClassSymbol*>(exp_base.second);
			InterfaceSymbol* int_type = dynamic_cast<InterfaceSymbol*>(exp_base.second);
			if(class_type == nullptr && int_type == nullptr) {
				ReportError::IdentifierNotDeclared(new Identifier(*exp->GetLocation(), exp_base.second->getName()), 
					reasonT::LookingForClass);
			}
			else if(class_type != nullptr) {
				res = class_type->getSymbol(field->getName(), true);
				if(res == nullptr) {
					ReportError::FieldNotFoundInBase(field, new AstType(class_type->Symbol::getName()));
				}
			} 
			else if(int_type != nullptr) {
				res = int_type->getSymbol(field->getName(), true);
				if(res == nullptr) {
					ReportError::FieldNotFoundInBase(field, new AstType(int_type->Symbol::getName()));
				}
			}
		}
	}
	stdOutput("FieldAccess end");
	if(res == nullptr) return {-26, nullptr};
	exp->type = res->getType();
	return {-26, res->getType()};
}

std::pair<int, SymbolType*> SemanticExpr::handle(Call* exp) {
	stdOutput("Call begin");
	std::pair<int, SymbolType*> exp_base {Expr::emptyExpr, nullptr};
	FunctionSymbol* res = nullptr;
	std::list<Expr*> *actuals = exp->actuals;
	if(exp->base != nullptr)
		exp_base = exp->base->testAndReturnType();
	if(exp->base != nullptr && exp_base.second == nullptr) {
		return {-9, nullptr};
	}
	if(exp_base.first == Expr::emptyExpr) {
		stdOutput(exp->field->getName());
		Symbol* sym = top_scope->getSymbol(exp->field->getName(), true);
		if(sym != nullptr) {
			stdOutput("???");
			FnDecl* fn = dynamic_cast<FnDecl*>(sym->Symbol::getAstNode());
			std::cout << fn << endl;
			if(fn != nullptr && !fn->getIsSematicFinished()) {
				stdOutput(">>>>>");
				fn->SemanticAnalysis();
			}
			res = dynamic_cast<FunctionSymbol*>(sym->getType());
		}
		else {
			ReportError::IdentifierNotDeclared(exp->field, reasonT::LookingForFunction);
		}
	}
	else {
		ClassSymbol* class_type = dynamic_cast<ClassSymbol*>(exp_base.second);
		InterfaceSymbol* int_type = dynamic_cast<InterfaceSymbol*>(exp_base.second);
		ArrayType* array_type = dynamic_cast<ArrayType*>(exp_base.second);
		if(class_type == nullptr && array_type == nullptr && int_type == nullptr) {
			ReportError::FieldNotFoundInBase(exp->field, new AstType(exp_base.second->getName()));
		}
		else if(array_type != nullptr) {
			if(exp->field->getName() != "length") {
				ReportError::FieldNotFoundInBase(exp->field, new AstNamedType(
					new Identifier(*(exp->base->GetLocation()), array_type->getName())
				));
			}
			res = new FunctionSymbol("length", InternalType::intType, new std::list<SymbolType*>);
		}
		else if(class_type != nullptr){
			Symbol* sym = class_type->getSymbol(exp->field->getName(), true);
			if(sym != nullptr) {
				Scope* temp = top_scope;
				top_scope = class_type;
				FnDecl* fn = dynamic_cast<FnDecl*>(sym->Symbol::getAstNode());
				if(fn != nullptr && !fn->getIsSematicFinished()) {
					fn->SemanticAnalysis();
				}
				top_scope = temp;
				res = dynamic_cast<FunctionSymbol*>(sym->getType());
			} else {
				ReportError::FieldNotFoundInBase(exp->field, new AstNamedType(
					new Identifier(*(exp->base->GetLocation()), class_type->Symbol::getName())
				));
			}
		}
		else if(int_type != nullptr) {
			Symbol* sym = int_type->getSymbol(exp->field->getName(), true);
			Scope* temp = top_scope;
			top_scope = int_type;
			FnDecl* fn = dynamic_cast<FnDecl*>(sym->Symbol::getAstNode());
			if(fn != nullptr && !fn->getIsSematicFinished()) {
				fn->SemanticAnalysis();
			}
			top_scope = temp;
			if(sym != nullptr) {
				res = dynamic_cast<FunctionSymbol*>(sym->getType());
			} else {
				ReportError::FieldNotFoundInBase(exp->field, new AstNamedType(
					new Identifier(*(exp->base->GetLocation()), int_type->Symbol::getName())
				));
			}
		}
		else {
			Assert(1 == 2);
		}
	}
	if(res == nullptr){
		for (auto iter : *(exp->actuals)) {
			iter->testAndReturnType();
		}
	}
	else {
		if (actuals->size() != res->getNumberOfParameters()) {
			ReportError::NumArgsMismatch(exp->field, res->getNumberOfParameters(), actuals->size());
		}
		else {
			list<SymbolType*>* expected_list = res->getArgumentTypes();
			auto iter_given = actuals->begin(); 
			int index = 1;
			for(auto iter_expected = expected_list->begin(); iter_expected != expected_list->end(); 
				++iter_expected, ++iter_given, ++index) {
				std::pair<int, SymbolType*> param = (*iter_given)->testAndReturnType();
				SymbolType* given = param.second;
				SymbolType* expected = *iter_expected;
				if (!given->IsEquivalentTo(expected)) {
					ReportError::ArgMismatch(*iter_given, index, 
						new AstType(given->getName()), new AstType(expected->getName()));
				}
			}
		}
	}
	stdOutput("Call end");
	exp->type = nullptr;
	if(res == nullptr) return {-9, nullptr};
	exp->type = res->getReturnType();
	return {-9, res->getReturnType()};
}

std::pair<int, SymbolType*> SemanticExpr::handle(NewExpr* exp) {
	/* just check wether cType is Class */
	stdOutput("NewExpr begin");
	Assert(exp->cType != nullptr);
	Symbol* sym = top_scope->getSymbol(exp->cType->getName(), true);
	SymbolType* given = dynamic_cast<ClassSymbol*>(sym);
	if(given == nullptr) {
		ReportError::IdentifierNotDeclared(exp->cType->id, reasonT::LookingForClass);
	}
	else if(!given->isClass()) {
		Assert(1 == 2);
	}
	stdOutput("NewExpr end");
	exp->type = given;
	return {-25, given};
}

std::pair<int, SymbolType*> SemanticExpr::handle(NewArrayExpr* exp) {
	/* size must be int, elemType must declaration */
	stdOutput("NewArrayExpr begin");
	std::pair<int, SymbolType*> size_exp = exp->size->testAndReturnType();
	if (!size_exp.second->IsEquivalentTo(InternalType::intType)) {
		ReportError::NewArraySizeNotInteger(exp->size);
	}
	AstNamedType* cname = dynamic_cast<AstNamedType*>(exp->elemType);
	SymbolType* res = nullptr;
	if(cname != nullptr) {
		ClassSymbol* f = top_scope->getClassSymbol(cname->getName());
		res = f;
		if(f == nullptr) {
			ReportError::IdentifierNotDeclared(cname->id, reasonT::LookingForClass);
		}
	}
	else{
		res = exp->elemType->Generate();
	}
	stdOutput("NewArrayExpr end");
	if(res == nullptr) 
		return {20, nullptr};
	res = new ArrayType(res, new AstArrayType(*(exp->GetLocation()), exp->elemType));
	exp->type = res;
	return {20, res};
}

std::pair<int, SymbolType*> SemanticExpr::handle(ReadIntegerExpr* exp){
	stdOutput("ReadIntegerExpr begin");
	stdOutput("ReadIntegerExpr end");
	exp->type = InternalType::voidType;
	return {21,  InternalType::intType};
}

std::pair<int, SymbolType*> SemanticExpr::handle(ReadLineExpr* exp){
	stdOutput("ReadLineExpr begin");
	stdOutput("ReadLineExpr end");
	exp->type = InternalType::voidType;
	return {22, InternalType::stringType};
}
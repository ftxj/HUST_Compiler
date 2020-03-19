#include "../symbol/SymbolType.h"
#include "../symbol/InternalType.h"
#include "../symbol/ClassSymbol.h"
#include "../symbol/ArrayType.h"
#include "../tools/utility.h"
#include "../error/errors.h"

#include "../ast/ast_decl.h"
#include "../ast/ast_expr.h"
#include "../ast/ast_type.h"
#include "../ast/ast.h"

#include "../generate/tac.h"
#include "../generate/tac_expr.h"
#include "../generate/codegen.h"
#include "../generate/rw.h"

#include "../semantic/semantic_expr.h"

#include <utility>
Location* TACExpr::handle(Expr* exp, Scope* curScope) {
    Assert(1 == 2);
	return nullptr;
}

Location* TACExpr::handle(EmptyExpr* exp, Scope* curScope){
	return nullptr;
}

Location* TACExpr::handle(IntConstant* exp, Scope* curScope){
    stdOutput("Int handle");
	return generator->GenLoadConstant(exp->value);
}

Location* TACExpr::handle(DoubleConstant* exp, Scope* curScope){
    Assert(1 == 2);
	return nullptr;
}

Location* TACExpr::handle(BoolConstant* exp, Scope* curScope){
    Location* res = generator->GenLoadConstant(exp->value);
    exp->setVarLocation(res); 
	return res;
}

Location* TACExpr::handle(StringConstant* exp, Scope* curScope){
	Location* res = generator->GenLoadConstant(exp->value);
    exp->setVarLocation(res); 
	return res;
}

Location* TACExpr::handle(NullConstant* exp, Scope* curScope){
    Location* res = generator->GenLoadConstant(0);
    exp->setVarLocation(res); 
	return res;
}

Location* TACExpr::handle(Operator* exp, Scope* curScope){
	return nullptr;
}

Location* TACExpr::handle(CompoundExpr* exp, Scope* curScope){
	return nullptr;
}

Location* TACExpr::handle(ArithmeticExpr* exp, Scope* curScope) {
    Expr* left = exp->left;
    Expr* right = exp->right;
	Location *src = right->ReadValue(curScope);
    Location *left_loc; 
    Location* res = nullptr;
    if (left != nullptr) {
        left_loc = left->ReadValue(curScope);
        res = generator->GenBinaryOp(std::string(exp->op->tokenString), left_loc, src); 

    }
    else {
        if (std::string(exp->op->tokenString) == "-") {
            Location *place_holder = generator->GenLoadConstant(0); 
            res = generator->GenBinaryOp("-", place_holder, src); 
        }
    }
    exp->setVarLocation(res);
    return res;
}

Location* TACExpr::handle(RelationalExpr* exp, Scope* curScope){
    Expr* left = exp->left;
    Expr* right = exp->right;
    std::string op = std::string(exp->op->tokenString);
	Location *srcR = right->ReadValue(curScope); 
    Location *srcL = left->ReadValue(curScope);
    Location* res = nullptr;
    if (op == "<") { 
        res = generator->GenBinaryOp(op, srcL, srcR); 
    }
    else if (op == ">") {
        res =  generator->GenBinaryOp("<", srcR, srcL); 
    }
    else if (op == "<=") {
        Location *less_than = generator->GenBinaryOp("<", srcL, srcR); 
        Location *equals = generator->GenBinaryOp("==", srcL, srcR); 
        res =  generator->GenBinaryOp("||", less_than, equals); 
    }
    if (op == ">=") {
        Location *greater_than = generator->GenBinaryOp("<", srcR, srcL); 
        Location *equals = generator->GenBinaryOp("==", srcL, srcR); 
        res =   generator->GenBinaryOp("||", greater_than, equals); 
    }
    exp->setVarLocation(res);
    return res;
}

Location* TACExpr::handle(EqualityExpr* exp, Scope* curScope) {
    Expr* left = exp->left;
    Expr* right = exp->right;
	Location *srcR = right->ReadValue(curScope); 
    Location *srcL = left->ReadValue(curScope);
    std::string op = std::string(exp->op->tokenString);
    Location* res = nullptr;
    if (op == "!=") {
        stdOutput(op);
        Location *is_equal; 
        if (left->type == InternalType::stringType) {
            is_equal = generator->GenBuiltInCall(StringEqual, srcL, srcR); 
        }
        else {
            is_equal = generator->GenBinaryOp("==", srcR, srcL); 
        }
        Location *one = generator->GenLoadConstant(1); 
        res = generator->GenBinaryOp("-", one, is_equal); 
    }
    else {
        stdOutput(op);
        if (left->type == InternalType::stringType) {
            res = generator->GenBuiltInCall(StringEqual, srcL, srcR); 
        }
        else {
            res = generator->GenBinaryOp("==", srcR, srcL); 
        }
    }
    exp->setVarLocation(res);
    return res;
}

Location* TACExpr::handle(LogicalExpr* exp, Scope* curScope) {
    Expr* left = exp->left;
    Expr* right = exp->right;
	Location *src = right->ReadValue(curScope); 
    Location *left_loc; 
    if (left != nullptr) {
        left_loc = left->ReadValue(curScope);
        return generator->GenBinaryOp(std::string(exp->op->tokenString), left_loc, src); 
    }
    else {
        if (std::string(exp->op->tokenString) == "!") {
            Location *one = generator->GenLoadConstant(1); 
            Location *unary_not = generator->GenBinaryOp("-", one, src); 
            exp->setVarLocation(unary_not);
            return unary_not;
        }
    }
	return nullptr;
}

Location* TACExpr::handle(AssignExpr* exp, Scope* curScope){
    stdOutput("Assign Expr handle");
    Expr* left = exp->left;
    Expr* right = exp->right;
    Location* src = nullptr;
    src= right->ReadValue(curScope);
    left->StoreValue(curScope, src);
    exp->setVarLocation(src);
    stdOutput("assign end");
    return src;
}

Location* TACExpr::handle(LValue* exp, Scope* curScope) {
	return nullptr;
}

Location* TACExpr::handle(This* exp, Scope* curScope) {
    stdOutput("1111111");
    Location *res = new Location(fpRelative, 4, "this"); 
    return res;
}

Location* TACExpr::handle(ArrayAccess* exp, Scope* curScope) {
    Expr* subscript = exp->subscript;
    Expr* base = exp->base;
    if(exp->getVarLocation() != nullptr) {
        return exp->getVarLocation();
    }
    Location *subscript_loc = subscript->Emit(curScope); 
    ArrayAccess *base_array = dynamic_cast<ArrayAccess*>(base);
    Location* base_loc = nullptr;
    if(base_array != nullptr) 
        base_loc = base->ReadValue(curScope);
    else 
        base_loc = base->Emit(curScope);
    Location* four = generator->GenLoadConstant(4); 
    Location* offset = generator->GenBinaryOp("*", four, subscript_loc); 
    Location* res= generator->GenBinaryOp("+", base_loc, offset); 
    exp->setVarLocation(res);
    return res;
}

Location* TACExpr::handle(FieldAccess* exp, Scope* curScope) {
    stdOutput("Field Access handle");
    Identifier* field = exp->field;
    Expr* base = exp->base;
    if(exp->base == nullptr) {
        ClassSymbol* cScope = curScope->getClassScope();
        Symbol* cSymbol = nullptr;
        if(cScope != nullptr) cSymbol = cScope->getSymbol(field->getName() ,false);
        Assert(curScope != nullptr);
        Symbol* curSymbol = curScope->getSymbol(field->getName(), true);
        Node* declNode = curSymbol->getAstNode();
        Assert(curSymbol != nullptr);
        if(cScope != nullptr && curSymbol == cSymbol) {
            int bias = curSymbol->getInsertionOrderNumber();
            Location* thisLabel = new Location(fpRelative, 4, "this");
            Location* off = generator->GenLoadConstant(bias * 4);
            Location* varP = generator->GenBinaryOp("+", thisLabel, off);
            stdOutput("1212");
            return varP;
        }
        else if(declNode->getVarLocation() != nullptr) {
            stdOutput("2323");
            return declNode->getVarLocation();
        }
        Assert(1 == 2);
    }
    else {
        SymbolType* type = base->type;
        stdOutput(type->getTableName());
        ClassSymbol* cScope = dynamic_cast<ClassSymbol*>(type);
        Assert(cScope != nullptr);
        Symbol* sym = cScope->getSymbol(field->getName(), true);
        int bias = sym->getInsertionOrderNumber();
        Location* baseLoc = base->ReadValue(curScope); // This
        Location* off = generator->GenLoadConstant(bias * 4);
        Location* varP = generator->GenBinaryOp("+", baseLoc, off);
        stdOutput("333");
        return varP; 
    }
	return nullptr;
}

Location* TACExpr::handle(Call* exp, Scope* curScope) {
    stdOutput("Call handle");
    Expr* base = exp->base;
    Identifier* field = exp->field;
    std::string fnName= field->getName();
    stdOutput(fnName);
    std::list<Expr*>* actuals = exp->actuals;
    Symbol* cSymbol = nullptr;
    ClassSymbol* cScope = curScope->getClassScope();
    if(cScope != nullptr) 
        cSymbol = cScope->getSymbol(field->getName() ,false);
    if(cSymbol != nullptr && base == nullptr) {
        base = new This(*(field->location));
        base->type = cScope;
    }
    if (base == nullptr) {
        FunctionSymbol* fnSymbol = curScope->getFncSymbol(fnName);
        FnDecl *curr = dynamic_cast<FnDecl*>(fnSymbol->Symbol::getAstNode());
        Assert(curr != nullptr);
        int numBytesOfParams = 0; 
        for (auto iter = actuals->rbegin(); iter != actuals->rend(); ++iter) {
            SymbolType* type = (*iter)->type;
            Location *l = (*iter)->ReadValue(curScope);
            generator->GenPushParam(l); 
            numBytesOfParams += 4;
        }
        string str = "_" + fnName; 
        bool hasReturnValue;          
        if (fnSymbol->getReturnType()->IsEquivalentTo(InternalType::voidType))
            hasReturnValue = false; 
        else
            hasReturnValue = true; 
        Location *return_val = generator->GenLCall(str, hasReturnValue);
        generator->GenPopParams(numBytesOfParams);
        stdOutput("Call handle end");
        return return_val;
    }
    else {
        stdOutput("A.b() handle");
        SymbolType* type = base->type;
        stdOutput(type->getTableName());
        ClassSymbol* cScope = dynamic_cast<ClassSymbol*>(type);
        Assert(cScope != nullptr);
        FunctionSymbol* fnSymbol = cScope->getFncSymbol(fnName);
        Location* baseLoc = base->ReadValue(curScope); // This
        Location* VTable = generator->GenLoad(baseLoc);
        int bias = fnSymbol->getInsertionOrderNumber() - 1;
        Location* varP = generator->GenLoad(VTable, bias * 4);
        int numBytesOfParams = 0;
        for (auto iter = actuals->rbegin(); iter != actuals->rend(); ++iter) {
            Location *l = (*iter)->ReadValue(curScope); 
            generator->GenPushParam(l); 
            numBytesOfParams += 4; 
        }
        Location *l = baseLoc; 
        generator->GenPushParam(l); 
        numBytesOfParams += 4; 
        bool hasReturnValue;          
        if (fnSymbol->getReturnType()->IsEquivalentTo(InternalType::voidType))
            hasReturnValue = false; 
        else
            hasReturnValue = true; 
        Location* call = generator->GenACall(varP, hasReturnValue);
        generator->GenPopParams(numBytesOfParams);
        stdOutput("Call handle end");
        return call;
    }
	return nullptr;
}

Location* TACExpr::handle(NewExpr* exp, Scope* curScope) {
    AstNamedType* type = exp->cType;
    std::string className = type->getName();
    ClassSymbol* cSymbol = curScope->getClassSymbol(className);
    Assert(cSymbol != nullptr);
    int size = cSymbol->getSize() + 1;
    Assert(4 * size >= 0);
    Location* four = generator->GenLoadConstant(4 * size);
    Location* alloc = generator->GenBuiltInCall(Alloc, four);
    Location *vtable = generator->GenLoadLabel(type->getName()); 
    generator->GenStore(alloc, vtable);
    return alloc;
}

Location* TACExpr::handle(NewArrayExpr* exp, Scope* curScope) {
    AstType* type = exp->elemType;
    Expr* size = exp->size;
    Location* four = generator->GenLoadConstant(4);
    Location* sizeLoc = size->Emit(curScope);
    Location* realSize = generator->GenBinaryOp("*", four, sizeLoc);
    Location* call = generator->GenBuiltInCall(Alloc, realSize);
	return call;
}

Location* TACExpr::handle(ReadIntegerExpr* exp, Scope* curScope) {
    return generator->GenBuiltInCall(ReadInteger); 
}

Location* TACExpr::handle(ReadLineExpr* exp, Scope* curScope) {
    return generator->GenBuiltInCall(ReadLine); 
}
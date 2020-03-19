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

#include "../generate/tac.h"
#include "../generate/tac_decl.h"
#include "../generate/codegen.h"
#include "../semantic/semantic.h"
#include <map>
#include <iostream>
void TACDecl::handle(Decl* decl, Scope* cuScope){

}

void TACDecl::handle(VarDecl* decl, Scope* cuScope){
    Location* newL = nullptr;
    AstArrayType* arrType = dynamic_cast<AstArrayType*>(decl->type);
    ClassSymbol* cScope = dynamic_cast<ClassSymbol*>(cuScope);
    Symbol* sym = cuScope->getSymbol(decl->getName(), false);
    if(cuScope == Semantic::globleScope) {
        newL = new Location(gpRelative, generator->nextGlobalOffset, decl->getName());
        generator->nextGlobalOffset -= 4;
    }
    else if(cScope != nullptr) {
        return;
    }
    else {
        newL = new Location(fpRelative, generator->nextLocalOffset, decl->getName());
        generator->nextLocalOffset -= 4; 
        generator->currFunctionFrameSize += 4;
    }
    std::cout << decl->getName() << " L:" << newL << std::endl;
    decl->setVarLocation(newL);
}

void TACDecl::handle(ClassDecl* decl, Scope* cuScope){
    std::string className = decl->getName();
    ClassSymbol* cScope = cuScope->getClassSymbol(className);
    Assert(cScope != nullptr);
    stdOutput("1");
    cScope->getLayOut();
    stdOutput("2");
    cScope->getVTable();
    stdOutput("4");
    std::list<Decl*>* members = decl->members;
    std::list<std::string>* methodLabels = cScope->getVTable();
    stdOutput("3");
    for(auto iter : *methodLabels) {
        stdOutput(iter);
    }
    generator->GenVTable(className, methodLabels);
    for (auto iter : *members) {
        iter->Emit(cScope); 
    }
}

void TACDecl::handle(InterfaceDecl* decl, Scope* cuScope){

}

void TACDecl::handle(FnDecl* decl, Scope* cuScope) {
    ClassSymbol* cuClassScope = dynamic_cast<ClassSymbol*>(cuScope);
    generator->currSeg = fpRelative;
    generator->nextLocalOffset = generator->OffsetToFirstLocal; 
    generator->nextParamOffset = generator->OffsetToFirstParam; 
    std::string label;
    std::string fnName = decl->getName();
    if (fnName == "main" && cuScope == Semantic::globleScope) {
        label =  "main"; 
    }
    else if (cuClassScope == nullptr) {
        label = "_" + fnName; 
    }
    else if (cuClassScope != nullptr) {
        string cname = cuClassScope->Symbol::getName(); 
        label = "_" + cname + "." + fnName; 
    }
    generator->GenLabel(label);
    BeginFunc *b = generator->GenBeginFunc(); 
    int a;
    if (cuScope == Semantic::globleScope)
        a = 0;
    else
        a = 1;  //because the first parameter in formals is actually the 2nd parameter on the stack b/c of the implicit this pointer
    std::list<VarDecl*> *formals = decl->formals;
    int index = 0;
    for (auto iter = formals->begin(); iter != formals->end(); ++iter, ++index) {
        int offset = (index + a + 1) * 4; 
        Location *i_th = new Location(fpRelative, offset, (*iter)->getName());
        (*iter)->setVarLocation(i_th);
    }
    decl->body->Emit(cuScope->getFncSymbol(decl->getName()));
    b->SetFrameSize(generator->currFunctionFrameSize); 
    generator->GenEndFunc();
    generator->currFunctionFrameSize = 0;
    generator->currSeg = gpRelative; 
}
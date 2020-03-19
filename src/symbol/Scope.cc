#include <map>
#include <list>
#include <iostream>
#include <cstdio>
#include "../ast/ast.h"
#include "../symbol/ClassSymbol.h"
#include "../symbol/FunctionSymbol.h"
#include "../symbol/InterfaceSymbol.h"
#include "../symbol/Scope.h"
#include "../tools/utility.h"
#include "../tools/TextTable.h"

Scope::Scope() : parent(nullptr) { 
    InsertOrder = 0; 
    order = 0;
    fnInsertOrder = 0; 
}

Scope::Scope(Scope* p) : parent(p) { 
    InsertOrder = 0; 
    order = 0;
    fnInsertOrder = 0; 
}

void Scope::setParentScope(Scope* parent) {
	this->parent = parent;
}

Scope* Scope::getParentScope() { 
    return parent;
}

std::map<std::string, Symbol*> Scope::getMembers() {
	return symbols;
}

void Scope::setLoop(bool b) {
    isLoop = b;
}

void Scope::addNested(Scope* s) {
    nestedScopes.push_back(s);
}

Symbol* Scope::addSymbol(Symbol* sym) {
	if (symbols.find(sym->getName()) != symbols.end()) {
        return symbols.find(sym->getName())->second;
    }
    int lexOrder = 0;
    FunctionSymbol* fn = dynamic_cast<FunctionSymbol*>(sym);
    order++;
    if(fn != nullptr) {
        lexOrder = ++fnInsertOrder;
    } 
    else {
        lexOrder = ++InsertOrder;
    }
    sym->setInsertionOrderNumber(lexOrder);
    orderList.push_back({sym->getName(), order - 1});
    sym->setScope(this);
    // sym->setInsertionOrderNumber(symbols.size());
    symbols.insert({sym->getName(), sym});
    return nullptr;
}
void Scope::setSuperFnNum(int num) {
    fnInsertOrder = num;
}

FunctionSymbol* Scope::getFncScope() {
    Scope* iter = this;
    FunctionSymbol* res = nullptr;
    while(iter != nullptr) {
        if((res = dynamic_cast<FunctionSymbol*>(iter)) != nullptr) {
            return res;
        }
        iter = iter->getParentScope();
    }
    return nullptr;
}

FunctionSymbol* Scope::getFncSymbol(std::string name) {
    return dynamic_cast<FunctionSymbol*>(getSymbol(name, true));
}

ClassSymbol* Scope::getClassSymbol(std::string name) {
    return dynamic_cast<ClassSymbol*>(getSymbol(name, true));
}

ClassSymbol* Scope::getClassScope() {
    Scope* iter = this;
    ClassSymbol* res = nullptr;
    while(iter != nullptr) {
        if((res = dynamic_cast<ClassSymbol*>(iter)) != nullptr) {
            return res;
        }
        iter = iter->getParentScope();
    }
    return nullptr;
}

InterfaceSymbol* Scope::getInterfaceSymbol(std::string name) {
    Symbol* res = getSymbol(name, true);
    return dynamic_cast<InterfaceSymbol*>(res);
}

Scope* Scope::getLoopedScope() {
    Scope* iter = this;
    while(iter != nullptr) {
        if(iter->isLoop) {
            return iter;
        }
        iter = iter->getParentScope();
    }
    return nullptr;
}

Symbol* Scope::getSymbol(std::string name, bool resolve) {
    auto res = symbols.find(name);
    if (res != symbols.end()) {
        return res->second;
    }
    if(resolve) {
        Scope* parent = getParentScope();
        if (parent != nullptr) 
            return parent->getSymbol(name, resolve);
    }
    return nullptr;
}

void Scope::PrintSymbolTable(TextTable* t, std::string scopeName) {
    bool ff = false;
    if(t == nullptr) {
        ff = true;
        t = new TextTable( '-', '|', '+' );
        t->setHead(scopeName);
        t->add("Line Number");
        t->add("Identifier");
        t->add("Type");
        t->endOfRow();
    }
    for(auto iter : orderList) {
        Symbol* sym = getSymbol(iter.first, false);
        Assert(sym != nullptr);
        int line = sym->getAstNode()->GetLocation()->first_line;
        t->add(std::to_string(line));
        t->add(sym->Symbol::getName());
        if(sym->getType() != nullptr) {
            t->add(sym->getType()->getTableName());
        }
        else {
            t->add("error");
        }
        t->endOfRow();
    }
    int i = 0;
    for(auto iter : nestedScopes) {
        ++i;
        iter->PrintSymbolTable(t, "Global Block " + std::to_string(i));
    }

    if(ff)
        std:cout << *t << std::endl;
    for(auto iter : orderList) {
        Symbol* sym = getSymbol(iter.first, false);
        ClassSymbol* cSym = nullptr;
        InterfaceSymbol* iSym = nullptr;
        FunctionSymbol* fSym = nullptr;
        if((cSym = dynamic_cast<ClassSymbol*>(sym)) != nullptr) {
            cSym->PrintSymbolTable(nullptr, cSym->Symbol::getName());
        }
        else if((iSym = dynamic_cast<InterfaceSymbol*>(sym)) != nullptr) {
            iSym->PrintSymbolTable(nullptr, iSym->Symbol::getName());
        }
        else if((fSym = dynamic_cast<FunctionSymbol*>(sym)) != nullptr) {
            fSym->PrintSymbolTable(nullptr, fSym->Symbol::getName());
        }
    }
}
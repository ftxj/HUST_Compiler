#include "../symbol/FunctionSymbol.h"
#include "../symbol/Symbol.h"
#include "../symbol/Scope.h"
#include "../symbol/LocalScope.h"
#include "../tools/utility.h"
#include "../symbol/LocalScope.h"
#include "../symbol/ClassSymbol.h"
#include "../symbol/InterfaceSymbol.h"
#include "../tools/TextTable.h"
#include "../symbol/SymbolType.h"
#include "../ast/ast.h"
#include "../ast/ast_decl.h"
#include <algorithm>
#include <list>
#include <string>
void ClassSymbol::PrintSymbolTable(TextTable* tt, std::string scopeName) {
    bool ff = false;
    std::string base = scopeName;
    if(tt == nullptr) {
        ff = true;
        tt = new TextTable('-', '|', '+' );
        tt->setHead("Class " + this->Symbol::getName());
        tt->add("Line Number");
        tt->add("Identifier");
        tt->add("Type");
        tt->add("Base");
        tt->endOfRow();
        base = "this";
    }

    for(auto iter : orderList) {
        Symbol* sym = getSymbol(iter.first, false);
        Assert(sym != nullptr);
        int line = sym->getAstNode()->GetLocation()->first_line;
        tt->add(std::to_string(line));
        tt->add(sym->Symbol::getName());
        if(sym->getType() != nullptr) {
            tt->add(sym->getType()->getTableName());
        }
        else {
            tt->add("error");
        }
        tt->add(base);
        tt->endOfRow();
    }
    int i = 0;
    for(auto iter : nestedScopes) {
        ++i;
        iter->PrintSymbolTable(tt, base  + " Block " + std::to_string(i));
    }
    
    if(superScope != nullptr) {
        superScope->PrintSymbolTable(tt, base + "::" + superScope->Symbol::getName());
    }

    if(ff) {
        std:cout << *tt << std::endl;
        for(auto iter : orderList) {
            Symbol* sym = getSymbol(iter.first, false);
            ClassSymbol* cSym = nullptr;
            InterfaceSymbol* iSym = nullptr;
            FunctionSymbol* fSym = nullptr;
            if((cSym = dynamic_cast<ClassSymbol*>(sym)) != nullptr) {
                cSym->PrintSymbolTable(nullptr,  scopeName + "::" + cSym->Symbol::getName());
            }
            else if((iSym = dynamic_cast<InterfaceSymbol*>(sym)) != nullptr) {
                iSym->PrintSymbolTable(nullptr,  scopeName + "::" + iSym->Symbol::getName());
            }
            else if((fSym = dynamic_cast<FunctionSymbol*>(sym)) != nullptr) {
                fSym->PrintSymbolTable(nullptr,  scopeName + "::" + fSym->Symbol::getName());
            }
        }
    }
}

bool ClassSymbol::IsEquivalentTo(SymbolType * type) {
    if(type == nullptr) return false;
    if(type->name == "null") return true;
    ClassSymbol* ss = dynamic_cast<ClassSymbol*>(type);
    if(ss == nullptr) return false;
    if(ss != nullptr) {
        if(ss->Symbol::name == Symbol::name) {
            return true;
        }
        std::map<std::string, InterfaceSymbol*>* t = ss->getAllInterfaces();
        for(auto iter : *t) {
            if(interfaceSymbols->find(iter.first) != interfaceSymbols->end()) {
                return true;
            }
        }
        if(ss->superScope != nullptr) 
            return IsEquivalentTo(ss->superScope);
    }
    return false;
}

std::list<std::string>* ClassSymbol::getLayOut() {
    if(LayOut == nullptr) {
        stdOutput("hh");
        std::list<std::string>* res = new std::list<std::string>; 
        if(superScope != nullptr) {
            stdOutput("?");
            std::list<std::string>* super = superScope->getLayOut();
            Assert(super != nullptr);
            res->assign(super->begin(), super->end());
        }
        stdOutput("sss");
        int Psize = res->size();
        int index = 0;
        for (auto iter : symbols) {
            stdOutput(iter.first);
            if(dynamic_cast<FunctionSymbol*>(iter.second) == nullptr) {
                std::string varName = iter.first;
                auto oldIter = std::find(res->begin(), res->end(), varName);
                if(oldIter == res->end()) {
                    index += 1;
                    iter.second->setInsertionOrderNumber(Psize + index);
                    res->push_back(varName);
                }
                else {
                    iter.second->setInsertionOrderNumber(std::distance(res->begin(), oldIter));
                }
            }
            stdOutput("end");
        }
        LayOut = res;
    }
    stdOutput("eemmmm");
    return LayOut;
}

int ClassSymbol::getSize() {
    int res = 0;
    if(superScope != nullptr) {
        res += superScope->getSize();
    }
    for (auto iter : symbols) {
        if(dynamic_cast<FunctionSymbol*>(iter.second) == nullptr) {
            res += 1;
        }
    }
    return res;
}

std::list<std::string>* ClassSymbol::getVTable() {
    if(VTable == nullptr) {
        std::list<std::string>* res = new std::list<std::string>;
        if(superScope != nullptr) {
            std::list<std::string>* super = superScope->getVTable();
            res->assign(super->begin(), super->end());
        }
        int Psize = res->size();
        int index = 0;
        for (auto iter : symbols) {
            if(dynamic_cast<FunctionSymbol*>(iter.second) != nullptr) {
                std::string fnName = iter.first;
                if(superScope != nullptr) {
                    fnName = "_" + superScope->Symbol::getName() + "." + fnName;
                }
                auto oldIter = std::find(res->begin(), res->end(), fnName);
                std::string label = "_" + Symbol::getName() + "." + iter.first;
                if(oldIter == res->end()) {
                    index += 1;
                    iter.second->setInsertionOrderNumber(Psize + index);
                    res->push_back(label);
                }
                else {
                    iter.second->setInsertionOrderNumber(std::distance(res->begin(), oldIter));
                    *oldIter = label;
                }
            }
        }
        VTable = res;
    }
    return VTable;
}
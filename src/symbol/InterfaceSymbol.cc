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

void InterfaceSymbol::PrintSymbolTable(TextTable* tt, std::string scopeName) {
    bool ff = false;
    if(tt == nullptr) {
        ff = true;
        tt = new TextTable('-', '|', '+' );
        tt->setHead("Interface " + scopeName);
        tt->add("Line Number");
        tt->add("Identifier");
        tt->add("Type");
        tt->endOfRow();
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
        tt->endOfRow();
    }
    if(ff)
        std:cout << *tt << std::endl;
}

bool InterfaceSymbol::IsEquivalentTo(SymbolType * type) {
    stdOutput("111");
    if(type->name == "null") return true;
    ClassSymbol* ss = dynamic_cast<ClassSymbol*>(type);
    InterfaceSymbol* si = dynamic_cast<InterfaceSymbol*>(type);
    if(ss == nullptr && si == nullptr) return false;
    if(ss != nullptr) {
        stdOutput("222");
        std::map<std::string, InterfaceSymbol*>* t = ss->getAllInterfaces();
        if(t->find(Symbol::name) != t->end()) {
            return true;
        }
    }
    if(si != nullptr) {
        if(Symbol::name == si->Symbol::getName()) {
            return true;
        }
    }
    return false;
}
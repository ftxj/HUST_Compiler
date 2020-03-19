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

void FunctionSymbol::PrintSymbolTable(TextTable* tt, std::string scopeName) {
    bool ff = false;
    if(tt == nullptr) {
        ff = true;
        tt = new TextTable('-', '|', '+' );
        tt->setHead("Function " + scopeName);
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
    int i = 0;
    for(auto iter : nestedScopes) {
        ++i;
        iter->PrintSymbolTable(tt, scopeName + " Block " + std::to_string(i));
    }
    if(ff)
        std:cout << *tt << std::endl;
}
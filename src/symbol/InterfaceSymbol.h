#ifndef __INTERFACE_SYMBOL_H__
#define __INTERFACE_SYMBOL_H__
#include "../symbol/Symbol.h"
#include "../symbol/Scope.h"
#include "../symbol/SymbolType.h"
#include "../symbol/FunctionSymbol.h"
#include <map>
#include <list>
class TextTable;
class InterfaceSymbol : public Symbol, public Scope, public SymbolType {
    public:
        InterfaceSymbol(std::string name) : Symbol(name) , SymbolType("Interface") {}
        std::list<FunctionSymbol*>* getAllMethods(){
            std::list<FunctionSymbol*>* res = new std::list<FunctionSymbol*>;
            for(auto& iter : symbols) {
                FunctionSymbol* tt = dynamic_cast<FunctionSymbol*>(iter.second);
                res->push_back(tt);
            }
            return res;
        }
        void PrintSymbolTable(TextTable* tt, std::string scopeName);
        
        bool IsEquivalentTo(SymbolType * type);
        SymbolType* getType() {
            return this;
        }
		std::string getTableName() {
			return Symbol::getName() + "(interface)";
		}
};
#endif
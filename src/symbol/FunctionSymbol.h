#ifndef __FunctionSymbol_H__
#define __FunctionSymbol_H__
#include "../symbol/Symbol.h"
#include "../symbol/Scope.h"
#include "../symbol/LocalScope.h"
#include "../tools/utility.h"
class TextTable;
class FunctionSymbol : public Symbol, public Scope, public SymbolType {
	protected:
		SymbolType* returnType;
		std::list<SymbolType*>* argumentTypes;
	public:
		FunctionSymbol(std::string name) : 
			Symbol(name), SymbolType("function"), returnType(nullptr), argumentTypes(new std::list<SymbolType*>){}
		FunctionSymbol(std::string name, SymbolType* rType, std::list<SymbolType*>* argsType)  :  
			Symbol(name), SymbolType("function"), returnType(rType), argumentTypes(argsType){}
		
		void addArgType(SymbolType* s) {
			argumentTypes->push_back(s);
		}

		bool IsEquivalentTo(SymbolType* type) {
			FunctionSymbol* fnc = dynamic_cast<FunctionSymbol*>(type);
			if(fnc == nullptr) return false;
			if(Symbol::name != fnc->Symbol::name) {
				return false;
			}
			if(!returnType->IsEquivalentTo(fnc->returnType)) {
				return false;
			}
			if(fnc->getNumberOfParameters() != getNumberOfParameters()) {
				return false;
			}
			std::list<SymbolType*>* ttype = fnc->getArgumentTypes();
			auto given = ttype->begin();
			auto expected = argumentTypes->begin();
			for(;given != ttype->end(); ++given, ++expected) {
				if(!(*expected)->IsEquivalentTo(*given)) {
					return false;
				}
			}
			return true;
		}
		
		int getNumberOfParameters() {
			return argumentTypes->size();
		}
		SymbolType* getType() {
			return this;
		}
		std::string getName() {
			return Symbol::getName();
		}
		int getTypeIndex() {
			return -1; 
		}
		SymbolType* getReturnType(){
			return returnType;
		}
		void setReturnType(SymbolType* ss){
			returnType = ss;
		}
		std::list<SymbolType*>* getArgumentTypes() {
			return argumentTypes;
		}
		std::string getTableName() {
			std::string re = returnType->getTableName();
			std::list<std::string> argnameList; 
			for(auto iter : *argumentTypes) {
				if(iter == nullptr) 
					argnameList.push_back("error");
				else 
					argnameList.push_back(iter->getTableName());
			}
			std::string res;
			res += "(*" + re +")(";
			for(auto iter : argnameList) {
				res += iter;
				res += ",";
			}
			if(res[res.length() - 1] == ',') res[res.length() - 1] = ')';
			else res += ")";
			return res;
		}
		void PrintSymbolTable(TextTable* tt, std::string scopeName);
};
#endif
#ifndef __ClassSymbol_H__
#define __ClassSymbol_H__
#include "../symbol/Symbol.h"
#include "../symbol/Scope.h"
#include "../symbol/SymbolType.h"
#include "../symbol/InterfaceSymbol.h"
#include "../tools/utility.h"
#include <map>
class TextTable;
class ClassSymbol : public Symbol, public Scope, public SymbolType {
	protected:
		std::list<std::string>* VTable;
		std::list<std::string>* LayOut;
		std::string superClassName;
		ClassSymbol* superScope;
		std::map<std::string, InterfaceSymbol*>* interfaceSymbols;
	public:
		int size = 0;
		ClassSymbol(std::string name) : Symbol(name), SymbolType("class"), VTable(nullptr), LayOut(nullptr),
			superClassName(""), superScope(nullptr), interfaceSymbols(new std::map<std::string, InterfaceSymbol*>) {}

		ClassSymbol(std::string name, Scope* parent) : 
			Symbol(name), Scope(parent), SymbolType("class"), VTable(nullptr), LayOut(nullptr),
			superClassName(""), superScope(nullptr), interfaceSymbols(new std::map<std::string, InterfaceSymbol*>) {}
		
		std::list<std::string>* getVTable();
		void setSuperClass(std::string super_name, ClassSymbol* super_scope) {
			superClassName = super_name;
			superScope = super_scope;
		}
		
		std::list<std::string>* getLayOut();

		int getSize();

        bool IsEquivalentTo(SymbolType * type);

		ClassSymbol* getSuperClassScope() {
			return superScope;
		}
		
		SymbolType* getType() {
			return this;
		}

		FunctionSymbol* getMemberFunction(FunctionSymbol* ft) {
			Symbol* sym = getMemberSymbol(ft->getName());
			return dynamic_cast<FunctionSymbol*>(sym);
		}

		std::map<std::string, InterfaceSymbol*>* getAllInterfaces() {
			std::map<std::string, InterfaceSymbol*>* tt = new std::map<std::string, InterfaceSymbol*>(*interfaceSymbols);
			if(superScope != nullptr) {
				std::map<std::string, InterfaceSymbol*>* su = superScope->getAllInterfaces();
				tt->insert(su->begin(), su->end());
			}
			return tt;
		}

		InterfaceSymbol* addInterfaces(std::string interface_name, InterfaceSymbol* interface_sym) {
			if(interfaceSymbols->find(interface_name) != interfaceSymbols->end()) {
				Symbol* res = interfaceSymbols->find(interface_name)->second;
				return dynamic_cast<InterfaceSymbol*>(res);
			}
			(*interfaceSymbols)[interface_name] = interface_sym;
			return nullptr;
		}
		
		Symbol* getSymbol(std::string name, bool resolve) {
			Symbol* res = getMemberSymbol(name);
			if (res != nullptr) {
				return res;
			}
			if(resolve) {
				Scope* parent = getParentScope();
				if (parent != nullptr) 
					return parent->getSymbol(name, resolve);
			}
			return nullptr;
		}

		Symbol* getMemberSymbol(std::string name) {
			Symbol* s = Scope::getSymbol(name, false);
			if (s != nullptr) {
				return s;
			}
			// walk superclass chain
			ClassSymbol* super = getSuperClassScope();
			while(super != nullptr) {
				if((s = super->getMemberSymbol(name)) != nullptr) {
					return s;
				}
				super = super->getSuperClassScope();
			}
			return nullptr;
		}

		ClassSymbol* getClassSymbol() {
			return this;
		}
		
		std::string getTableName() {
			return Symbol::getName() + "(class)";
		}

		void PrintSymbolTable(TextTable* tt, std::string scopeName);
};
#endif
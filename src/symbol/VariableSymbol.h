#ifndef __VariableSymbol_H__
#define __VariableSymbol_H__
#include "../symbol/Symbol.h"
class SymbolType;
class VariableSymbol : public Symbol {
	public:
		VariableSymbol(std::string name) : Symbol(name) {}
};
#endif
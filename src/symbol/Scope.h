#ifndef __Semantic_Scope_H__
#define __Semantic_Scope_H__
#include <map>
#include <list>
#include <utility>
#include <string>
class ClassSymbol;
class InterfaceSymbol;
class FunctionSymbol;
class Symbol;
class TextTable;

class Scope {
    int order;
    int InsertOrder;
    int fnInsertOrder;
	protected:
        bool print = false;
        Scope* parent;
	    std::map<std::string, Symbol*> symbols;
        std::list<std::pair<std::string, int>> orderList;
	    std::list<Scope*> nestedScopes;
        bool isLoop;
        bool isFn;
	public:
        Scope();
        Scope(Scope* p);
    public:
        void setParentScope(Scope* parent);
        int getFunNum() {return fnInsertOrder;}
        Scope* getParentScope();
        Scope* getLoopedScope();
	    std::map<std::string, Symbol*> getMembers();
        void setLoop(bool b);
        void addNested(Scope* );
        Scope* getNested() {return *(nestedScopes.begin());}
    public:
        void setSuperFnNum(int num);
    	Symbol* addSymbol(Symbol* sym);
        virtual Symbol* getSymbol(std::string name, bool resolve);
        virtual FunctionSymbol* getFncScope();
        FunctionSymbol* getFncSymbol(std::string name);
        virtual ClassSymbol* getClassScope();
        ClassSymbol* getClassSymbol(std::string name);
        InterfaceSymbol* getInterfaceSymbol(std::string name);
        virtual void PrintSymbolTable(TextTable* tt, std::string scopeName);
};
#endif
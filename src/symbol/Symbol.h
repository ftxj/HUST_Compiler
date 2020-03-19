#ifndef __Symbol_T__
#define __Symbol_T__
#include "../symbol/SymbolType.h"
#include <string>
class Scope;
class Node;

class Symbol {
	protected:
        std::string name;   		        // All symbols at least have a name
        SymbolType* type;				    // cava is statically typed, so all symbols have a type
        Scope* scope;      		            // All symbols know what scope contains them.
        Node* defNode;                      // points at definition node in tree
        int lexicalOrder;                   // order seen or insertion order from 0
    public:
	    Symbol(std::string s) : name(s) {}
        Symbol(std::string s, SymbolType* t) : name(s), type(t) {}
	    std::string getName() { 
            return name; 
        }
	    Scope* getScope() {
            return scope; 
        }
	    void setScope(Scope* scope) { 
            this->scope = scope; 
        }
	    virtual SymbolType* getType() { 
            return type; 
        }
	    void setType(SymbolType* type) { 
            this->type = type; 
        }
	    void setASTNode(Node* defNode) {
		    this->defNode = defNode;
	    }
        Node* getAstNode() {
		    return defNode;
	    }
	    int getInsertionOrderNumber() {
		    return lexicalOrder;
        }
	    void setInsertionOrderNumber(int i) {
		    this->lexicalOrder = i;
	    }
    public:
        std::string toString() {
            return "";
        }
        friend class InterfaceSymbol;
};
#endif
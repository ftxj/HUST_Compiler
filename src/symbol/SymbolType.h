#ifndef __SymbolType__H__
#define __SymbolType__H__
#include <string>
class Node;
class SymbolType {
    protected:
        std::string name = "";
        Node* node;
    public:
        SymbolType(std::string s) : name(s) {}
        SymbolType(std::string s, Node* n) : name(s), node(n) {}
        void setAstNode(Node* s);
        Node* getAstNode();
        bool isArray();
        bool isClass();
        virtual std::string getName();
        virtual bool IsEquivalentTo(SymbolType *);
        virtual int getTypeIndex();
        virtual std::string getTableName();
        friend class ClassSymbol;
        friend class InterfaceSymbol;
};
#endif
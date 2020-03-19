#ifndef __H_ast__
#define __H_ast__
#include "../tools/location.h" // for yyltype
#include "../generate/codegen.h"
#include <iostream>
#include <string>
using namespace std;
class Handle;
class Node {
    public:
        yyltype * location;
        Location* declL;
        Node* parent;
        bool is_sem;    
    public:
        Node(yyltype loc);
        Node();
        virtual ~Node();
        Location* getVarLocation() {return declL;}
		void setVarLocation(Location* l) { declL = l;}
        yyltype* GetLocation();
        Node* GetParent();
        void SetParent(Node *p);
        bool getIsSematicFinished();
        void setSem();
        virtual std::string GetPrintNameForNode() = 0;    
        void PrintAST(int indentLevel, std::string label = ""); 
        virtual void PrintChildren(int indentLevel)  {}
};

class Identifier : public Node  {
    public:
        std::string name;
    public:
        Identifier(yyltype loc, std::string name);
        std::string getName();

        std::string GetPrintNameForNode()   { return "Identifier"; }
        void PrintChildren(int indentLevel);
        friend std::ostream& operator<<(std::ostream& out, Identifier *id) { return out << id->name; }
};

class Error : public Node  {
    public:
        Error();
        std::string GetPrintNameForNode()   { return "Error"; }
};
#endif
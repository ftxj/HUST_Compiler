#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf

void Node::PrintAST(int indentLevel, std::string label) { 
    const int numSpaces = 3;
	std::string space = "   ";
	std::cout << std::endl;
    if (GetLocation()){
		printf("%*d", numSpaces, GetLocation()->first_line);
	}
    else {
		printf("%*s", numSpaces, "");
	} 
	printf("%*s", indentLevel*numSpaces, "");
	cout << label << GetPrintNameForNode() << ": ";
   	PrintChildren(indentLevel);
}

Node::Node(yyltype loc)  {
	location = new yyltype(loc);
	parent = NULL;
	is_sem = false;
	declL = nullptr;
}

Node::Node()  {
	declL = nullptr;
	location = NULL;
	parent = NULL;
	is_sem = false;
}

Node::~Node() {

}

yyltype* Node::GetLocation() {
	return location;
}

Node* Node::GetParent() {
	return parent;
}

void Node::SetParent(Node *p) {
	parent = p;
}

bool Node::getIsSematicFinished() {
	return is_sem;
}

void Node::setSem() {
	is_sem = true;
}

Identifier::Identifier(yyltype loc, std::string n) : Node(loc) {
	name = n;
}

void Identifier::PrintChildren(int indentLevel) {
    cout << this;
}

std::string Identifier::getName() {
	return name;
}

Error::Error() : Node() {

}
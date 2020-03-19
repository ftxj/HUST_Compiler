#include "../symbol/SymbolType.h"
std::string SymbolType::getName() {
    return name;
}
bool SymbolType::IsEquivalentTo(SymbolType *t) {
    return name == t->name; 
}
int SymbolType::getTypeIndex() {
    return 0;
}
void SymbolType::setAstNode(Node* s) {
    node = s;
}
Node* SymbolType::getAstNode() {
    return node;
}

std::string SymbolType::getTableName() {
    return name;
}

bool SymbolType::isArray() {
    return name == "array";
}

bool SymbolType::isClass() {
    return name == "class";
}
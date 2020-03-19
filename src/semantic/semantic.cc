#include "../semantic/semantic.h"
#include "../symbol/Scope.h"
Scope* Semantic::globleScope = new Scope(nullptr);
Scope* Semantic::top_scope = nullptr;

void PrintSymbolTable() {

}
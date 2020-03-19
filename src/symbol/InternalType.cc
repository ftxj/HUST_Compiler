#include "../symbol/InternalType.h"
#include "../symbol/SymbolType.h"
#include "../ast/ast_type.h"
InternalType* InternalType::intType = new InternalType("int", new AstType("int"));
InternalType* InternalType::doubleType = new InternalType("double", new AstType("double"));
InternalType* InternalType::boolType = new InternalType("bool", new AstType("bool"));
InternalType* InternalType::voidType = new InternalType("void", new AstType("void"));
InternalType* InternalType::nullType = new InternalType("null", new AstType("null"));
InternalType* InternalType::stringType = new InternalType("string", new AstType("string"));
InternalType* InternalType::errorType = new InternalType("error", new AstType("error"));
InternalType* InternalType::arrayType = new InternalType("array"); 
InternalType* InternalType::classType = new InternalType("class");
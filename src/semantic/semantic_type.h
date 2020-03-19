#ifndef __SEMANTIC_TYPE_H__
#define __SEMANTIC_TYPE_H__
#include "../semantic/semantic.h"
#include <utility> 
class AstType;
class AstNamedType;
class AstArrayType;
class SymbolType;
class SemanticType : public Semantic {
    public:
        static SymbolType* handle(AstType* );
        static SymbolType* handle(AstNamedType* );
        static SymbolType* handle(AstArrayType* );
};
#endif 
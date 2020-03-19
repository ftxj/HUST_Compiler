#ifndef __SEMANTIC_EXPR_H__
#define __SEMANTIC_EXPR_H__
#include "../semantic/semantic.h"
#include <utility> 
class Expr;
class EmptyExpr;
class IntConstant;
class DoubleConstant;
class BoolConstant;
class StringConstant;
class NullConstant;
class Operator;
class CompoundExpr;
class ArithmeticExpr;
class RelationalExpr;
class EqualityExpr;
class LogicalExpr;
class AssignExpr;
class LValue;
class This;
class ArrayAccess;
class FieldAccess;
class Call;
class NewExpr;
class NewArrayExpr;
class ReadIntegerExpr;
class ReadLineExpr;
class SymbolType;
class SemanticExpr : public Semantic {
    public:
        static std::pair<int, SymbolType*>  handle(Expr*);
        static std::pair<int, SymbolType*>  handle(EmptyExpr*);
        static std::pair<int, SymbolType*>  handle(IntConstant*);
        static std::pair<int, SymbolType*>  handle(DoubleConstant*);
        static std::pair<int, SymbolType*>  handle(BoolConstant*);
        static std::pair<int, SymbolType*>  handle(StringConstant*);
        static std::pair<int, SymbolType*>  handle(NullConstant*);
        static std::pair<int, SymbolType*>  handle(Operator*);
        static std::pair<int, SymbolType*>  handle(CompoundExpr*);
        static std::pair<int, SymbolType*>  handle(ArithmeticExpr*);
        static std::pair<int, SymbolType*>  handle(RelationalExpr*);
        static std::pair<int, SymbolType*>  handle(EqualityExpr*);
        static std::pair<int, SymbolType*>  handle(LogicalExpr*);
        static std::pair<int, SymbolType*>  handle(AssignExpr*);
        static std::pair<int, SymbolType*>  handle(LValue*);
        static std::pair<int, SymbolType*>  handle(This*);
        static std::pair<int, SymbolType*>  handle(ArrayAccess*);
        static std::pair<int, SymbolType*>  handle(FieldAccess*);
        static std::pair<int, SymbolType*>  handle(Call*);
        static std::pair<int, SymbolType*>  handle(NewExpr*);
        static std::pair<int, SymbolType*>  handle(NewArrayExpr*);
        static std::pair<int, SymbolType*>  handle(ReadIntegerExpr*);
        static std::pair<int, SymbolType*>  handle(ReadLineExpr*);
};
#endif 
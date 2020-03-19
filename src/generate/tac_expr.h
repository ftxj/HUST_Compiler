#ifndef __GENERATE_EXPR_H__
#define __GENERATE_EXPR_H__
#include "../generate/tac.h"
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

class Location;
class Scope;

class TACExpr : public TAC {
	public:
		static Location* handle(Expr*, Scope*);
		static Location* handle(EmptyExpr*, Scope*);
		static Location* handle(IntConstant*, Scope*);
		static Location* handle(DoubleConstant*, Scope*);
		static Location* handle(BoolConstant*, Scope*);
		static Location* handle(StringConstant*, Scope*);
		static Location* handle(NullConstant*, Scope*);
		static Location* handle(Operator*, Scope*);
		static Location* handle(CompoundExpr*, Scope*);
		static Location* handle(ArithmeticExpr*, Scope*);
		static Location* handle(RelationalExpr*, Scope*);
		static Location* handle(EqualityExpr*, Scope*);
		static Location* handle(LogicalExpr*, Scope*);
		static Location* handle(AssignExpr*, Scope*);
		static Location* handle(LValue*, Scope*);
		static Location* handle(This*, Scope*);
		static Location* handle(ArrayAccess*, Scope*);
		static Location* handle(FieldAccess*, Scope*);
		static Location* handle(Call*, Scope*);
		static Location* handle(NewExpr*, Scope*);
		static Location* handle(NewArrayExpr*, Scope*);
		static Location* handle(ReadIntegerExpr*, Scope*);
		static Location* handle(ReadLineExpr*, Scope*);
};
#endif 
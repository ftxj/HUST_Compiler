class Node;
class Identifier;
class Error;

class Type;
class NamedType;
class ArrayType;

class Program;
class Stmt;
class StmtBlock;
class ConditionalStmt;
class LoopStmt;
class ForStmt;
class WhileStmt;
class IfStmt;
class BreakStmt;
class ReturnStmt;
class PrintStmt;

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

class Decl;
class VarDecl;
class ClassDecl;
class InterfaceDecl;
class FnDecl;

class Handle {
    public:
        virtual void handle(Node*) = 0;
        virtual void handle(Identifier*) = 0;
        virtual void handle(Error*) = 0;

        virtual void handle(Type*) = 0;
        virtual void handle(NamedType*) = 0;
        virtual void handle(ArrayType*) = 0;

        virtual void handle(Program*) = 0;
        virtual void handle(Stmt*) = 0;
        virtual void handle(StmtBlock*) = 0;
        virtual void handle(ConditionalStmt*) = 0;
        virtual void handle(LoopStmt*) = 0;
        virtual void handle(ForStmt*) = 0;
        virtual void handle(WhileStmt*) = 0;
        virtual void handle(IfStmt*) = 0;
        virtual void handle(BreakStmt*) = 0;
        virtual void handle(ReturnStmt*) = 0;
        virtual void handle(PrintStmt*) = 0;

        virtual void handle(Expr*) = 0;
        virtual void handle(EmptyExpr*) = 0;
        virtual void handle(IntConstant*) = 0;
        virtual void handle(DoubleConstant*) = 0;
        virtual void handle(BoolConstant*) = 0;
        virtual void handle(StringConstant*) = 0;
        virtual void handle(NullConstant*) = 0;
        virtual void handle(Operator*) = 0;
        virtual void handle(CompoundExpr*) = 0;
        virtual void handle(ArithmeticExpr*) = 0;
        virtual void handle(RelationalExpr*) = 0;
        virtual void handle(EqualityExpr*) = 0;
        virtual void handle(LogicalExpr*) = 0;
        virtual void handle(AssignExpr*) = 0;
        virtual void handle(LValue*) = 0;
        virtual void handle(This*) = 0;
        virtual void handle(ArrayAccess*) = 0;
        virtual void handle(FieldAccess*) = 0;
        virtual void handle(Call*) = 0;
        virtual void handle(NewExpr*) = 0;
        virtual void handle(NewArrayExpr*) = 0;
        virtual void handle(ReadIntegerExpr*) = 0;
        virtual void handle(ReadLineExpr*) = 0;

        virtual void handle(Decl*) = 0;
        virtual void handle(VarDecl*) = 0;
        virtual void handle(ClassDecl*) = 0;
        virtual void handle(InterfaceDecl *) = 0;
        virtual void handle(FnDecl *) = 0;
};
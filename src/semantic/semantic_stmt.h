#ifndef __SEMANTIC_STMT_H__
#define __SEMANTIC_STMT_H__
#include "../semantic/semantic.h"
#include <utility> 
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

class SemanticStmt : public Semantic {
    public:
        static void handle(Expr* ); 
        static void handle(Program* );
        static void handle(Stmt* );
        static void handle(StmtBlock* );
        static void handle(ConditionalStmt* );
        static void handle(LoopStmt* );
        static void handle(ForStmt* );
        static void handle(WhileStmt* );
        static void handle(IfStmt* );
        static void handle(BreakStmt* );
        static void handle(ReturnStmt* );
        static void handle(PrintStmt* );
};
#endif 
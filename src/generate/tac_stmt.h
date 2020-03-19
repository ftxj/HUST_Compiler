#ifndef __GENERATE_STMT_H__
#define __GENERATE_STMT_H__
#include <utility> 
#include "../generate/tac.h"
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

class Scope;
class TACStmt : public TAC {
    public:
        static void handle(Expr*, Scope* ); 
        static void handle(Program*, Scope* );
        static void handle(Stmt* , Scope*);
        static void handle(StmtBlock* , Scope*);
        static void handle(ConditionalStmt* , Scope*);
        static void handle(LoopStmt* , Scope*);
        static void handle(ForStmt* , Scope*);
        static void handle(WhileStmt* , Scope*);
        static void handle(IfStmt* , Scope*);
        static void handle(BreakStmt* , Scope*);
        static void handle(ReturnStmt* , Scope*);
        static void handle(PrintStmt* , Scope*);
};
#endif 
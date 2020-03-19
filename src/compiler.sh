#!/bin/sh
set -v on

g++ -std=gnu++11 -g -Wall -Wno-unused -Wno-sign-compare main.cc \
parser/lex.yy.c parser/y.tab.c \
ast/ast_decl.cc ast/ast_expr.cc ast/ast_stmt.cc ast/ast_type.cc ast/ast.cc \
error/errors.cc tools/utility.cc tools/windows.cc tools/TextTable.cc \
semantic/semantic.cc semantic/semantic_decl.cc semantic/semantic_type.cc \
semantic/semantic_stmt.cc semantic/semantic_expr.cc \
symbol/Scope.cc symbol/Generate.cc symbol/SymbolType.cc \
symbol/InternalType.cc symbol/FunctionSymbol.cc symbol/ClassSymbol.cc symbol/InterfaceSymbol.cc \
generate/codegen.cc generate/mips.cc generate/rw.cc \
generate/tac.cc generate/tac_decl.cc generate/tac_expr.cc generate/tac_stmt.cc generate/tac_type.cc \


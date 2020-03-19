
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include "../parser/scanner.h"            // for yylex
#include "../parser/parser.h"
#include "../error/errors.h"
#include "../tools/location.h"
#include "../ast/ast.h"		
#include "../ast/ast_type.h"
#include "../ast/ast_decl.h"
#include "../ast/ast_expr.h"
#include "../ast/ast_stmt.h"
#include "../tools/utility.h"
#include <list>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
void yyerror(const char *msg); // standard error-handling routine


/* Line 189 of yacc.c  */
#line 93 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_Void = 258,
     T_Bool = 259,
     T_Int = 260,
     T_Double = 261,
     T_String = 262,
     T_Class = 263,
     T_LessEqual = 264,
     T_GreaterEqual = 265,
     T_Equal = 266,
     T_NotEqual = 267,
     T_Dims = 268,
     T_And = 269,
     T_Or = 270,
     T_Null = 271,
     T_Extends = 272,
     T_This = 273,
     T_Interface = 274,
     T_Implements = 275,
     T_While = 276,
     T_For = 277,
     T_If = 278,
     T_Else = 279,
     T_Return = 280,
     T_Break = 281,
     T_New = 282,
     T_NewArray = 283,
     T_Print = 284,
     T_ReadInteger = 285,
     T_ReadLine = 286,
     T_Identifier = 287,
     T_StringConstant = 288,
     T_IntConstant = 289,
     T_DoubleConstant = 290,
     T_BoolConstant = 291,
     LOWER_THAN_ELSE = 292
   };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Identifier 287
#define T_StringConstant 288
#define T_IntConstant 289
#define T_DoubleConstant 290
#define T_BoolConstant 291
#define LOWER_THAN_ELSE 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 20 "parser.y"

	char 					identifier[MaxIdentLen + 1];;
	int						integerConstant;
    bool					boolConstant;
    char *					stringConstant;
    double					doubleConstant;

	Identifier*				uIdentifier;
	list<Identifier*>*		uIdentifierList;

	Decl*					uDecl;
	FnDecl*					uFnDecl;	
	VarDecl*				uVarDecl;
	ClassDecl*				uClassDecl;	
	InterfaceDecl*			uIntfDecl;

	list<Decl*>*			uDeclList;
	list<FnDecl*>*			uFnDeclList;
	list<VarDecl*>*			uVarDeclList;
	list<ClassDecl*>*		uClassDeclList;
	list<InterfaceDecl*>*	uInterfaceDeclList;
	
	AstType*				uType;
	AstNamedType*			uNamedType;
	AstArrayType*			uArrayType;

	list<AstNamedType*>*	uNameTypeList;

	Stmt*					uStmt;
	IfStmt*					uIfStmt;
	ForStmt*				uForStmt;
	LoopStmt*				uLoopStmt;
	PrintStmt*				uPrintStmt;
	BreakStmt*				uBreakStmt;
	WhileStmt*				uWhileStmt;
	StmtBlock*				uStmtBlock;
	ReturnStmt*				uReturnStmt;
	ConditionalStmt*		uConditionalStmt;

	list<Stmt*>*			uStmtList;

	Expr*					uExpr;
	EmptyExpr*				uEmptyExpr;
	LValue*					uLValue;
	Call*					uCall;
	IntConstant*			uIntConstant;
	DoubleConstant*			uDoubleConstant;
	BoolConstant*			uBoolConstant;
	StringConstant*			uStringConstant;
	NullConstant*			uNullConstant;
	Operator*				uOperator;
	CompoundExpr*			uCompoundExpr;
	
	list<Expr*>*			uExprList;



/* Line 214 of yacc.c  */
#line 261 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 286 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   408

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  195

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    44,     2,     2,
      50,    51,    42,    40,    52,    41,    46,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
      38,    37,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      21,    24,    26,    28,    30,    32,    34,    37,    44,    51,
      53,    54,    58,    60,    68,    71,    72,    75,    76,    80,
      82,    85,    86,    88,    90,    96,    99,   100,   107,   114,
     119,   122,   123,   126,   127,   130,   132,   134,   136,   138,
     140,   142,   144,   151,   154,   155,   165,   171,   174,   178,
     184,   186,   187,   191,   193,   195,   197,   199,   203,   207,
     211,   215,   219,   223,   226,   230,   234,   238,   242,   246,
     250,   254,   258,   261,   265,   269,   272,   279,   281,   285,
     290,   292,   294,   296,   298,   300,   305,   312,   314,   315,
     319
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    -1,    58,    59,    -1,    59,    -1,
      60,    -1,    63,    -1,    72,    -1,    66,    -1,    61,    49,
      -1,    62,    32,    -1,     5,    -1,     4,    -1,     6,    -1,
       7,    -1,    32,    -1,    62,    13,    -1,    62,    32,    50,
      64,    51,    75,    -1,     3,    32,    50,    64,    51,    75,
      -1,    65,    -1,    -1,    65,    52,    61,    -1,    61,    -1,
       8,    32,    67,    68,    53,    70,    54,    -1,    17,    32,
      -1,    -1,    20,    69,    -1,    -1,    69,    52,    32,    -1,
      32,    -1,    70,    71,    -1,    -1,    60,    -1,    63,    -1,
      19,    32,    53,    73,    54,    -1,    73,    74,    -1,    -1,
      62,    32,    50,    64,    51,    49,    -1,     3,    32,    50,
      64,    51,    49,    -1,    53,    76,    77,    54,    -1,    76,
      60,    -1,    -1,    78,    77,    -1,    -1,    86,    49,    -1,
      79,    -1,    81,    -1,    82,    -1,    83,    -1,    84,    -1,
      75,    -1,    85,    -1,    23,    50,    87,    51,    78,    80,
      -1,    24,    78,    -1,    -1,    22,    50,    86,    49,    87,
      49,    86,    51,    78,    -1,    21,    50,    87,    51,    78,
      -1,    26,    49,    -1,    25,    86,    49,    -1,    29,    50,
      92,    51,    49,    -1,    87,    -1,    -1,    88,    37,    87,
      -1,    89,    -1,    88,    -1,    18,    -1,    90,    -1,    50,
      87,    51,    -1,    87,    40,    87,    -1,    87,    41,    87,
      -1,    87,    42,    87,    -1,    87,    43,    87,    -1,    87,
      44,    87,    -1,    41,    87,    -1,    87,    38,    87,    -1,
      87,     9,    87,    -1,    87,    39,    87,    -1,    87,    10,
      87,    -1,    87,    11,    87,    -1,    87,    12,    87,    -1,
      87,    14,    87,    -1,    87,    15,    87,    -1,    45,    87,
      -1,    30,    50,    51,    -1,    31,    50,    51,    -1,    27,
      32,    -1,    28,    50,    87,    52,    62,    51,    -1,    32,
      -1,    87,    46,    32,    -1,    87,    47,    87,    55,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    16,    -1,
      32,    50,    91,    51,    -1,    87,    46,    32,    50,    91,
      51,    -1,    92,    -1,    -1,    92,    52,    87,    -1,    87,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   146,   146,   163,   164,   167,   168,   169,   170,   176,
     179,   182,   183,   184,   185,   186,   187,   193,   198,   205,
     206,   209,   211,   219,   225,   229,   232,   234,   237,   241,
     246,   247,   250,   251,   257,   263,   267,   270,   274,   280,
     286,   287,   291,   292,   295,   296,   297,   298,   299,   300,
     301,   302,   305,   311,   312,   318,   324,   330,   333,   336,
     342,   343,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   363,   364,   368,   372,
     376,   377,   378,   379,   383,   384,   385,   392,   393,   397,
     400,   401,   402,   403,   404,   407,   411,   417,   418,   421,
     422
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "'='", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "'.'", "'['", "LOWER_THAN_ELSE", "';'",
  "'('", "')'", "','", "'{'", "'}'", "']'", "$accept", "Program",
  "DeclList", "Decl", "VarDecl", "Variable", "Type", "FnDecl", "Parameter",
  "VarList", "ClassDecl", "OptExtends", "OptImplements", "ImplementsList",
  "FieldList", "Field", "IntfDecl", "PrototypeList", "Prototype",
  "StmtBlock", "VarDeclList", "StmtList", "Stmt", "IfStmt", "OptElse",
  "ForStmt", "WhileStmt", "BreakStmt", "ReturnStmt", "PrintStmt",
  "OptExpr", "Expr", "LValue", "Constant", "Call", "Actuals", "ExprList", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    61,    60,    62,
      43,    45,    42,    47,    37,    33,    46,    91,   292,    59,
      40,    41,    44,   123,   125,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      61,    62,    62,    62,    62,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    73,    73,    74,    74,    75,
      76,    76,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    79,    80,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    88,
      89,    89,    89,    89,    89,    90,    90,    91,    91,    92,
      92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     2,     6,     6,     1,
       0,     3,     1,     7,     2,     0,     2,     0,     3,     1,
       2,     0,     1,     1,     5,     2,     0,     6,     6,     4,
       2,     0,     2,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     6,     2,     0,     9,     5,     2,     3,     5,
       1,     0,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     2,     6,     1,     3,     4,
       1,     1,     1,     1,     1,     4,     6,     1,     0,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    11,    13,    14,     0,     0,    15,     0,
       2,     4,     5,     0,     0,     6,     8,     7,     0,    25,
       0,     1,     3,     9,    16,    10,    20,     0,    27,    36,
      20,    22,     0,     0,    19,    24,     0,     0,     0,     0,
      10,     0,     0,    29,    26,    31,     0,    34,     0,    35,
       0,    41,    18,    21,     0,     0,     0,     0,    17,    43,
      28,    23,    32,    33,    30,    20,    20,    94,    65,     0,
       0,     0,    61,     0,     0,     0,     0,     0,     0,    87,
      90,    91,    92,    93,     0,     0,     0,    40,    50,     0,
      43,    45,    46,    47,    48,    49,    51,     0,    60,    64,
      63,    66,     0,     0,     0,    61,     0,    87,     0,    57,
      85,     0,     0,     0,     0,    98,    73,    82,     0,    39,
      42,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,   100,     0,    83,    84,     0,
      97,    67,    75,    77,    78,    79,    80,    81,    74,    76,
      68,    69,    70,    71,    72,    88,     0,    62,    38,    37,
      61,     0,    61,     0,     0,     0,    95,    98,    89,    56,
       0,    54,     0,    59,    99,     0,    61,    61,    52,    86,
      96,     0,    53,    61,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    32,    15,    33,    34,
      16,    28,    37,    44,    55,    64,    17,    38,    49,    88,
      59,    89,    90,    91,   188,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   149,   150
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
     193,   -30,  -155,  -155,  -155,  -155,   -13,    -2,  -155,    22,
     193,  -155,  -155,   -22,    -4,  -155,  -155,  -155,    20,    73,
      40,  -155,  -155,  -155,  -155,    23,   210,    72,    85,  -155,
     210,  -155,     4,    58,    67,  -155,    78,    59,     8,    90,
    -155,    89,   210,  -155,    91,  -155,   114,  -155,    64,  -155,
      89,  -155,  -155,  -155,   115,    60,    99,   104,  -155,    95,
    -155,  -155,  -155,  -155,  -155,   210,   210,  -155,  -155,   107,
     109,   110,   358,   119,   139,   122,   124,   125,   127,   126,
    -155,  -155,  -155,  -155,   358,   358,   358,  -155,  -155,   132,
     334,  -155,  -155,  -155,  -155,  -155,  -155,   153,   292,   170,
    -155,  -155,   159,   160,   358,   358,   358,   163,   179,  -155,
    -155,   358,   358,   178,   188,   358,   211,   -39,   180,  -155,
    -155,  -155,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   358,   358,   358,   358,   198,   358,   358,   195,   201,
     194,   207,   237,  -155,   141,   292,    56,  -155,  -155,   192,
     212,  -155,   227,   227,   277,   277,   302,   302,   227,   227,
     211,   211,   -39,   -39,   -39,   209,   123,   292,  -155,  -155,
      53,   358,    53,   210,   223,   358,  -155,   358,  -155,  -155,
     251,   258,   -10,  -155,   292,   234,   358,    53,  -155,  -155,
    -155,   245,  -155,    53,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,   289,    13,    -5,     0,   250,    -7,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,   -21,
    -155,   218,  -154,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
     -71,   -80,  -155,  -155,  -155,   133,   197
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -62
static const yytype_int16 yytable[] =
{
      14,   108,    18,    24,   116,   117,   118,   135,   136,    24,
      14,    46,     2,     3,     4,     5,   179,    24,   181,    19,
      52,    31,    21,    39,   140,    31,   142,    23,    25,    58,
      20,   144,   145,   192,   141,   145,    40,    53,    48,   194,
       8,   189,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,    14,   166,   167,   102,   103,
      31,    31,    47,     1,     2,     3,     4,     5,    62,    67,
      26,    68,    87,    30,    69,    70,    71,    24,    72,    73,
      74,    75,    76,    77,    78,   107,    80,    81,    82,    83,
      27,   180,     8,    29,    84,   184,    57,   145,    85,     2,
       3,     4,     5,    86,    35,    36,    51,   174,   175,    41,
      43,    67,    45,    68,    61,   191,    69,    70,    71,    42,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   122,   123,   124,   125,    84,   126,   127,   -15,
      85,    50,    51,    54,   -61,    86,    56,    60,    51,    65,
     122,   123,   124,   125,    66,   126,   127,   104,   -15,   105,
     106,   128,   129,   130,   131,   132,   133,   134,   109,   135,
     136,   110,   111,   182,   112,   113,   115,   114,   178,   128,
     129,   130,   131,   132,   133,   134,   119,   135,   136,   122,
     123,   124,   125,   173,   126,   127,     1,     2,     3,     4,
       5,     6,   121,   122,   123,   124,   125,   137,   126,   127,
     138,   139,     7,   115,     2,     3,     4,     5,   128,   129,
     130,   131,   132,   133,   134,     8,   135,   136,   143,   147,
     165,   151,   128,   129,   130,   131,   132,   133,   134,   148,
     135,   136,     8,   176,   168,   170,   122,   123,   124,   125,
     169,   126,   127,   132,   133,   134,   171,   135,   136,   177,
     122,   123,   124,   125,   175,   126,   127,   130,   131,   132,
     133,   134,   183,   135,   136,   128,   129,   130,   131,   132,
     133,   134,   187,   135,   136,   190,   122,   123,   172,   128,
     129,   130,   131,   132,   133,   134,   193,   135,   136,    22,
     186,   122,   123,   124,   125,    63,   126,   127,   120,   146,
     185,   122,   123,   124,   125,   128,   129,   130,   131,   132,
     133,   134,     0,   135,   136,     0,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,   134,     0,   135,   136,
     128,   129,   130,   131,   132,   133,   134,     0,   135,   136,
      67,     0,    68,     0,     0,    69,    70,    71,     0,    72,
      73,    74,    75,    76,    77,    78,   107,    80,    81,    82,
      83,     0,     0,     0,    67,    84,    68,     0,     0,    85,
       0,     0,     0,   -61,    86,    74,    75,    51,    77,    78,
     107,    80,    81,    82,    83,     0,     0,     0,     0,    84,
       0,     0,     0,    85,     0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
       0,    72,    32,    13,    84,    85,    86,    46,    47,    13,
      10,     3,     4,     5,     6,     7,   170,    13,   172,    32,
      41,    26,     0,    30,   104,    30,   106,    49,    32,    50,
      32,   111,   112,   187,   105,   115,    32,    42,    38,   193,
      32,    51,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    55,   136,   137,    65,    66,
      65,    66,    54,     3,     4,     5,     6,     7,    55,    16,
      50,    18,    59,    50,    21,    22,    23,    13,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      17,   171,    32,    53,    41,   175,    32,   177,    45,     4,
       5,     6,     7,    50,    32,    20,    53,    51,    52,    51,
      32,    16,    53,    18,    54,   186,    21,    22,    23,    52,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,     9,    10,    11,    12,    41,    14,    15,    13,
      45,    51,    53,    52,    49,    50,    32,    32,    53,    50,
       9,    10,    11,    12,    50,    14,    15,    50,    32,    50,
      50,    38,    39,    40,    41,    42,    43,    44,    49,    46,
      47,    32,    50,   173,    50,    50,    50,    50,    55,    38,
      39,    40,    41,    42,    43,    44,    54,    46,    47,     9,
      10,    11,    12,    52,    14,    15,     3,     4,     5,     6,
       7,     8,    49,     9,    10,    11,    12,    37,    14,    15,
      51,    51,    19,    50,     4,     5,     6,     7,    38,    39,
      40,    41,    42,    43,    44,    32,    46,    47,    49,    51,
      32,    51,    38,    39,    40,    41,    42,    43,    44,    51,
      46,    47,    32,    51,    49,    51,     9,    10,    11,    12,
      49,    14,    15,    42,    43,    44,    49,    46,    47,    50,
       9,    10,    11,    12,    52,    14,    15,    40,    41,    42,
      43,    44,    49,    46,    47,    38,    39,    40,    41,    42,
      43,    44,    24,    46,    47,    51,     9,    10,    51,    38,
      39,    40,    41,    42,    43,    44,    51,    46,    47,    10,
      49,     9,    10,    11,    12,    55,    14,    15,    90,   112,
     177,     9,    10,    11,    12,    38,    39,    40,    41,    42,
      43,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    46,    47,
      38,    39,    40,    41,    42,    43,    44,    -1,    46,    47,
      16,    -1,    18,    -1,    -1,    21,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    16,    41,    18,    -1,    -1,    45,
      -1,    -1,    -1,    49,    50,    27,    28,    53,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    32,    57,
      58,    59,    60,    61,    62,    63,    66,    72,    32,    32,
      32,     0,    59,    49,    13,    32,    50,    17,    67,    53,
      50,    61,    62,    64,    65,    32,    20,    68,    73,    64,
      32,    51,    52,    32,    69,    53,     3,    54,    62,    74,
      51,    53,    75,    61,    52,    70,    32,    32,    75,    76,
      32,    54,    60,    63,    71,    50,    50,    16,    18,    21,
      22,    23,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    41,    45,    50,    60,    75,    77,
      78,    79,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    64,    64,    50,    50,    50,    32,    86,    49,
      32,    50,    50,    50,    50,    50,    87,    87,    87,    54,
      77,    49,     9,    10,    11,    12,    14,    15,    38,    39,
      40,    41,    42,    43,    44,    46,    47,    37,    51,    51,
      87,    86,    87,    49,    87,    87,    92,    51,    51,    91,
      92,    51,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    32,    87,    87,    49,    49,
      51,    49,    51,    52,    51,    52,    51,    50,    55,    78,
      87,    78,    62,    49,    87,    91,    49,    24,    80,    51,
      51,    86,    78,    51,    78
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    { 
												(yylsp[(1) - (1)]);
												/* 
												* pp2: The @1 is needed to convince 
												* yacc to set up yylloc. You can remove 
												* it once you have other uses of @n 
												*/
												Program *program = new Program((yyvsp[(1) - (1)].uDeclList));
												cout << "semantic analysis" << endl;
												if (ReportError::NumErrors() == 0) 
													program->PrintAST(0);
												program->SemanticAnalysis();
												program->Emit();
												// if no errors, advance to next phase
											}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    {	((yyval.uDeclList) = (yyvsp[(1) - (2)].uDeclList))->push_back((yyvsp[(2) - (2)].uDecl));	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    {	((yyval.uDeclList) = new list<Decl*>)->push_back((yyvsp[(1) - (1)].uDecl));	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    {	(yyval.uDecl) = (yyvsp[(1) - (1)].uVarDecl);	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    {	(yyval.uDecl) = (yyvsp[(1) - (1)].uFnDecl);	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {	(yyval.uDecl) = (yyvsp[(1) - (1)].uIntfDecl);	}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    {	(yyval.uDecl) = (yyvsp[(1) - (1)].uClassDecl);	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    {	(yyval.uVarDecl) = (yyvsp[(1) - (2)].uVarDecl);	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    {	(yyval.uVarDecl) = new VarDecl(new Identifier((yylsp[(2) - (2)]), std::string((yyvsp[(2) - (2)].identifier))), (yyvsp[(1) - (2)].uType));	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    {	(yyval.uType) = AstType::intType;	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {	(yyval.uType) = AstType::boolType;	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    {	(yyval.uType) = AstType::doubleType;	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    {	(yyval.uType) = AstType::stringType;	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    {	(yyval.uType) = new AstNamedType(new Identifier((yylsp[(1) - (1)]), std::string((yyvsp[(1) - (1)].identifier))));	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    {	(yyval.uType) = new AstArrayType(Join((yylsp[(1) - (2)]), (yylsp[(2) - (2)])), (yyvsp[(1) - (2)].uType));	}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    {	
												(yyval.uFnDecl) = new FnDecl(new Identifier((yylsp[(2) - (6)]), std::string((yyvsp[(2) - (6)].identifier))), (yyvsp[(1) - (6)].uType), (yyvsp[(4) - (6)].uVarDeclList));	
												(yyval.uFnDecl)->SetFunctionBody((yyvsp[(6) - (6)].uStmtBlock));
											}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {	
												(yyval.uFnDecl) = new FnDecl(new Identifier((yylsp[(2) - (6)]), std::string((yyvsp[(2) - (6)].identifier))), AstType::voidType, (yyvsp[(4) - (6)].uVarDeclList));
												(yyval.uFnDecl)->SetFunctionBody((yyvsp[(6) - (6)].uStmtBlock));
											}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    {	(yyval.uVarDeclList) = (yyvsp[(1) - (1)].uVarDeclList);	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    {	(yyval.uVarDeclList) = new list<VarDecl*>;	}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    {	((yyval.uVarDeclList) = (yyvsp[(1) - (3)].uVarDeclList))->push_back((yyvsp[(3) - (3)].uVarDecl));	}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    {	((yyval.uVarDeclList) = new list<VarDecl*>)->push_back((yyvsp[(1) - (1)].uVarDecl));	}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    {	
												(yyval.uClassDecl) = new ClassDecl(new Identifier((yylsp[(2) - (7)]), std::string((yyvsp[(2) - (7)].identifier))), (yyvsp[(3) - (7)].uNamedType), (yyvsp[(4) - (7)].uNameTypeList), (yyvsp[(6) - (7)].uDeclList));	
											}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 226 "parser.y"
    {	
												(yyval.uNamedType) = new AstNamedType(new Identifier((yylsp[(2) - (2)]), std::string((yyvsp[(2) - (2)].identifier))));
											}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    {	(yyval.uNamedType) = NULL;	}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    {	(yyval.uNameTypeList) = (yyvsp[(2) - (2)].uNameTypeList);	}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 234 "parser.y"
    {	(yyval.uNameTypeList) = new list<AstNamedType*>;	}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    {	
												((yyval.uNameTypeList) = (yyvsp[(1) - (3)].uNameTypeList))->push_back(new AstNamedType(new Identifier((yylsp[(3) - (3)]), std::string((yyvsp[(3) - (3)].identifier)))));	
											}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    {	
												((yyval.uNameTypeList)= new list<AstNamedType*>)->push_back(new AstNamedType(new Identifier((yylsp[(1) - (1)]), std::string((yyvsp[(1) - (1)].identifier)))));
											}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    {	((yyval.uDeclList) = (yyvsp[(1) - (2)].uDeclList))->push_back((yyvsp[(2) - (2)].uDecl));	}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    {	(yyval.uDeclList) = new list<Decl*>;	}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 250 "parser.y"
    {	(yyval.uDecl) = (yyvsp[(1) - (1)].uVarDecl);	}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {	(yyval.uDecl) = (yyvsp[(1) - (1)].uFnDecl);	}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {	
												(yyval.uIntfDecl) = new InterfaceDecl(new Identifier((yylsp[(2) - (5)]), std::string((yyvsp[(2) - (5)].identifier))), (yyvsp[(4) - (5)].uDeclList));	
											}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 264 "parser.y"
    {
												((yyval.uDeclList) = ((yyvsp[(1) - (2)].uDeclList) == NULL? (new list<Decl*>) : (yyvsp[(1) - (2)].uDeclList)))->push_back((yyvsp[(2) - (2)].uFnDecl));	
											}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    {	(yyval.uDeclList) = new list<Decl*>;	}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {	
												(yyval.uFnDecl) = new FnDecl(new Identifier((yylsp[(2) - (6)]), std::string((yyvsp[(2) - (6)].identifier))), (yyvsp[(1) - (6)].uType), (yyvsp[(4) - (6)].uVarDeclList)); 
											}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    {
												(yyval.uFnDecl) = new FnDecl(new Identifier((yylsp[(2) - (6)]), std::string((yyvsp[(2) - (6)].identifier))), AstType::voidType, (yyvsp[(4) - (6)].uVarDeclList));
											}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 281 "parser.y"
    {
												(yyval.uStmtBlock) = new StmtBlock((yyvsp[(2) - (4)].uVarDeclList), (yyvsp[(3) - (4)].uStmtList));
											}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    {	((yyval.uVarDeclList) = (yyvsp[(1) - (2)].uVarDeclList))->push_back((yyvsp[(2) - (2)].uVarDecl));	}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 287 "parser.y"
    {	(yyval.uVarDeclList) = new list<VarDecl*>;	}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 291 "parser.y"
    {	(yyval.uStmtList) = (yyvsp[(2) - (2)].uStmtList); (yyval.uStmtList)->push_front((yyvsp[(1) - (2)].uStmt));	}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    {	(yyval.uStmtList) = new list<Stmt*>;	}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 295 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (2)].uExpr);	}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uIfStmt);	}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 297 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uForStmt);	}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uWhileStmt);	}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 299 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uBreakStmt);	}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uReturnStmt);	}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uStmtBlock);	}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 302 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(1) - (1)].uPrintStmt);	}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {	
												(yyval.uIfStmt) = new IfStmt((yyvsp[(3) - (6)].uExpr), (yyvsp[(5) - (6)].uStmt), (yyvsp[(6) - (6)].uStmt));
											}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 311 "parser.y"
    {	(yyval.uStmt) = (yyvsp[(2) - (2)].uStmt);	}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 313 "parser.y"
    {	
												(yyval.uStmt) = NULL;	
											}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 319 "parser.y"
    {
												(yyval.uForStmt) = new ForStmt((yyvsp[(3) - (9)].uExpr), (yyvsp[(5) - (9)].uExpr), (yyvsp[(7) - (9)].uExpr), (yyvsp[(9) - (9)].uStmt));
											}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    {
												(yyval.uWhileStmt) = new WhileStmt((yyvsp[(3) - (5)].uExpr), (yyvsp[(5) - (5)].uStmt));
											}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    {	(yyval.uBreakStmt) = new BreakStmt((yylsp[(1) - (2)]));	}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {	(yyval.uReturnStmt) = new ReturnStmt(Join((yylsp[(1) - (3)]), (yylsp[(3) - (3)])), (yyvsp[(2) - (3)].uExpr));	}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    {
												(yyval.uPrintStmt) = new PrintStmt((yyvsp[(3) - (5)].uExprList));
											}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 342 "parser.y"
    {	(yyval.uExpr) = (yyvsp[(1) - (1)].uExpr);	}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    {	(yyval.uExpr) = new EmptyExpr;	}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    {	(yyval.uExpr) = new AssignExpr((yyvsp[(1) - (3)].uLValue), new Operator((yylsp[(2) - (3)]), "="), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 347 "parser.y"
    {	(yyval.uExpr) = (yyvsp[(1) - (1)].uExpr);	}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    {	(yyval.uExpr) = (yyvsp[(1) - (1)].uLValue);	}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 349 "parser.y"
    {	(yyval.uExpr) = new This((yylsp[(1) - (1)]));	}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 350 "parser.y"
    {	(yyval.uExpr) = (yyvsp[(1) - (1)].uCall);	}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 351 "parser.y"
    {	(yyval.uExpr) = (yyvsp[(2) - (3)].uExpr); /* may be a problem */	}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 352 "parser.y"
    {	(yyval.uExpr) = new ArithmeticExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "+"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    {	(yyval.uExpr) = new ArithmeticExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "-"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 354 "parser.y"
    {	(yyval.uExpr) = new ArithmeticExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "*"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 355 "parser.y"
    {	(yyval.uExpr) = new ArithmeticExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "/"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 356 "parser.y"
    {	(yyval.uExpr) = new ArithmeticExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "%"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 357 "parser.y"
    {	(yyval.uExpr) = new ArithmeticExpr(new Operator((yylsp[(1) - (2)]), "-"), (yyvsp[(2) - (2)].uExpr));	}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 358 "parser.y"
    { 	(yyval.uExpr) = new RelationalExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "<"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {
												(yyval.uExpr) = new RelationalExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "<="), (yyvsp[(3) - (3)].uExpr));
											}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 363 "parser.y"
    {	(yyval.uExpr) = new RelationalExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), ">"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 365 "parser.y"
    {
												(yyval.uExpr) = new RelationalExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), ">="), (yyvsp[(3) - (3)].uExpr));
											}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    {
												(yyval.uExpr) = new EqualityExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "=="), (yyvsp[(3) - (3)].uExpr));
											}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 373 "parser.y"
    {
												(yyval.uExpr) = new EqualityExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "!="), (yyvsp[(3) - (3)].uExpr));
											}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    {	(yyval.uExpr) = new LogicalExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "&&"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 377 "parser.y"
    {	(yyval.uExpr) = new LogicalExpr((yyvsp[(1) - (3)].uExpr), new Operator((yylsp[(2) - (3)]), "||"), (yyvsp[(3) - (3)].uExpr));	}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {	(yyval.uExpr) = new LogicalExpr(new Operator((yylsp[(1) - (2)]), "!"), (yyvsp[(2) - (2)].uExpr));	}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    {
												(yyval.uExpr) = new ReadIntegerExpr(Join((yylsp[(1) - (3)]),(yylsp[(3) - (3)])));
											}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {	(yyval.uExpr) = new ReadLineExpr(Join((yylsp[(1) - (3)]),(yylsp[(3) - (3)])));	}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 384 "parser.y"
    {	(yyval.uExpr) = new NewExpr(Join((yylsp[(1) - (2)]), (yylsp[(2) - (2)])), new AstNamedType(new Identifier((yylsp[(2) - (2)]), std::string((yyvsp[(2) - (2)].identifier)))));	}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 386 "parser.y"
    {
												(yyval.uExpr) = new NewArrayExpr(Join((yylsp[(1) - (6)]), (yylsp[(6) - (6)])), (yyvsp[(3) - (6)].uExpr), (yyvsp[(5) - (6)].uType));
											}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 392 "parser.y"
    {	(yyval.uLValue) = new FieldAccess (NULL, new Identifier((yylsp[(1) - (1)]), std::string((yyvsp[(1) - (1)].identifier)))); }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 394 "parser.y"
    {
												(yyval.uLValue) = new FieldAccess ((yyvsp[(1) - (3)].uExpr), new Identifier((yylsp[(3) - (3)]), std::string((yyvsp[(3) - (3)].identifier))));
											}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    {	(yyval.uLValue) = new ArrayAccess (Join(*((yyvsp[(1) - (4)].uExpr)->GetLocation()), (yylsp[(4) - (4)])), (yyvsp[(1) - (4)].uExpr), (yyvsp[(3) - (4)].uExpr));	}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 400 "parser.y"
    {	printf("%s\n", (yyvsp[(1) - (1)].stringConstant)); std::cout << std::string((yyvsp[(1) - (1)].stringConstant)) << std::endl; (yyval.uExpr) = new StringConstant ((yylsp[(1) - (1)]), std::string((yyvsp[(1) - (1)].stringConstant)));	}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 401 "parser.y"
    {	(yyval.uExpr) = new IntConstant ((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].integerConstant));	}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 402 "parser.y"
    {	(yyval.uExpr) = new DoubleConstant ((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].doubleConstant));	}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 403 "parser.y"
    {	(yyval.uExpr) = new BoolConstant ((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].boolConstant));	}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 404 "parser.y"
    {	(yyval.uExpr) = new NullConstant ((yylsp[(1) - (1)]));	}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 408 "parser.y"
    {
												(yyval.uCall) = new Call (Join((yylsp[(1) - (4)]), (yylsp[(4) - (4)])), NULL, new Identifier((yylsp[(1) - (4)]), std::string((yyvsp[(1) - (4)].identifier))), (yyvsp[(3) - (4)].uExprList));
											}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 412 "parser.y"
    {
												(yyval.uCall) = new Call (Join(*((yyvsp[(1) - (6)].uExpr)->GetLocation()), (yylsp[(4) - (6)])), (yyvsp[(1) - (6)].uExpr), new Identifier((yylsp[(3) - (6)]), std::string((yyvsp[(3) - (6)].identifier))), (yyvsp[(5) - (6)].uExprList));
											}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {	(yyval.uExprList) = (yyvsp[(1) - (1)].uExprList);	}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 418 "parser.y"
    {	(yyval.uExprList) = new list<Expr*>;	}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 421 "parser.y"
    {	((yyval.uExprList) = (yyvsp[(1) - (3)].uExprList))->push_back((yyvsp[(3) - (3)].uExpr));	}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 422 "parser.y"
    {	((yyval.uExprList) = new list<Expr*>)->push_back((yyvsp[(1) - (1)].uExpr));	}
    break;



/* Line 1455 of yacc.c  */
#line 2496 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 425 "parser.y"


/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}


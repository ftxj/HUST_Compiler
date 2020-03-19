%{
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
void yyerror(const char *msg);
%}

%union {
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
}

%token	T_Void T_Bool T_Int T_Double T_String T_Class 
%token	T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token	T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token	T_While T_For T_If T_Else T_Return T_Break
%token	T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token	<identifier> T_Identifier
%token	<stringConstant> T_StringConstant 
%token	<integerConstant> T_IntConstant
%token	<doubleConstant> T_DoubleConstant
%token	<boolConstant> T_BoolConstant

%left		'='
%left		T_Or T_And
%left		T_Equal T_NotEqual
%left		'<' '>' T_GreaterEqual T_LessEqual
%left		'+' '-'
%left		'*' '/' '%'
%left		'!'
%nonassoc	'.' '['
/* the method to solve if/else stmt conflict in book : flex and bison */
%nonassoc	LOWER_THAN_ELSE
%nonassoc	T_Else

/* Non-terminal types*/
%type	<uDecl>					Decl Field
%type	<uFnDecl>				FnDecl Prototype
%type	<uVarDecl>				VarDecl Variable
%type	<uIntfDecl>				IntfDecl
%type	<uClassDecl>			ClassDecl

%type	<uDeclList>				DeclList FieldList PrototypeList
%type	<uVarDeclList>			Parameter VarList VarDeclList

%type	<uType>					Type
%type	<uNamedType>			OptExtends

%type	<uNameTypeList>			OptImplements ImplementsList

%type	<uStmt>					Stmt OptElse
%type	<uIfStmt>				IfStmt
%type	<uForStmt>				ForStmt
%type	<uPrintStmt>			PrintStmt
%type	<uBreakStmt>			BreakStmt
%type	<uWhileStmt>			WhileStmt
%type	<uStmtBlock>			StmtBlock
%type	<uReturnStmt>			ReturnStmt

%type	<uStmtList>				StmtList

%type	<uExpr>					Expr OptExpr Constant
%type	<uLValue>				LValue
%type	<uCall>					Call;
%type	<uExprList>				ExprList Actuals


%%
Program			:		DeclList			{ 
												@1;
												Program *program = new Program($1);
												cout << "semantic analysis" << endl;
												if (ReportError::NumErrors() == 0) {
													program->PrintAST(0);
													program->SemanticAnalysis();
													program->Emit();
												}
											} 
												
		  		;

DeclList		:		DeclList Decl		{	($$ = $1)->push_back($2);	}
				|		Decl				{	($$ = new list<Decl*>)->push_back($1);	}
				;

Decl			:		VarDecl				{	$$ = $1;	}
				|		FnDecl				{	$$ = $1;	}
				|		IntfDecl			{	$$ = $1;	}
				|		ClassDecl			{	$$ = $1;	}
				;
				



VarDecl			:		Variable ';'		{	$$ = $1;	}
				;

Variable		:		Type T_Identifier	{	$$ = new VarDecl(new Identifier(@2, std::string($2)), $1);	}
				;

Type			:		T_Int				{	$$ = AstType::intType;	}
				|		T_Bool				{	$$ = AstType::boolType;	}
				|		T_Double			{	$$ = AstType::doubleType;	}
				|		T_String			{	$$ = AstType::stringType;	}
				|		T_Identifier		{	$$ = new AstNamedType(new Identifier(@1, std::string($1)));	}
				|		Type T_Dims			{	$$ = new AstArrayType(Join(@1, @2), $1);	}
				;




FnDecl			:		Type T_Identifier '(' Parameter ')' StmtBlock		
											{	
												$$ = new FnDecl(new Identifier(@2, std::string($2)), $1, $4);	
												$$->SetFunctionBody($6);
											}
				|		T_Void  T_Identifier '(' Parameter ')' StmtBlock
											{	
												$$ = new FnDecl(new Identifier(@2, std::string($2)), AstType::voidType, $4);
												$$->SetFunctionBody($6);
											}
				;

Parameter		:		VarList				{	$$ = $1;	}
				|		/* empty */			{	$$ = new list<VarDecl*>;	}
				;

VarList			:		VarList ',' Variable
											{	($$ = $1)->push_back($3);	}
				|		Variable
											{	($$ = new list<VarDecl*>)->push_back($1);	}
				;





ClassDecl		:		T_Class T_Identifier OptExtends OptImplements '{' FieldList '}'
											{	
												$$ = new ClassDecl(new Identifier(@2, std::string($2)), $3, $4, $6);	
											}
				;

OptExtends		:		T_Extends T_Identifier
											{	
												$$ = new AstNamedType(new Identifier(@2, std::string($2)));
											}
				|		/* empty */			{	$$ = NULL;	}
				;

OptImplements	:		T_Implements ImplementsList
											{	$$ = $2;	}
				|		/* empty */			{	$$ = new list<AstNamedType*>;	}
				;

ImplementsList	:		ImplementsList ',' T_Identifier
											{	
												($$ = $1)->push_back(new AstNamedType(new Identifier(@3, std::string($3))));	
											}
				|		T_Identifier		{	
												($$= new list<AstNamedType*>)->push_back(new AstNamedType(new Identifier(@1, std::string($1))));
											}
				;

FieldList		:		FieldList Field		{	($$ = $1)->push_back($2);	}
				|		/* empty */			{	$$ = new list<Decl*>;	}
				;

Field			:		VarDecl				{	$$ = $1;	}
				|		FnDecl				{	$$ = $1;	}
				;




IntfDecl		:		T_Interface T_Identifier '{' PrototypeList '}'
											{	
												$$ = new InterfaceDecl(new Identifier(@2, std::string($2)), $4);	
											}
				;

PrototypeList	:		PrototypeList Prototype
											{
												($$ = ($1 == NULL? (new list<Decl*>) : $1))->push_back($2);	
											}
				|		/* empty */			{	$$ = new list<Decl*>;	}
				;

Prototype		:		Type T_Identifier '(' Parameter ')' ';'
											{	
												$$ = new FnDecl(new Identifier(@2, std::string($2)), $1, $4); 
											}
				|		T_Void T_Identifier '(' Parameter ')' ';'
											{
												$$ = new FnDecl(new Identifier(@2, std::string($2)), AstType::voidType, $4);
											}
				;
/* have some problem */
StmtBlock		:		'{' VarDeclList StmtList '}'
											{
												$$ = new StmtBlock($2, $3);
											}
				;

VarDeclList		:		VarDeclList VarDecl	{	($$ = $1)->push_back($2);	}
				|		/* empty */			{	$$ = new list<VarDecl*>;	}
				;

/* have a problem in StmtList : StmtList Stmt*/
StmtList		:		Stmt StmtList 		{	$$ = $2; $$->push_front($1);	}
				|		/* empty */			{	$$ = new list<Stmt*>;	}
				;
/* solve if/if/else conflict */
Stmt			:		OptExpr ';'			{	$$ = $1;	}
				|		IfStmt				{	$$ = $1;	}
				|		ForStmt				{	$$ = $1;	}
				|		WhileStmt			{	$$ = $1;	}
				|		BreakStmt			{	$$ = $1;	}
				|		ReturnStmt			{	$$ = $1;	}
				|		StmtBlock			{	$$ = $1;	}
				|		PrintStmt			{	$$ = $1;	}
				;

IfStmt			:		T_If '(' Expr ')' Stmt OptElse
											{	
												$$ = new IfStmt($3, $5, $6);
											}
				;

OptElse			:		T_Else Stmt			{	$$ = $2;	}
				|		/* empty */	 %prec LOWER_THAN_ELSE 
											{	
												$$ = NULL;	
											}
				;

ForStmt			:		T_For '(' OptExpr ';' Expr ';' OptExpr ')' Stmt
											{
												$$ = new ForStmt($3, $5, $7, $9);
											}
				;

WhileStmt		:		T_While '(' Expr ')' Stmt
											{
												$$ = new WhileStmt($3, $5);
											}
				;

BreakStmt		:		T_Break ';'			{	$$ = new BreakStmt(@1);	}
				;

ReturnStmt		:		T_Return OptExpr ';'{	$$ = new ReturnStmt(Join(@1, @3), $2);	}
				;

PrintStmt		:		T_Print	'(' ExprList ')' ';'
											{
												$$ = new PrintStmt($3);
											}
				;

OptExpr			:		Expr				{	$$ = $1;	}
				|		/* empty */			{	$$ = new EmptyExpr;	}
				;

Expr			:		LValue '=' Expr		{	$$ = new AssignExpr($1, new Operator(@2, "="), $3);	}
				|		Constant			{	$$ = $1;	}
				|		LValue				{	$$ = $1;	}
				|		T_This				{	$$ = new This(@1);	}
				|		Call				{	$$ = $1;	}
				|		'(' Expr ')'		{	$$ = $2; /* may be a problem */	}
				|		Expr '+' Expr		{	$$ = new ArithmeticExpr($1, new Operator(@2, "+"), $3);	}
				|		Expr '-' Expr		{	$$ = new ArithmeticExpr($1, new Operator(@2, "-"), $3);	}
				|		Expr '*' Expr		{	$$ = new ArithmeticExpr($1, new Operator(@2, "*"), $3);	}
				|		Expr '/' Expr		{	$$ = new ArithmeticExpr($1, new Operator(@2, "/"), $3);	}
				|		Expr '%' Expr		{	$$ = new ArithmeticExpr($1, new Operator(@2, "%"), $3);	}
				|		'-' Expr			{	$$ = new ArithmeticExpr(new Operator(@1, "-"), $2);	}
				|		Expr '<' Expr		{ 	$$ = new RelationalExpr($1, new Operator(@2, "<"), $3);	}
				|		Expr T_LessEqual Expr
											{
												$$ = new RelationalExpr($1, new Operator(@2, "<="), $3);
											}
				|		Expr '>' Expr		{	$$ = new RelationalExpr($1, new Operator(@2, ">"), $3);	}
				|		Expr T_GreaterEqual Expr
											{
												$$ = new RelationalExpr($1, new Operator(@2, ">="), $3);
											}
				|		Expr T_Equal Expr
											{
												$$ = new EqualityExpr($1, new Operator(@2, "=="), $3);
											}
				|		Expr T_NotEqual Expr
											{
												$$ = new EqualityExpr($1, new Operator(@2, "!="), $3);
											}
				|		Expr T_And Expr		{	$$ = new LogicalExpr($1, new Operator(@2, "&&"), $3);	}
				|		Expr T_Or Expr		{	$$ = new LogicalExpr($1, new Operator(@2, "||"), $3);	}
				|		'!' Expr			{	$$ = new LogicalExpr(new Operator(@1, "!"), $2);	}
				|		T_ReadInteger '(' ')'
											{
												$$ = new ReadIntegerExpr(Join(@1,@3));
											}
				|		T_ReadLine '(' ')'	{	$$ = new ReadLineExpr(Join(@1,@3));	}
				|		T_New T_Identifier	{	$$ = new NewExpr(Join(@1, @2), new AstNamedType(new Identifier(@2, std::string($2))));	}
				|		T_NewArray '(' Expr ',' Type ')'
											{
												$$ = new NewArrayExpr(Join(@1, @6), $3, $5);
											}
				;


LValue			:		T_Identifier		{	$$ = new FieldAccess (NULL, new Identifier(@1, std::string($1))); }
				|		Expr '.' T_Identifier
											{
												$$ = new FieldAccess ($1, new Identifier(@3, std::string($3)));
											}
				|		Expr '[' Expr ']' 	{	$$ = new ArrayAccess (Join(*($1->GetLocation()), @4), $1, $3);	}
				;

Constant		:		T_StringConstant	{	printf("%s\n", $1); std::cout << std::string($1) << std::endl; $$ = new StringConstant (@1, std::string($1));	}
				|		T_IntConstant		{	$$ = new IntConstant (@1, $1);	}
				|		T_DoubleConstant	{	$$ = new DoubleConstant (@1, $1);	}
				|		T_BoolConstant		{	$$ = new BoolConstant (@1, $1);	}
				|		T_Null				{	$$ = new NullConstant (@1);	}
				;

Call			:		T_Identifier '(' Actuals ')'
											{
												$$ = new Call (Join(@1, @4), NULL, new Identifier(@1, std::string($1)), $3);
											}
				|		Expr '.' T_Identifier '(' Actuals ')'
											{
												$$ = new Call (Join(*($1->GetLocation()), @4), $1, new Identifier(@3, std::string($3)), $5);
											}
				;

Actuals			:		ExprList			{	$$ = $1;	}
				|		/* empty */			{	$$ = new list<Expr*>;	}
				;

ExprList		:		ExprList ',' Expr	{	($$ = $1)->push_back($3);	}
				|		Expr				{	($$ = new list<Expr*>)->push_back($1);	}
				;

%%
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}

%{

#include <string.h>
#include <stdio.h>
#include "../parser/scanner.h"
#include "../tools/utility.h" // for PrintDebug()
#include "../error/errors.h"
#include "../parser/parser.h" // for token codes, yylval
#include <vector>
using namespace std;

#define TAB_SIZE 8

static int curLineNum, curColNum;
extern YYSTYPE yylval;
extern struct yyltype yylloc;
vector<const char*> savedLines;

static void DoBeforeEachAction(); 
#define YY_USER_ACTION DoBeforeEachAction();

%}

%s N
%x COPY COMM
%option stack

DIGIT             ([0-9])
HEX_DIGIT         ([0-9a-fA-F])
HEX_INTEGER       (0[Xx]{HEX_DIGIT}+)
INTEGER           ({DIGIT}+)
EXPONENT          ([Ee][-+]?{INTEGER})
DOUBLE            ({INTEGER}"."{DIGIT}*{EXPONENT}?)
BEG_STRING        (\"[^"\n]*)
STRING            ({BEG_STRING}\")
IDENTIFIER        ([a-zA-Z][a-zA-Z_0-9]*)
OPERATOR          ([-+/*%=.,;!<>()[\]{}])
BEG_COMMENT       ("/*")
END_COMMENT       ("*/")
SINGLE_COMMENT    ("//"[^\n]*)

%%             /* BEGIN RULES SECTION */

<COPY>.*               { char curLine[512];
                         //strncpy(curLine, yytext, sizeof(curLine));
                        char *str = (char *)malloc(strlen(yytext) + 1);
	                    if (str)
		                    strcpy(str, yytext);
                         savedLines.push_back(str);
                         curColNum = 1; yy_pop_state(); yyless(0); }
<COPY><<EOF>>          { yy_pop_state(); }
<*>\n                  { curLineNum++; curColNum = 1;
                         if (YYSTATE == COPY) savedLines.push_back("");
                         else yy_push_state(COPY); }

[ ]+                   { /* ignore all spaces */  }
<*>[\t]                { curColNum += TAB_SIZE - curColNum%TAB_SIZE + 1; }

 /* -------------------- Comments ----------------------------- */
{BEG_COMMENT}          { BEGIN(COMM); }
<COMM>{END_COMMENT}    { BEGIN(N); }
<COMM><<EOF>>          { ReportError::UntermComment();
                         return 0; }
<COMM>.                { /* ignore everything else that doesn't match */ }
{SINGLE_COMMENT}       { /* skip to end of line for // comment */ }


 /* --------------------- Keywords ------------------------------- */
"void"              { return T_Void;        }
"int"               { return T_Int;         }
"double"            { return T_Double;      }
"bool"              { return T_Bool;        }
"string"            { return T_String;      }
"null"              { return T_Null;        }
"class"             { return T_Class;       }
"extends"           { return T_Extends;     }
"this"              { return T_This;        }
"interface"         { return T_Interface;   }
"implements"        { return T_Implements;  }
"while"             { return T_While;       }
"for"               { return T_For;         }
"if"                { return T_If;          }
"else"              { return T_Else;        }
"return"            { return T_Return;      }
"break"             { return T_Break;       }
"new"               { return T_New;         }
"NewArray"          { return T_NewArray;    }
"Print"             { return T_Print;       }
"ReadInteger"       { return T_ReadInteger; }
"ReadLine"          { return T_ReadLine;    }



 /* -------------------- Operators ----------------------------- */
"<="                { return T_LessEqual;   }
">="                { return T_GreaterEqual;}
"=="                { return T_Equal;       }
"!="                { return T_NotEqual;    }
"&&"                { return T_And;         }
"||"                { return T_Or;          }
"[]"                { return T_Dims;        }
{OPERATOR}          { return yytext[0];     }

 /* -------------------- Constants ------------------------------ */
"true"|"false"      { yylval.boolConstant = (yytext[0] == 't');
                         return T_BoolConstant; }
{INTEGER}           { yylval.integerConstant = strtol(yytext, NULL, 10);
                         return T_IntConstant; }
{HEX_INTEGER}       { yylval.integerConstant = strtol(yytext, NULL, 16);
                         return T_IntConstant; }
{DOUBLE}            { yylval.doubleConstant = atof(yytext);
                         return T_DoubleConstant; }
{STRING}            {   char *str = (char *)malloc(strlen(yytext) + 1);
	                    if (str) {
                            strncpy(str, yytext, strlen(yytext) + 1);
                            yylval.stringConstant = str;
                            str[strlen(yytext)] = '\0';
                        }
                        return T_StringConstant; }
{BEG_STRING}        { ReportError::UntermString(&yylloc, yytext); }


 /* -------------------- Identifiers --------------------------- */
{IDENTIFIER}        { if (strlen(yytext) > MaxIdentLen)
                         ReportError::LongIdentifier(&yylloc, yytext);
                       strncpy(yylval.identifier, yytext, MaxIdentLen);
                       yylval.identifier[MaxIdentLen] = '\0';
                       return T_Identifier; }


 /* -------------------- Default rule (error) -------------------- */
.                   { ReportError::UnrecogChar(&yylloc, yytext[0]); }

%%

void InitScanner()
{
    PrintDebug("lex", "Initializing scanner");
    yy_flex_debug = false;
    BEGIN(N);
    yy_push_state(COPY); // copy first line at start
    curLineNum = 1;
    curColNum = 1;
}

static void DoBeforeEachAction()
{
   yylloc.first_line = curLineNum;
   yylloc.first_column = curColNum;
   yylloc.last_column = curColNum + yyleng - 1;
   curColNum += yyleng;
}

const char *GetLineNumbered(int num) {
   if (num <= 0 || num > savedLines.size()) return NULL;
   return savedLines[num-1]; 
}



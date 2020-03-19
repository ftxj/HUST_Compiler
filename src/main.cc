#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "./tools/utility.h"
#include "./error/errors.h"
#include "./parser/parser.h"

std::ofstream astStream;
std::ofstream symStream;
std::ofstream tacStream;
std::ofstream mipsStream;

int main(int argc, char *argv[]) {
    
    ParseCommandLine(argc, argv);
    InitScanner();
    InitParser();
    yyparse();
    return (ReportError::NumErrors() == 0? 0 : -1);
}


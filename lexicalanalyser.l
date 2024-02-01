%{
#include <stdio.h>
%}

%%

[ \t\n]         

[0-9]+          { printf("Number: %s\n", yytext); }
[+\-*/]         { printf("Operator: %s\n", yytext); }  /* Properly escaped '-' */
[(){}]          { printf("Delimiter: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }

.               { printf("Invalid character: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}


/* Save the code as lex.l.
Use the Lex tool (e.g., flex on Linux/macOS) to compile: flex lex.l.
This generates a lex.yy.c file containing the C code for the lexical analyzer.
Compile the generated C code with C compiler: gcc lex.yy.c -lfl (or) gcc lex.yy.c -o lex -ll.
Run the executable to perform lexical analysis on your input file */

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);

double result;  // To store the result of calculations

%}

%token NUMBER
%token ADD SUB MUL DIV POW

%%

expression: NUMBER             { result = $1; }
          | expression ADD expression    { result = $1 + $3; }
          | expression SUB expression    { result = $1 - $3; }
          | expression MUL expression    { result = $1 * $3; }
          | expression DIV expression    { result = $1 / $3; }
          | expression POW expression    { result = pow($1, $3); }
          ;

%%

int main() {
    printf("Enter an expression: ");
    yyparse();
    printf("Result: %f\n", result);
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

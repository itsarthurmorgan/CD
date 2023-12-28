#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Token types
#define KEYWORD 1
#define IDENTIFIER 2
#define CONSTANT 3
#define OPERATOR 4
#define DELIMITER 5

// Function to check if a string is a keyword
int isKeyword(char *token) {
    char keywords[][10] = {"int", "float", "char", "if", "else", "while", "for", "return"};

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to classify a token into different types
int classifyToken(char *token) {
    if (isKeyword(token)) {
        return KEYWORD;
    } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        return CONSTANT;
    } else if ((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z')) {
        return IDENTIFIER;
    } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '=') {
        return OPERATOR;
    } else if (token[0] == ';' || token[0] == ',' || token[0] == '(' || token[0] == ')' || token[0] == '{' || token[0] == '}') {
        return DELIMITER;
    } else {
        return -1; // Unknown token type
    }
}

// Function to tokenize the input program
void tokenize(char *program) {
    char *token = strtok(program, " \t\n");
    while (token != NULL) {
        int type = classifyToken(token);

        printf("Token: %-15s Type: ", token);
        switch (type) {
            case KEYWORD:
                printf("Keyword\n");
                break;
            case IDENTIFIER:
                printf("Identifier\n");
                break;
            case CONSTANT:
                printf("Constant\n");
                break;
            case OPERATOR:
                printf("Operator\n");
                break;
            case DELIMITER:
                printf("Delimiter\n");
                break;
            default:
                printf("Unknown\n");
        }

        token = strtok(NULL, " \t\n");
    }
}

int main() {
    char program[1000];

    printf("Enter the C program:\n");
    fgets(program, sizeof(program), stdin);

    printf("\nTokenization Results:\n");
    tokenize(program);

    return 0;
}

//o: Enter the C program:
//int a = b + c

//Tokenization Results:
//Token: int             Type: Keyword
//Token: a               Type: Identifier
//Token: =               Type: Operator
//Token: b               Type: Identifier
//Token: +               Type: Operator
//Token: c               Type: Identifier

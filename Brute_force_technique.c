#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

typedef struct {
    char nonTerminal;
    char rhs[MAX_RULES][MAX_SYMBOLS];
    int numRules;
} ProductionRule;

ProductionRule rules[MAX_RULES];
int numRules;

int match(char c, char **input) {
    if (**input == c) {
        (*input)++;
        return 1;
    }
    return 0;
}

void displayRules() {
    printf("\nGrammar Rules:\n");
    for (int i = 0; i < numRules; i++) {
        printf("%c -> %s", rules[i].nonTerminal, rules[i].rhs[0]);
        for (int j = 1; j < rules[i].numRules; j++) {
            printf("\n| %s", rules[i].rhs[j]);
        }
        printf("\n");
    }
}

int parse(char *input, char nonTerminal) {
    for (int i = 0; i < numRules; i++) {
        if (rules[i].nonTerminal == nonTerminal) {
            for (int j = 0; j < rules[i].numRules; j++) {
                char *originalInput = input;
                int success = 1;

                for (int k = 0; k < strlen(rules[i].rhs[j]); k++) {
                    if (!match(rules[i].rhs[j][k], &input)) {
                        success = 0;
                        break;
                    }
                }

                if (success) {
                    printf("Successfully matched rule: %c -> %s\n", nonTerminal, rules[i].rhs[j]);
                    return 1;
                }

                input = originalInput;
            }
        }
    }

    return 0;
}

int main() {
    printf("Enter the number of production rules: ");
    scanf("%d", &numRules);

    printf("Enter the production rules:\n");
    for (int i = 0; i < numRules; i++) {
        printf("Rule %d (Non-terminal): ", i + 1);
        scanf(" %c", &rules[i].nonTerminal);

        printf("Number of rules for %c: ", rules[i].nonTerminal);
        scanf("%d", &rules[i].numRules);

        printf("Enter the rules (separated by spaces): ");
        for (int j = 0; j < rules[i].numRules; j++) {
            scanf("%s", rules[i].rhs[j]);
        }
    }

    displayRules();

    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);

    char *inputPtr = input;
    int success = parse(inputPtr, rules[0].nonTerminal);

    if (success) {
        printf("Parsing successful!\n");
    } else {
        printf("Parsing failed!\n");
    }

    return 0;
}
//o:Enter the number of production rules: 2
// Enter the production rules:
// Rule 1 (Non-terminal): S
// Number of rules for S: 2
// Enter the rules (separated by spaces): a b
// Rule 2 (Non-terminal): A
// Number of rules for A: 1
// Enter the rules (separated by spaces): b

// Grammar Rules:
// S -> a
// | b
// A -> b
// Enter the input string: abc
// Successfully matched rule: S -> a
// Parsing successful!

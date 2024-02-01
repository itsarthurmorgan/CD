#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

// Structure to represent production rules
typedef struct {
    char nonTerminal;
    char rhs[MAX_RULES][MAX_SYMBOLS];
    int numRules;
} ProductionRule;

ProductionRule rules[MAX_RULES];
int numRules;

// Function to calculate First set for a non-terminal
void calculateFirst(char nonTerminal, char firstSet[MAX_SYMBOLS]) {
    int i, j, k;
    for (i = 0; i < numRules; i++) {
	if (rules[i].nonTerminal == nonTerminal) {
	    for (j = 0; j < rules[i].numRules; j++) {
		char firstSymbol = rules[i].rhs[j][0];
		if (firstSymbol >= 'a' && firstSymbol <= 'z') {
		    // Terminal symbol
		    firstSet[firstSymbol - 'a'] = 1;
		} else if (firstSymbol != 'e') {
		    // Non-terminal symbol
		    calculateFirst(firstSymbol, firstSet);
		    for (k = 0; k < MAX_SYMBOLS; k++) {
			if (firstSet[k]) {
			    firstSet[k] = 0;
			    strcat(firstSet, rules[i].rhs[j]);
			}
		    }
		} else {
		    // ε production
		    firstSet[firstSymbol - 'e'] = 1;
		}
	    }
	}
    }
}

// Function to calculate Follow set for a non-terminal
void calculateFollow(char nonTerminal, char followSet[MAX_SYMBOLS]) {
    int i, j, k;
    for (i = 0; i < numRules; i++) {
	for (j = 0; j < rules[i].numRules; j++) {
	    char* pos = strstr(rules[i].rhs[j], &nonTerminal);
	    if (pos != NULL) {
		char nextSymbol = *(pos + 1);
		if (nextSymbol >= 'a' && nextSymbol <= 'z') {
		    // Terminal symbol
		    followSet[nextSymbol - 'a'] = 1;
		} else if (nextSymbol != '\0') {
		    // Non-terminal symbol
		    char firstSet[MAX_SYMBOLS];
		    calculateFirst(nextSymbol, firstSet);
		    for (k = 0; k < MAX_SYMBOLS; k++) {
			if (firstSet[k]) {
			    firstSet[k] = 0;
			    strcat(followSet, firstSet);
			}
		    }
		    if (strchr(firstSet, 'e') != NULL) {
			// ε is in the First set of nextSymbol
			calculateFollow(rules[i].nonTerminal, followSet);
		    }
		}
	    }
	}
    }
}

int main() {
    int i,j;
    // Reading the grammar rules
    printf("Enter the number of production rules: ");
    scanf("%d", &numRules);

    printf("Enter the production rules:\n");
    for (i=0; i<numRules; i++) {
	printf("Rule %d (Non-terminal): ", i + 1);
	scanf(" %c", &rules[i].nonTerminal);

	printf("Number of rules for %c: ", rules[i].nonTerminal);
	scanf("%d", &rules[i].numRules);

	printf("Enter the rules (separated by spaces): ");
	for ( j = 0; j < rules[i].numRules; j++) {
	    scanf("%s", rules[i].rhs[j]);
	}
    }

    // Calculate and print First and Follow sets
    for ( i = 0; i < numRules; i++) {
	char firstSet[MAX_SYMBOLS] = {0};
	calculateFirst(rules[i].nonTerminal, firstSet);
	printf("First(%c): {", rules[i].nonTerminal);
	for ( j = 0; j < MAX_SYMBOLS; j++) {
	    if (firstSet[j]) {
		printf(" %c", 'a' + j);
	    }
	}
	printf(" }\n");
    }

    for ( i = 0; i < numRules; i++) {
	char followSet[MAX_SYMBOLS] = {0};
	calculateFollow(rules[i].nonTerminal, followSet);
	printf("Follow(%c): {", rules[i].nonTerminal);
	for ( j = 0; j < MAX_SYMBOLS; j++) {
            if (followSet[j]) {
                printf(" %c", 'a' + j);
            }
        }
        printf(" }\n");
    }

    return 0;
}

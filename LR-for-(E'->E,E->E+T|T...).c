#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[30];
int top = -1;

void push(char c) {
    top++;
    stack[top] = c;
}

char pop() {
    char c;
    if (top != -1) {
        c = stack[top];
        top--;
        return c;
    }
    return 'x';
}

void printstat() {
    int i;
    printf("\n$");
    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int main() {
    int i, l;
    char input[20], ch1, ch2, ch3;

    printf("----LR PARSING----\n");
    printf("ENTER THE EXPRESSION:");
    scanf("%s", input);
    l = strlen(input);
    printf("$");

    for (i = 0; i < l; i++) {
        if (input[i] == 'a') {
            push('F');
            printstat();
            printf("a");
        } else if (input[i] == '+') {
            push('+');
            printstat();
            printf("+");
        } else if (input[i] == '*') {
            push('*');
            printstat();
            printf("*");
        } else if (input[i] == '(') {
            push('(');
            printstat();
            printf("(");
        } else if (input[i] == ')') {
            push(')');
            printstat();
            printf(")");
        }
    }

    printstat();
    l = strlen(input);
    while (l) {
        ch1 = pop();
        if (ch1 == 'x') {
            printf("\n$");
            break;
        }
        if (ch1 == 'a' || ch1 == '+' || ch1 == '*' || ch1 == '(' || ch1 == ')') {
            ch2 = pop();
            if (ch2 == 'F') {
                push('T');
                printstat();
                printf("F");
            } else if (ch2 == '+' || ch2 == '*') {
                ch3 = pop();
                if (ch3 == 'T') {
                    push('E');
                    printstat();
                    printf("T");
                }
            } else if (ch2 == '(') {
                ch3 = pop();
                if (ch3 == ')') {
                    push(')');
                    printstat();
                    printf(")");
                }
            }
        }
    }

    return 0;
}

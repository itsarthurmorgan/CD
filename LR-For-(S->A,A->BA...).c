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
    char s1[20], ch1, ch2, ch3;

    printf("----LR PARSING----\n");
    printf("ENTER THE EXPRESSION:");
    scanf("%s", s1);
    l = strlen(s1);
    printf("$");

    for (i = 0; i < l; i++) {
        if (s1[i] == 'a') {
            push('B');
            printstat();
            printf("a");
        } else if (s1[i] == 'b') {
            push('B');
            printstat();
            printf("b");
        }
    }

    printstat();
    l = strlen(s1);
    while (l) {
        ch1 = pop();
        if (ch1 == 'x') {
            printf("\n$");
            break;
        }
        if (ch1 == 'B') {
            ch2 = pop();
            if (ch2 == 'a') {
                push('A');
                printstat();
                printf("a");
            } else if (ch2 == 'b') {
                push('A');
                printstat();
                printf("b");
            }
        }
        ch3 = ch1;
    }

    return 0;
}
//o:----LR PARSING----
//ENTER THE EXPRESSION:aabb
//$
//$Ba
//$BBa
//$BBBb
//$BBBBb
//$BBBB
//$

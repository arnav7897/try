#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

typedef struct {
    char lhs;
    char rhs[MAX_SYMBOLS];
    int dot;
} LR0Item;

LR0Item items[MAX_RULES * MAX_SYMBOLS];
int itemCount = 0;
char grammar[MAX_RULES][MAX_SYMBOLS];

void addItem(char lhs, char *rhs, int dot) {
    items[itemCount].lhs = lhs;
    strcpy(items[itemCount].rhs, rhs);
    items[itemCount].dot = dot;
    itemCount++;
}

void generateLR0Items(int ruleCount) {
    for (int i = 0; i < ruleCount; i++) {
        int len = strlen(grammar[i]) - 2;  // Ignore "A->"
        for (int j = 0; j <= len; j++) {
            addItem(grammar[i][0], grammar[i] + 3, j);
        }
    }
}

void printLR0Items() {
    printf("LR(0) Items:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("[%c -> ", items[i].lhs);
        for (int j = 0; j <= strlen(items[i].rhs); j++) {
            if (j == items[i].dot) printf(".");
            if (j < strlen(items[i].rhs)) printf("%c", items[i].rhs[j]);
        }
        printf("]\n");
    }
}

int main() {
    int ruleCount;
    printf("Enter number of grammar rules: ");
    scanf("%d", &ruleCount);
    getchar();
    
    printf("Enter grammar rules (format: A->BC or A->a):\n");
    for (int i = 0; i < ruleCount; i++) {
        fgets(grammar[i], MAX_SYMBOLS, stdin);
        grammar[i][strcspn(grammar[i], "\n")] = '\0';
    }

    generateLR0Items(ruleCount);
    printLR0Items();

    return 0;
}

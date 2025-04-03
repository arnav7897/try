#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

char grammar[MAX_RULES][MAX_SYMBOLS];
char first[MAX_SYMBOLS][MAX_SYMBOLS], follow[MAX_SYMBOLS][MAX_SYMBOLS];
char nonTerminals[MAX_SYMBOLS];
int ruleCount, nonTermCount = 0;

int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

void addToSet(char *set, char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void computeFirst(char symbol, char *result) {
    for (int i = 0; i < ruleCount; i++) {
        if (grammar[i][0] == symbol) {
            if (!isNonTerminal(grammar[i][3]) || grammar[i][3] == '#') {
                addToSet(result, grammar[i][3]);
            } else {
                computeFirst(grammar[i][3], result);
            }
        }
    }
}

void computeFollow(char symbol, char *result) {
    if (symbol == grammar[0][0]) addToSet(result, '$');
    for (int i = 0; i < ruleCount; i++) {
        for (int j = 3; j < strlen(grammar[i]); j++) {
            if (grammar[i][j] == symbol) {
                if (j + 1 < strlen(grammar[i])) {
                    if (!isNonTerminal(grammar[i][j + 1])) {
                        addToSet(result, grammar[i][j + 1]);
                    } else {
                        char temp[MAX_SYMBOLS] = "";
                        computeFirst(grammar[i][j + 1], temp);
                        strcat(result, temp);
                    }
                } else {
                    computeFollow(grammar[i][0], result);
                }
            }
        }
    }
}

void printSets() {
    for (int i = 0; i < nonTermCount; i++) {
        printf("FIRST(%c) = { %s }\n", nonTerminals[i], first[i]);
        printf("FOLLOW(%c) = { %s }\n", nonTerminals[i], follow[i]);
    }
}

int main() {
    printf("Enter number of grammar rules: ");
    scanf("%d", &ruleCount);
    getchar();

    printf("Enter grammar rules (format: A->BC or A->a):\n");
    for (int i = 0; i < ruleCount; i++) {
        fgets(grammar[i], MAX_SYMBOLS, stdin);
        grammar[i][strcspn(grammar[i], "\n")] = '\0';
        if (!strchr(nonTerminals, grammar[i][0])) {
            nonTerminals[nonTermCount++] = grammar[i][0];
        }
    }

    for (int i = 0; i < nonTermCount; i++) computeFirst(nonTerminals[i], first[i]);
    for (int i = 0; i < nonTermCount; i++) computeFollow(nonTerminals[i], follow[i]);

    printSets();
    return 0;
}
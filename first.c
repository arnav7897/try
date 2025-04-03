#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 100
#define MAX_SYMBOL 100

char nonTerminal[MAX_SYMBOL], first[MAX_SYMBOL][MAX_SYMBOL], follow[MAX_SYMBOL][MAX_SYMBOL];
char rhs[MAX_RULES][MAX_SYMBOL][MAX_RULES];
int numRules;

int isnonTerminal(char c) { return (c >= 'A' && c <= 'Z'); }

void addSet(char *set, char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void findFirst(int idx) {
    if (first[idx][0]) return;
    for (int i = 0; rhs[idx][i][0]; i++) {
        char *prod = rhs[idx][i];
        if (!isnonTerminal(prod[0]) || prod[0] == 'e') addSet(first[idx], prod[0]);
        else {
            for (int j = 0; j < numRules; j++) {
                if (nonTerminal[j] == prod[0]) {
                    findFirst(j);
                    for (int k = 0; first[j][k]; k++) {
                        if (first[j][k] != 'e') addSet(first[idx], first[j][k]);
                    }
                }
            }
        }
    }
}

void findFollow() {
    addSet(follow[0], '$');
    int change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < numRules; i++) {
            for (int j = 0; rhs[i][j][0]; j++){
                for (int k = 0; rhs[i][j][k]; k++){
                    if (isnonTerminal(rhs[i][j][k])){
                        int idx = strchr(nonTerminal, rhs[i][j][k]) - nonTerminal;
                        int next = k + 1;
                        while (rhs[i][j][next]){
                            if (!isnonTerminal(rhs[i][j][next])){
                                addSet(follow[idx], rhs[i][j][next]);
                                break;
                            }
                            int nextIdx = strchr(nonTerminal, rhs[i][j][next]) - nonTerminal;
                            for (int m = 0; first[nextIdx][m]; m++) {
                                if (first[nextIdx][m] != 'e') addSet(follow[idx], first[nextIdx][m]);
                            }
                            if (!strchr(first[nextIdx], 'e')) break;
                            next++;
                        }
                        if(!rhs[i][j][next]) {
                            for (int m = 0; follow[i][m]; m++) {
                                if (!strchr(follow[idx], follow[i][m])) {
                                    addSet(follow[idx], follow[i][m]);
                                    change = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    printf("Enter number of rules: ");
    scanf("%d", &numRules);
    getchar();
    for (int i = 0; i < numRules; i++) {
        char input[MAX_SYMBOL * 2], *token;
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        nonTerminal[i] = input[0];  
        token = strtok(input + 3, "|");
        int j = 0;
        while (token) {
            strcpy(rhs[i][j++], token);
            token = strtok(NULL, "|");
        }
    }
    for (int i = 0; i < numRules; i++) 
    findFirst(i);
    findFollow();
    
    for (int i = 0; i < numRules; i++)
        printf("FIRST(%c) = { %s }\n", nonTerminal[i], first[i]);
    for (int i = 0; i < numRules; i++)
        printf("FOLLOW(%c) = { %s }\n", nonTerminal[i], follow[i]);
    return 0;
}
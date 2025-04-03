#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 20
#define MAX_TRANSITIONS 10
#define MAX_LABELS 26

char labels[MAX_LABELS] = "ABCDEFIJKL";
char table[MAX_STATES][MAX_TRANSITIONS][MAX_LABELS];
char dfaTable[MAX_STATES * MAX_STATES][MAX_TRANSITIONS][MAX_LABELS];
bool visited[MAX_STATES * MAX_STATES];

int states, transitions, dfaStateCount = 0;
char dfaStates[MAX_STATES * MAX_STATES][MAX_LABELS];

void readTransitions() {
    printf("Enter transitions:\n");
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < transitions; j++) {
            scanf("%s", table[i][j]);
        }
    }
}

int findStateIndex(char *state) {
    for (int i = 0; i < dfaStateCount; i++) {
        if (strcmp(dfaStates[i], state) == 0) return i;
    }
    return -1;
}

void buildDFA() {
    int front = 0, rear = 0;
    strcpy(dfaStates[dfaStateCount++], "A");
    visited[0] = true;

    while (front < dfaStateCount) {
        char curr[MAX_LABELS];
        strcpy(curr, dfaStates[front++]);

        for (int i = 0; i < transitions; i++) {
            char nextState[MAX_LABELS] = "";
            bool present[26] = {0};

            for (int j = 0; curr[j] != '\0'; j++) {
                char *trans = table[curr[j] - 'A'][i];
                for (int k = 0; trans[k] != '\0'; k++) {
                    if (!present[trans[k] - 'A']) {
                        present[trans[k] - 'A'] = true;
                        int len = strlen(nextState);
                        nextState[len] = trans[k];
                        nextState[len + 1] = '\0';
                    }
                }
            }

            int index = findStateIndex(nextState);
            if (index == -1) {
                strcpy(dfaStates[dfaStateCount], nextState);
                index = dfaStateCount++;
            }
            strcpy(dfaTable[front - 1][i], nextState);
        }
    }
}

void printDFA() {
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfaStateCount; i++) {
        printf("%s: ", dfaStates[i]);
        for (int j = 0; j < transitions; j++) {
            printf("%s ", dfaTable[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &states);
    printf("Enter number of transitions: ");
    scanf("%d", &transitions);
    readTransitions();
    buildDFA();
    printDFA();
    return 0;
}
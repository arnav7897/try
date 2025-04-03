#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register",
    "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef"
};

const char *operators[] = { "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=" };

int is_keyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(const char *word) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(word, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_identifier(const char *word) {
    if (isalpha(word[0]) || word[0] == '_') {
        for (int i = 1; word[i] != '\0'; i++) {
            if (!isalnum(word[i]) && word[i] != '_') {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void tokenize(const char *input) {
    char token[MAX_LEN];
    int len = strlen(input);
    int i = 0, j = 0;

    while (i < len) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_') {  
            j = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                token[j++] = input[i++];
            }
            token[j] = '\0';

            if (is_keyword(token)) printf("Keyword: %s\n", token);
            else printf("Identifier: %s\n", token);
        } 
        else if (isdigit(input[i])) {  
            j = 0;
            while (isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Number: %s\n", token);
        }
        else {  
            j = 0;
            token[j++] = input[i++];
            token[j] = '\0';

            if (is_operator(token)) printf("Operator: %s\n", token);
            else printf("Symbol: %s\n", token);
        }
    }
}

int main() {
    char input[MAX_LEN];

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  

    tokenize(input);

    return 0;
}

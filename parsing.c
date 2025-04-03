#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX];  // Input string
int pos = 0;      // Current position in input

// Function prototypes
int E();
int T();
int F();

// Function to check if the next character matches expected
void match(char expected) {
    if (input[pos] == expected)
        pos++;
    else {
        printf("Rejected (Invalid String)\n");
        exit(0);
    }
}

// Parses E → T E'
int E() {
    if (T()) {  // Parse T
        while (input[pos] == '+') {  // Handle E' → + T E' | ε
            match('+');
            if (!T()) return 0;
        }
        return 1;
    }
    return 0;
}

// Parses T → F T'
int T() {
    if (F()) {  // Parse F
        while (input[pos] == '*') {  // Handle T' → * F T' | ε
            match('*');
            if (!F()) return 0;
        }
        return 1;
    }
    return 0;
}

// Parses F → (E) | id
int F() {
    if (input[pos] == 'i') {  // id (represented as 'i')
        match('i');
        return 1;
    } else if (input[pos] == '(') {  // Handle (E)
        match('(');
        if (!E()) return 0;
        match(')');
        return 1;
    }
    return 0;
}

// Main function
int main() {
    printf("Enter input string (use 'i' for id, e.g., i+i*i): ");
    scanf("%s", input);
    
    if (E() && input[pos] == '\0')  // Start with E and check full input consumed
        printf("Accepted (Valid String)\n");
    else
        printf("Rejected (Invalid String)\n");

    return 0;
}

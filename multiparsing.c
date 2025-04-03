#include <stdio.h>
#include <string.h>

char input[100]; 
int pos = 0;   
int match(char expected) {
    if (input[pos] == expected) {
        pos++;
        return 1;
    }
    return 0;
}

int S() {
    if (match('a')) {
        return A();  // Call A if 'a' matched
    } else if (match('b')) {
        return B();  // Call B if 'b' matched
    }
    return 0;
}
int A() {
    if (match('c')) {
        return A();
    }
    return 1; 
}

int B() {
    return match('d'); 
}
int main() {
    printf("Enter string to check (use # for epsilon): ");
    scanf("%s", input);

    if (S() && input[pos] == '\0') {
        printf("Accepted: The string belongs to the CFG.\n");
    } else {
        printf("Rejected: The string does NOT belong to the CFG.\n");
    }

    return 0;
}

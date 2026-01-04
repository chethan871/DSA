#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Helper function: compute GCD of two integers
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Check if str can be formed by repeating sub string t
int isDivisible(const char *str, const char *t) {
    int lenStr = strlen(str);
    int lenT = strlen(t);
    
    if (lenStr % lenT != 0) return 0;
    
    for (int i = 0; i < lenStr; i++) {
        if (str[i] != t[i % lenT])
            return 0;
    }
    return 1;
}

// Main function
char* gcdOfStrings(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    int lenGCD = gcd(len1, len2);
    
    char *candidate = (char*)malloc(lenGCD + 1);
    strncpy(candidate, str1, lenGCD);
    candidate[lenGCD] = '\0';
    
    if (isDivisible(str1, candidate) && isDivisible(str2, candidate))
        return candidate;
    
    free(candidate);
    return "";
}

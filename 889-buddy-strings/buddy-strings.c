#include <stdbool.h>
#include <string.h>

bool buddyStrings(char* s, char* goal) {
    int len1 = strlen(s);
    int len2 = strlen(goal);

    // Lengths must be equal
    if (len1 != len2)
        return false;

    // Case 1: Strings are equal
    if (strcmp(s, goal) == 0) {
        int freq[26] = {0};

        for (int i = 0; i < len1; i++) {
            freq[s[i] - 'a']++;
            if (freq[s[i] - 'a'] > 1)
                return true;   // duplicate found
        }
        return false;
    }

    // Case 2: Strings are different
    int first = -1, second = -1;

    for (int i = 0; i < len1; i++) {
        if (s[i] != goal[i]) {
            if (first == -1)
                first = i;
            else if (second == -1)
                second = i;
            else
                return false; // more than 2 mismatches
        }
    }

    // Exactly two mismatches and swap should match
    return (second != -1 &&
            s[first] == goal[second] &&
            s[second] == goal[first]);
}

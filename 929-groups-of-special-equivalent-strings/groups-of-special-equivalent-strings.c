#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_LEN 100

// Compare function for qsort
int cmp(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

// Generate the canonical form of the string
void canonical(char *s, char *res) {
    int len = strlen(s);
    char even[MAX_LEN], odd[MAX_LEN];
    int e = 0, o = 0;

    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            even[e++] = s[i];
        else
            odd[o++] = s[i];
    }

    even[e] = '\0';
    odd[o] = '\0';

    qsort(even, e, sizeof(char), cmp);
    qsort(odd, o, sizeof(char), cmp);

    sprintf(res, "%s%s", even, odd);
}

// Check if the string is already in the group array
int exists(char **groups, int count, char *s) {
    for (int i = 0; i < count; i++) {
        if (strcmp(groups[i], s) == 0)
            return 1;
    }
    return 0;
}

// Main function
int numSpecialEquivGroups(char **words, int wordsSize){
    char *groups[MAX_WORDS];
    int count = 0;

    for (int i = 0; i < wordsSize; i++) {
        char res[MAX_LEN * 2] = {0};
        canonical(words[i], res);

        if (!exists(groups, count, res)) {
            groups[count] = (char *)malloc(strlen(res) + 1);
            strcpy(groups[count], res);
            count++;
        }
    }

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(groups[i]);
    }

    return count;
}

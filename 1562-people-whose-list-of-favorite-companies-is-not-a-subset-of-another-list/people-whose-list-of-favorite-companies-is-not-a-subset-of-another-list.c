#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int cmpstr(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

bool isSubset(char **a, int aSize, char **b, int bSize) {
    int i = 0, j = 0;
    while (i < aSize && j < bSize) {
        int cmp = strcmp(a[i], b[j]);
        if (cmp == 0) {
            i++; j++;
        } else if (cmp > 0) {
            j++;
        } else {
            return false;
        }
    }
    return i == aSize;
}

int* peopleIndexes(char ***favoriteCompanies, int favoriteCompaniesSize,
                   int* favoriteCompaniesColSize, int* returnSize) {

    // Sort each person's company list
    for (int i = 0; i < favoriteCompaniesSize; i++) {
        qsort(favoriteCompanies[i], favoriteCompaniesColSize[i],
              sizeof(char*), cmpstr);
    }

    int *result = (int*)malloc(sizeof(int) * favoriteCompaniesSize);
    int count = 0;

    for (int i = 0; i < favoriteCompaniesSize; i++) {
        bool subset = false;
        for (int j = 0; j < favoriteCompaniesSize && !subset; j++) {
            if (i == j) continue;
            if (favoriteCompaniesColSize[i] > favoriteCompaniesColSize[j]) continue;

            if (isSubset(favoriteCompanies[i], favoriteCompaniesColSize[i],
                         favoriteCompanies[j], favoriteCompaniesColSize[j])) {
                subset = true;
            }
        }
        if (!subset) {
            result[count++] = i;
        }
    }

    *returnSize = count;
    return result;
}

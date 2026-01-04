#include <string.h>

/* FUNCTION DECLARATION */
int minDistance(char* word1, char* word2);

/* FUNCTION DEFINITION */
int minDistance(char* word1, char* word2) {
    int n = strlen(word1);
    int m = strlen(word2);

    int dp[n + 1][m + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1]
                           ? dp[i - 1][j]
                           : dp[i][j - 1];
        }
    }

    int lcs = dp[n][m];
    return (n - lcs) + (m - lcs);
}

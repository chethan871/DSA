#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 505
#define MAXE 55

int n, evilLen;
char *s1, *s2, *evil;

int lps[MAXE];
int nextState[MAXE][26];
int dp[MAXN][MAXE][2][2];

/* ---------- KMP LPS ---------- */
void buildLPS() {
    int j = 0;
    lps[0] = 0;
    for (int i = 1; i < evilLen; i++) {
        while (j > 0 && evil[i] != evil[j])
            j = lps[j - 1];
        if (evil[i] == evil[j]) j++;
        lps[i] = j;
    }
}

/* ---------- KMP Automaton ---------- */
void buildAutomaton() {
    for (int i = 0; i < evilLen; i++) {
        for (int c = 0; c < 26; c++) {
            int j = i;
            char ch = c + 'a';
            while (j > 0 && evil[j] != ch)
                j = lps[j - 1];
            if (evil[j] == ch) j++;
            nextState[i][c] = j;
        }
    }
}

/* ---------- DP ---------- */
int solve(int pos, int matched, int low, int high) {
    if (matched == evilLen) return 0;   // evil found → invalid
    if (pos == n) return 1;             // valid string

    int *res = &dp[pos][matched][low][high];
    if (*res != -1) return *res;

    long long ans = 0;
    char from = low ? s1[pos] : 'a';
    char to   = high ? s2[pos] : 'z';

    for (char c = from; c <= to; c++) {
        int newMatched = nextState[matched][c - 'a'];
        ans = (ans + solve(
            pos + 1,
            newMatched,
            low && (c == from),
            high && (c == to)
        )) % MOD;
    }

    return *res = (int)ans;
}

/* ---------- MAIN FUNCTION ---------- */
int findGoodStrings(int _n, char* _s1, char* _s2, char* _evil) {
    n = _n;
    s1 = _s1;
    s2 = _s2;
    evil = _evil;
    evilLen = strlen(evil);

    buildLPS();
    buildAutomaton();

    memset(dp, -1, sizeof(dp));
    return solve(0, 0, 1, 1);
}

int countVowelStrings(int n) 
{
    long long res = 1;
    int k = 4;
for (int i = 1; i <= k; i++) {
        res = res * (n + i) / i;
    }

    return (int)res;
}

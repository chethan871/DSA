class Solution {
public:
    int distinctPoints(string s, int k) {
        int n = s.length(), px[n + 1], py[n + 1];
        px[0] = 0; py[0] = 0;
        for (int i = 1; i <= n; i++){
            px[i] = px[i - 1];
            py[i] = py[i - 1];
            char c = s[i - 1];
            if (c == 'U') py[i]++;
            else if (c == 'D') py[i]--;
            else if (c == 'L') px[i]--;
            else px[i]++;
        }
        int x = px[n], y = py[n];
        unordered_set<long long> set;
        for (int r = n, l = n - k; l >= 0; r--, l--){
            int dx = px[r] - px[l];
            int dy = py[r] - py[l];
            set.insert(hash(x - dx, y - dy));
        }
        return set.size();
    }
private:
    long long hash(int x, int y){
        x += 100000; y += 100000;
        return ((long long)x << 18) | y;
    }
};
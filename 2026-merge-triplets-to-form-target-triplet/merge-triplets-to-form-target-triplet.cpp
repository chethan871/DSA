class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int x = target[0], y = target[1], z = target[2];
        bool xt = false, yt = false, zt = false;

        for (auto &triplet : triplets) {
            if (triplet[0] <= x && triplet[1] <= y && triplet[2] <= z) {
                if (triplet[0] == x) xt = true;
                if (triplet[1] == y) yt = true;
                if (triplet[2] == z) zt = true;
            }
        }

        return xt && yt && zt;
    }
};
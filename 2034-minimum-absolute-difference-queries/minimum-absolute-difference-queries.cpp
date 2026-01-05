class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        std::vector<std::vector<int>> vec(101, std::vector<int>(n + 1));

        for (int i{}; i < n; ++i) {
            ++vec[nums[i]][i + 1];
        }

        for (int i{1}; i < 101; ++i) {
            for (int j{1}; j <= n; ++j) vec[i][j] += vec[i][j - 1];
        }

        std::vector<int> res;
        int a{}, b{};
        for (const std::vector<int>& query : queries) {
            a = query[0]; b = query[1];
            int min{std::numeric_limits<int>::max()};

            int prev{-1};
            for (int num{1}; num < 101; ++num) {
                if (vec[num][b + 1] - vec[num][a]) {
                    if (prev != -1) {
                        min = std::min(min, num - prev);
                    }

                    prev = num;
                }
            }

            if (min == std::numeric_limits<int>::max()) min = -1;
            res.push_back(min);
        }

        return res;
    }
};
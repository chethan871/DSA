class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long res = nums[0];
        for(int i = 1, n = nums.size(); i < n; ++i) res += max(nums[i] - nums[i - 1] , 0);
        return res;
    }
};
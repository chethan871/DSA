class Solution {
public:
    struct BIT {
        int n;
        vector<long long> tree;
        BIT(int n): n(n), tree(n+1, 0) {}

        void add(int i, long long v) {
            for (; i <= n; i += i & -i) tree[i] += v;
        }
        long long sum(int i) {
            long long s = 0;
            for (; i > 0; i -= i & -i) s += tree[i];
            return s;
        }
        long long range(int l, int r) {
            if (l > r) return 0;
            return sum(r) - sum(l - 1);
        }
    };

    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        vector<int> segmentEnd(n);
        int i = 0;

        while (i < n) {
            int j = i;
            while (j + 1 < n && nums[j] <= nums[j + 1]) j++;
            for (int k = i; k <= j; k++) segmentEnd[k] = j;
            i = j + 1;
        }

        vector<long long> segmentLength(n);
        for (int k = 0; k < n; k++)
            segmentLength[k] = segmentEnd[k] - k + 1LL;

        vector<array<int,2>> pair(n);
        for (int k = 0; k < n; k++)
            pair[k] = {segmentEnd[k], k};

        sort(pair.begin(), pair.end());

        int q = queries.size();
        vector<long long> answer(q);

        vector<int> left(q), right(q);
        for (int k = 0; k < q; k++) {
            left[k] = queries[k][0];
            right[k] = queries[k][1];
        }

        vector<int> queryOrder(q);
        iota(queryOrder.begin(), queryOrder.end(), 0);
        sort(queryOrder.begin(), queryOrder.end(),
             [&](int a, int b){ return right[a] < right[b]; });

        BIT bitCount(n), bitLength(n), bitIndexSum(n);

        vector<long long> prefIndexSum(n + 1);
        for (int k = 1; k <= n; k++)
            prefIndexSum[k] = prefIndexSum[k - 1] + (k - 1);

        int ptr = 0;

        for (int qi : queryOrder) {
            int L = left[qi];
            int R = right[qi];

            while (ptr < n && pair[ptr][0] <= R) {
                int idx = pair[ptr][1];
                int pos = idx + 1;

                bitCount.add(pos, 1);
                bitLength.add(pos, segmentLength[idx]);
                bitIndexSum.add(pos, idx);

                ptr++;
            }

            int Lpos = L + 1;
            int Rpos = R + 1;

            long long inCount = bitCount.range(Lpos, Rpos);
            long long inLengthSum = bitLength.range(Lpos, Rpos);
            long long inIndexSum = bitIndexSum.range(Lpos, Rpos);

            long long total = R - L + 1LL;
            long long outCount = total - inCount;

            long long fullIndexSum = prefIndexSum[R + 1] - prefIndexSum[L];
            long long outIndexSum = fullIndexSum - inIndexSum;

            answer[qi] = inLengthSum + outCount * (R + 1LL) - outIndexSum;
        }

        return answer;
    }
};
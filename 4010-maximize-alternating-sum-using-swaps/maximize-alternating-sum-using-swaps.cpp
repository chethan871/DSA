// The question is about rearranging elements in an array using allowed swaps to maximize the alternating sum.

// Using DSU to group indices that can be swapped
class DSU
{
private:
    vector<int> parent, sz;

public:
    DSU(int n)
    {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int u = find(x);
        int v = find(y);
        if (u != v)
        {
            if (sz[u] < sz[v])
                swap(u, v);
            parent[v] = u;
            sz[u] += sz[v];
        }
    }

    void sett(int x, int y) { parent[x] = y; }
};

class Solution
{
public:
    long long maxAlternatingSum(vector<int> &nums, vector<vector<int>> &swaps)
    {
        int n = nums.size();
        DSU dsu(n);
        for (auto e : swaps) // Union the indices in each swap
            dsu.unionSets(e[0], e[1]);

        set<int> parents;          // Unique parents representing different components
        map<int, int> oddCount;    // Count of odd indices in each component
        map<int, vector<int>> grp; // Elements in each component

        for (int i = 0; i < n; i++)
        {
            int p = dsu.find(i);
            parents.insert(p);
            grp[p].push_back(nums[i]); // Group elements by their component
            if (i % 2)
                oddCount[p]++; // Count odd indices in this component
        }
        long long ans = 0;
        for (int x : parents) // For each component
        {
            int odd = oddCount[x]; // Number of odd indices in this component
            
            // Now, to make the sum maximum, we should place the smallest 'odd' elements at odd indices
            sort(grp[x].begin(), grp[x].end());
            
            // First the elements at odd indices need to be subtracted, so taking the smallest 'odd' elements
            long long evenSum = 0, oddSum = 0;
            for (int i = 0; i < odd; i++)
                oddSum += grp[x][i];

            // Remaining elements will be at even indices, so taking the largest elements
            for (int i = odd; i < grp[x].size(); i++)
                evenSum += grp[x][i];

            ans += (evenSum - oddSum);
        }
        return ans;
    }
};
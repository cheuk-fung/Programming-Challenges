#include <algorithm>
#include <vector>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

class HatRack {
    private:
        int maxdep;
        vector<int> tree[100];
        int size[100], leafdep[100];
        long long f[100];

        long long dp(int u, int p, int dep)
        {
            maxdep = max(maxdep, dep);
            if (p) tree[u].erase(find(tree[u].begin(), tree[u].end(), p));
            if (SIZE(tree[u]) > 2) return 0;

            size[u] = 1;
            leafdep[u] = dep;
            if (tree[u].empty()) return f[u] = 1;

            for (int i = 0; i < SIZE(tree[u]); i++) {
                int v = tree[u][i];
                if (!dp(v, u, dep + 1)) return 0;
                size[u] += size[v];
                leafdep[u] = max(leafdep[u], leafdep[v]);
            }
            if (SIZE(tree[u]) == 1) {
                if (size[tree[u][0]] == 1) return f[u] = 1;
                return 0;
            }
            if (size[tree[u][0]] < size[tree[u][1]]) swap(tree[u][0], tree[u][1]);
            int lc = tree[u][0], rc = tree[u][1];
            if (size[lc] + 1 == 1ll << (leafdep[lc] - dep)) {
                if (size[rc] + 1 == 1ll << (leafdep[rc] - dep)) {
                    if (leafdep[lc] == leafdep[rc]) return f[u] = f[lc] * f[rc] * 2;
                    return f[u] = f[lc] * f[rc];
                }
                if (leafdep[lc] != leafdep[rc]) return 0;
                return f[u] = f[lc] * f[rc];
            }
            if (leafdep[lc] != leafdep[rc] + 1) return 0;
            if (size[rc] + 1 == 1ll << (leafdep[rc] - dep)) return f[u] = f[lc] * f[rc];
            return 0;
        }

        long long run(const vector<int> &knob1, const vector<int> &knob2, int root)
        {
            for (int i = 0; i <= SIZE(knob1) + 1; i++) tree[i].clear();
            for (int i = 0; i < SIZE(knob1); i++) {
                tree[knob1[i]].push_back(knob2[i]);
                tree[knob2[i]].push_back(knob1[i]);
            }
            maxdep = 0;
            return dp(root, 0, 0);
        }

    public:
        long long countWays(vector <int> knob1, vector <int> knob2)
        {
            long long res = 0;
            for (int i = 1; i <= SIZE(knob1) + 1; i++) {
                res += run(knob1, knob2, i);
            }
            return res;
        }
};

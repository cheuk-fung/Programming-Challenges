class Disjoint_Set {
    private:

    public:
        // a[i] > 0: a[i] is i's ancestor;
        // a[i] < 0: -a[i] is the number of elements sharing the same ancestor i
        int a[MAXN];

        Disjoint_Set() { reset(); }
        void reset() { memset(a, 0xff, sizeof(a)); }

        int find(int u)
        {
            if (a[u] < 0) return u;
            return a[u] = find(a[u]);
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
};


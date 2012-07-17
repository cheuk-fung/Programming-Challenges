class Disjoint_Set {
    public:
        // a[i] > 0: a[i] is i's ancestor;
        // a[i] < 0: -a[i] is the number of elements sharing the same ancestor i
        int a[MAXN];

        Disjoint_Set() { reset(); }
        void reset() { memset(a, 0xff, sizeof(a)); }

        int find(int u)
        {
            int x = u, y = u;
            while (a[u] >= 0) u = a[u];
            while (a[y] >= 0) {
                x = a[y];
                a[y] = u;
                y = x;
            }
            return u;
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


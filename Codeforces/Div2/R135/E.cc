#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return (x << 1) | 1; }
template<class T> inline int SIZE(const T &x) { return x.size(); }

const int MAXN = 1e6 + 10;

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int l, r;
            int best, gap;
        } node[MAXN];

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                node[idx].l = node[idx].r = v;
                node[idx].best = a;
                node[idx].gap = v ? 0 : -1;
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, v, a, mid, LC(idx));
            else update(c, v, mid, b, RC(idx));

            node[idx].l = node[LC(idx)].l;
            if (node[LC(idx)].l == mid - a) node[idx].l += node[RC(idx)].l;
            node[idx].r = node[RC(idx)].r;
            if (node[RC(idx)].r == b - mid) node[idx].r += node[LC(idx)].r;
            if (node[LC(idx)].gap >= node[RC(idx)].gap) {
                node[idx].gap = node[LC(idx)].gap;
                node[idx].best = node[LC(idx)].best;
            } else {
                node[idx].gap = node[RC(idx)].gap;
                node[idx].best = node[RC(idx)].best;
            }

            int gap = a == lep ? node[idx].l - 1 : (node[idx].l - 1) >> 1;
            if (gap >= node[idx].gap) {
                node[idx].best = min(gap == node[idx].gap ? node[idx].best : INF, a == lep ? lep : a + gap);
                node[idx].gap = gap;
            }

            gap = (node[LC(idx)].r + node[RC(idx)].l - 1) >> 1;
            if (gap >= node[idx].gap) {
                node[idx].best = min(gap == node[idx].gap ? node[idx].best : INF, mid - node[LC(idx)].r + gap);
                node[idx].gap = gap;
            }

            gap = b == rep ? node[idx].r - 1 : (node[idx].r - 1) >> 1;
            if (gap >= node[idx].gap) {
                node[idx].best = min(gap == node[idx].gap ? node[idx].best : INF, b == rep ? rep - 1 : b - node[idx].r + gap);
                node[idx].gap = gap;
            }
        }

        int query() const
        {
            return node[1].best;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int hash[MAXN];

int main()
{
    int n, m;
    cin >> n >> m;

    st.build(1, n + 1);
    for (int i = 1; i <= n; i++) st.update(i, 1);
    for (int i = 0; i < m; i++) {
        int ti, id;
        cin >> ti >> id;
        if (ti == 1) {
            int r = st.query();
            hash[id] = r;
            st.update(r, 0);
            cout << hash[id] << endl;
        } else {
            st.update(hash[id], 1);
        }
    }

    return 0;
}


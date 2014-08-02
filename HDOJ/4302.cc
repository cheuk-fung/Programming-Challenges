/*
 *  SRC: HDOJ 4302
 * PROB: Holedox Eating
 * ALGO: Segment Tree
 * DATE: Jul 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <utility>
#include <iostream>

using namespace std;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MAXN = 100010;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return (x << 1) | 1; }

class Segment_Tree {
    private:
        struct Tnode {
            int a, b;
            int mn, mx;
            int cnt;
        };
        Tnode node[MAXN << 4];

    public:
        void build(int a, int b, int idx = 1)
        {
            node[idx].a = a;
            node[idx].b = b;
            node[idx].mn = INF;
            node[idx].mx = -INF;
            node[idx].cnt = 1;

            if (a + 1 < b) {
                build(a, (a + b) >> 1, LC(idx));
                build((a + b) >> 1, b, RC(idx));
            }
        }

        void insert(int c, int d, int mn, int mx, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                node[idx].mn = mn;
                node[idx].mx = mx;
                return ;
            }

            if (c < (node[idx].a + node[idx].b) >> 1) insert(c, d, mn, mx, LC(idx));
            if (d > (node[idx].a + node[idx].b) >> 1) insert(c, d, mn, mx, RC(idx));
            node[idx].mn = min(node[LC(idx)].mn, node[RC(idx)].mn);
            node[idx].mx = max(node[LC(idx)].mx, node[RC(idx)].mx);
        }

        pii query(int c, int d, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                return pii(node[idx].mn, node[idx].mx);
            }

            pii l(INF, -INF), r(INF, -INF);
            if (c < (node[idx].a + node[idx].b) >> 1) l = query(c, d, LC(idx));
            if (d > (node[idx].a + node[idx].b) >> 1) r = query(c, d, RC(idx));
            return pii(min(l.first, r.first), max(l.second, r.second));
        }
};
Segment_Tree st;

int cake[MAXN];

void eat(int x)
{
    cake[x]--;
    if (!cake[x]) {
        st.insert(x, x + 1, INF, -INF);
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        memset(cake, 0, sizeof(cake));

        int len, n;
        scanf("%d%d", &len, &n);
        st.build(0, len + 3);
        st.insert(0, 1, -INF, -INF);
        st.insert(len + 2, len + 3, INF, INF);
        int dir = 0;
        int pos = 1;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (x == 0) {
                int y;
                scanf("%d", &y);
                y++;
                if (!cake[y]) {
                    st.insert(y, y + 1, y, y);
                }
                cake[y]++;
            } else {
                if (cake[pos]) {
                    eat(pos);
                    continue;
                }
                int l = st.query(0, pos).second;
                int r = st.query(pos + 1, len + 3).first;
                if (l == -INF && r == INF) continue;
                if (pos - l == r - pos) {
                    ans += r - pos;
                    if (dir == 0) {
                        eat(r);
                        pos = r;
                    } else {
                        eat(l);
                        pos = l;
                    }
                } else if (pos - l < r - pos) {
                    eat(l);
                    dir = 1;
                    ans += pos - l;
                    pos = l;
                } else {
                    eat(r);
                    dir = 0;
                    ans += r - pos;
                    pos = r;
                }
            }
        }

        cout << "Case " << task << ": " << ans << endl;
    }

    return 0;
}

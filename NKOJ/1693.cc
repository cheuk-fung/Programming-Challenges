/*
 *  SRC: NKOJ 1693
 * PROB: Horizontally Visible Segments
 * ALGO: Segment tree
 * DATE: Sep 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 8096 << 1;

int vis[MAXN >> 1];
vector<int> visible[MAXN >> 1];

class Segment_tree {
    private:
        static int lep, rep;

        int color[MAXN << 2];

        int LC(int x) const { return x << 1; }
        int RC(int x) const { return x << 1 | 1; }

        void push_down(int idx)
        {
            if (color[idx] != -1) {
                color[LC(idx)] = color[RC(idx)] = color[idx];
                color[idx] = -1;
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(color, 0xff, sizeof color);
        }

        void update(int c, int d, int col, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                color[idx] = col;
                return ;
            }

            push_down(idx);

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, col, a, mid, LC(idx));
            if (d > mid) update(c, d, col, mid, b, RC(idx));
        }

        void query(int c, int d, int now, int a = lep, int b = rep, int idx = 1)
        {
            if (color[idx] != -1) {
                if (vis[color[idx]] != now) {
                    vis[color[idx]] = now;
                    visible[now].push_back(color[idx]);
                }
                return ;
            }
            if (a + 1 == b) return ;

            push_down(idx);

            int mid = (a + b) >> 1;
            if (c < mid) query(c, d, now, a, mid, LC(idx));
            if (d > mid) query(c, d, now, mid, b, RC(idx));
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Segment {
    int y1, y2, x;

    bool operator<(const Segment &o) const { return x < o.x; }
} seg[MAXN >> 1];

int nextint()
{
    char c;
    while (!isdigit(c = getchar())) ;
    int r = c - '0';
    while (isdigit(c = getchar())) r = r * 10 + c - '0';
    return r;
}

int main()
{
    int tasks = nextint();
    while (tasks--) {
        int n = nextint();
        for (int i = 0; i < n; i++) visible[i].clear();
        memset(vis, 0xff, sizeof vis);

        int maxy = 0;
        for (int i = 0; i < n; i++) {
            seg[i] = (Segment){nextint() * 2, nextint() * 2, nextint()};
            maxy = max(maxy, seg[i].y2);
        }
        sort(seg, seg + n);

        st.build(0, maxy + 1);
        for (int i = 0; i < n; i++) {
            st.query(seg[i].y1, seg[i].y2 + 1, i);
            sort(visible[i].begin(), visible[i].end());

            st.update(seg[i].y1, seg[i].y2 + 1, i);
        }

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)visible[i].size(); j++) {
                int a = visible[i][j];
                for (int k = 0; k < (int)visible[a].size(); k++) {
                    if (binary_search(visible[i].begin(), visible[i].begin() + j, visible[a][k])) {
                        cnt++;
                    }
                }
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}


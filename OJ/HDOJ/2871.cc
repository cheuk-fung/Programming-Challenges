/*
 *  SRC: HDOJ 2871
 * PROB: Memory Control
 * ALGO: Segment tree
 * DATE: Aug 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int l, r, mx;
        } node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int a, int b, int idx)
        {
            int mid = (a + b) >> 1;
            node[idx].mx = max(max(node[LC(idx)].mx, node[RC(idx)].mx), node[LC(idx)].r + node[RC(idx)].l);
            node[idx].l = node[LC(idx)].l + (node[LC(idx)].l == mid - a) * node[RC(idx)].l;
            node[idx].r = node[RC(idx)].r + (node[RC(idx)].r == b - mid) * node[LC(idx)].r;
        }

        void push_down(int a, int b, int idx)
        {
            if (node[idx].mx == b - a) {
                int mid = (a + b) >> 1;
                node[LC(idx)].mx = node[LC(idx)].l = node[LC(idx)].r = mid - a;
                node[RC(idx)].mx = node[RC(idx)].l = node[RC(idx)].r = b - mid;
            } else if (node[idx].mx == 0) {
                node[LC(idx)].mx = node[LC(idx)].l = node[LC(idx)].r = 0;
                node[RC(idx)].mx = node[RC(idx)].l = node[RC(idx)].r = 0;
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                node[idx].l = node[idx].r = node[idx].mx = v ? 0 : b - a;
                return ;
            }

            push_down(a, b, idx);
            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));
            push_up(a, b, idx);
        }

        int query(int x, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) return a;

            push_down(a, b, idx);
            int mid = (a + b) >> 1;
            if (node[LC(idx)].mx >= x) return query(x, a, mid, LC(idx));
            if (node[LC(idx)].r + node[RC(idx)].l >= x) return mid - node[LC(idx)].r;
            if (node[RC(idx)].mx >= x) return query(x, mid, b, RC(idx));
            return 0;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

vector<pii> mem;

int find(int x)
{
    int l = 0, r = mem.size();
    while (l < r) {
        int mid = (l + r) >> 1;
        if (mem[mid].second > x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        st.build(1, n + 1);
        st.update(1, n + 1, 0);
        mem.clear();

        char opr[100];
        int x;
        while (m--) {
            scanf(" %s", opr);
            if (opr[0] != 'R') scanf("%d", &x);

            switch (opr[0]) {
                case 'R': {
                              puts("Reset Now");
                              st.update(1, n + 1, 0);
                              mem.clear();
                              break;
                          }
                case 'N': {
                              int r = st.query(x);
                              if (r == 0) {
                                  puts("Reject New");
                              } else {
                                  printf("New at %d\n", r);
                                  st.update(r, r + x, 1);
                                  int pos = find(r + x);
                                  mem.insert(mem.begin() + pos, pii(r, r + x));
                              }
                              break;
                          }
                case 'F': {
                              int pos = find(x);
                              if (pos == (int)mem.size() || mem[pos].first > x) {
                                  puts("Reject Free");
                              } else {
                                  printf("Free from %d to %d\n", mem[pos].first, mem[pos].second - 1);
                                  st.update(mem[pos].first, mem[pos].second, 0);
                                  mem.erase(mem.begin() + pos);
                              }
                              break;
                          }
                case 'G': {
                              if (x - 1 >= (int)mem.size()) {
                                  puts("Reject Get");
                              } else {
                                  printf("Get at %d\n", mem[x - 1].first);
                              }
                          }
            }
        }

        putchar(10);
    }

    return 0;
}


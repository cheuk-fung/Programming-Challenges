/*
 *  SRC: POJ 3225
 * PROB: Help with Intervals
 * ALGO: Segment tree
 * DATE: Aug 06, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 65556 << 1;

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int cover;
            int sd;
        } node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void XOR(int idx)
        {
            if (node[idx].cover > -1) {
                node[idx].cover ^= 1;
            } else {
                node[idx].sd ^= 1;
            }
        }

        void push_down(int idx)
        {
            if (node[idx].cover > -1) {
                node[LC(idx)].cover = node[RC(idx)].cover = node[idx].cover;
                node[idx].cover = -1;

                node[LC(idx)].sd = node[RC(idx)].sd  = 0;
            }
            if (node[idx].sd) {
                XOR(LC(idx));
                XOR(RC(idx));
                node[idx].sd = 0;
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int d, int opr, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                switch (opr) {
                    case 0: node[idx].cover = 0; node[idx].sd = 0; break;
                    case 1: node[idx].cover = 1; node[idx].sd = 0; break;
                    case -1: XOR(idx);
                }
                return ;
            }

            push_down(idx);

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, opr, a, mid, LC(idx));
            if (d > mid) update(c, d, opr, mid ,b, RC(idx));
        }

        void query(vector<pii> &ans, int a = lep, int b = rep, int idx = 1)
        {
            if (node[idx].cover > -1) {
                if (node[idx].cover == 0) return ;
                int l = a, r = b;
                while (!ans.empty() && ans.back().second == l) {
                    l = ans.back().first;
                    ans.pop_back();
                }
                ans.push_back(pii(l, r));
                return ;
            }

            push_down(idx);

            int mid = (a + b) >> 1;
            query(ans, a, mid, LC(idx));
            query(ans, mid, b, RC(idx));
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

vector<pii> ans(MAXN);

void printans()
{
    if (ans.empty()) {
        puts("empty set");
    } else {
        for (int i = 0; i < (int)ans.size(); i++) {
            char lb, rb;
            int l = ans[i].first, r = ans[i].second;
            lb = (l & 1) ? '(' : '[';
            rb = (r & 1) ? ']' : ')';
            printf("%c%d,%d%c%c", lb, l / 2, r / 2, rb, i + 1 == (int)ans.size() ? '\n': ' ');
        }
    }
}

int main()
{
    char opr;
    char interval[100];
    st.build(0, MAXN);
    while (~scanf(" %c %s", &opr, interval)) {
        char lb, rb;
        int l, r;
        sscanf(interval, "%c%d,%d%c", &lb, &l, &r, &rb);
        l <<= 1; r <<= 1;
        if (lb == '(') l++;
        if (rb == ']') r++;
        if (l >= r) {
            if (opr == 'I' || opr == 'C') {
                st.update(0, MAXN, 0);
            }
            continue;
        }
        switch (opr) {
            case 'U': st.update(l, r, 1); break;
            case 'I': {
                          if (l > 0) st.update(0, l, 0);
                          if (r < MAXN) st.update(r, MAXN, 0);
                          break;
                      }
            case 'D': st.update(l, r, 0); break;
            case 'C': {
                          if (l > 0) st.update(0, l, 0);
                          if (r < MAXN) st.update(r, MAXN, 0);
                          st.update(l, r, -1);
                          break;
                      }
            case 'S': st.update(l, r, -1);
        }

//        ans.clear();
//        st.query(ans);
//        printans();
    }

    ans.clear();
    st.query(ans);
    printans();

    return 0;
}


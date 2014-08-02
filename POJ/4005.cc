/*
 *  SRC: POJ 4005
 * PROB: Moles
 * ALGO: BIT + BST
 * DATE: Sep 21, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 600010;
char s[MAXN * 3], t[7010];
char *stail;
int prn[7010];

class BIT {
    private:
        int mn, mx;
        int c[MAXN];
        int lowbit(int x) const { return x & -x; }

    public:
        void build()
        {
            mn = 0x3f3f3f3f;
            mx = 0;
            memset(c, 0, sizeof c);
        }

        void update(int x)
        {
            mn = min(mn, x);
            mx = max(mx, x);
            for ( ; x < MAXN; x += lowbit(x)) c[x]++;
        }

        int sum(int x)
        {
            int r = 0;
            for ( ; x; x -= lowbit(x)) r += c[x];
            return r;
        }

        int getprev(int x)
        {
            if (x < mn) return -1;
            int l = mn, r = mx;
            int ret = sum(x) - 1;
            while (l < r) {
                int mid = (l + r - 1) >> 1;
                if (sum(mid) > ret) r = mid;
                else l = mid + 1;
            }
            return l;
        }

        int getnext(int x)
        {
            if (x > mx) return -1;
            int l = mn, r = mx;
            int ret = sum(x);
            while (l < r) {
                int mid = (l + r - 1) >> 1;
                if (sum(mid) > ret) r = mid;
                else l = mid + 1;
            }
            return l;
        }
} bit;

class BST {
    private:
        struct Tnode {
            int lc, rc;
            bool vis;
        };
        Tnode node[MAXN];
        int root;
        int S[MAXN * 3];

    public:
        void build()
        {
            memset(node, 0, sizeof node);
        }

        void insert(int v, int index)
        {
            if (index == 0) {
                root = v;
                return ;
            }

            int lp = bit.getprev(v);
            if (lp != -1 && node[lp].rc == 0) {
                node[lp].rc = v;
            } else {
                int rp = bit.getnext(v);
                node[rp].lc = v;
            }
        }

        void query()
        {
            int Stop = 0;

            S[Stop++] = root;
            while (Stop) {
                int p = S[Stop - 1];
                node[p].vis = true;
                *stail++ = p & 1 ? '1' : '0';
                if (node[p].lc && !node[node[p].lc].vis) {
                    S[Stop++] = node[p].lc;
                } else if (node[p].rc && !node[node[p].rc].vis) {
                    S[Stop++] = node[p].rc;
                } else {
                    Stop--;
                }
            }

            *stail++ = 0;
        }
} bst;

void kmpinit(char *b, int m)
{
    prn[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && b[j] != b[i]) j = prn[j - 1];
        if (b[j] == b[i]) j++;
        prn[i] = j;
    }
}

int kmp(char *a, int n, char *b, int m)
{
    int cnt = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && b[j] != a[i]) j = prn[j - 1];
        if (b[j] == a[i]) j++;
        if (j == m) {
            cnt++;
            j = prn[j - 1];
        }
    }
    return cnt;
}

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
    for (int task = 1; task <= tasks; task++) {
        bst.build();
        bit.build();
        stail = s;

        int n = nextint();
        for (int i = 0; i < n; i++) {
            int v = nextint();
            bst.insert(v, i);
            bit.update(v);
        }
        bst.query();
        // printf("%s\n", s);

        scanf("%s", t);
        int slen = stail - s, tlen = strlen(t);
        kmpinit(t, tlen);
        int r = kmp(s, slen, t, tlen);
        printf("Case #%d: %d\n", task, r);
    }

    return 0;
}


#include <cstdio>
#include <algorithm>

using std::sort;

const int MAXN = 10000000;
char vis[MAXN / 8 + 1];

struct Query {
    int q;
    int ans;
    short id;
} s[5000];

bool cmpq(const Query &a, const Query &b) { return a.q < b.q; }
bool cmpid(const Query &a, const Query &b) { return a.id < b.id; }

int main(int argc, char *argv[])
{
    // printf("%d\n", (sizeof vis + sizeof s)/ 1024);

    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &s[i].q);
        s[i].id = i;
    }
    sort(s, s + k, cmpq);

    int cnt = 0, pos = 0;
    for (int i = 1; i <= n; i++) {
        if (!(vis[i / 8] & (1 << (i & 7)))) {
            cnt++;
            while (pos < k && cnt == s[pos].q) {
                s[pos++].ans = i;
            }
        }

        int j = i, k = i;
        while (j) {
            k += j % 10;
            j /= 10;
        }
        if (k <= MAXN) vis[k / 8] |= 1 << (k & 7);
    }

    printf("%d\n", cnt);

    sort(s, s + k, cmpid);
    for (int i = 0; i < k; i++) {
        printf("%d%c", s[i].ans, i + 1 == k ? '\n' : ' ');
    }

    return 0;
}

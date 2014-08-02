#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 10010;

int prmcnt, prm[MAXN];
int sprmcnt, sprm[MAXN];
bool isprm[MAXN], issprm[MAXN];
vector<int> presentation, ans;

int getprm(int n, int *p, bool *b)
{
    int cnt = 0;
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * p[j] < n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }
    return cnt;
}

void dfs(int n, int x)
{
    if (n <= 2 || (!ans.empty() && presentation.size() >= ans.size())) return ;
    if (issprm[n]) {
        presentation.push_back(n);
        if (ans.empty() || presentation.size() < ans.size()) {
            ans = presentation;
        }
        presentation.pop_back();
        return ;
    }

    for (int i = x; i >= 0; i--) {
        presentation.push_back(sprm[i]);
        dfs(n - sprm[i], i);
        presentation.pop_back();
    }
}

int main(int argc, char *argv[])
{
    prmcnt = getprm(MAXN, prm, isprm);
    memset(issprm, false, sizeof issprm);
    for (int i = 0; i < prmcnt && prm[i] < prmcnt; i++) {
        sprm[sprmcnt++] = prm[prm[i] - 1];
        issprm[prm[prm[i] - 1]] = true;
    }

    int n;
    scanf("%d", &n);
    dfs(n, sprmcnt - 1);
    if (ans.empty()) {
        puts("0");
    } else {
        printf("%d\n", ans.size());
        for (int i = 0; i < (int)ans.size(); i++) {
            printf("%d%c", ans[i], i + 1 == (int)ans.size() ? '\n' : ' ');
        }
    }

    return 0;
}

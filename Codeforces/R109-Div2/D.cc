#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100010;

int get_prime(int n, int* p, bool* b)
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

int prm[MAXN], prm_vis[MAXN];
bool is_prm[MAXN];
vector<int> prm_fac[MAXN];
int prm_use[MAXN];
bool state[MAXN];

int main()
{

    int n, m;
    cin >> n >> m;

    int prm_cnt = get_prime(n + 1, prm, is_prm);
    for (int i = 2; i <= n; i++) {
        int p = i;
        for (int j = 0; j < prm_cnt && prm[j] <= p; j++)
            if (p % prm[j] == 0) {
                prm_fac[i].push_back(j);
                while (p % prm[j] == 0) p /= prm[j];
            }
    }

    for (int i = 0; i < m; i++) {
        char c;
        int id;
        cin >> c >> id;

        if (c == '-') {
            if (state[id]) {
                for (int j = 0; j < prm_fac[id].size(); j++)
                    prm_use[prm_fac[id][j]] = 0;
                state[id] = false;
                cout << "Success";
            }
            else cout << "Already off";
            goto loop_continue;
        }

        if (state[id]) {
            cout << "Already on";
            goto loop_continue;
        }

        for (int j = 0; j < prm_fac[id].size(); j++)
            if (prm_use[prm_fac[id][j]]) {
                cout << "Conflict with " << prm_use[prm_fac[id][j]];
                goto loop_continue;
            }

        for (int j = 0; j < prm_fac[id].size(); j++)
            prm_use[prm_fac[id][j]] = id;
        state[id] = true;
        cout << "Success";

loop_continue:
        cout << endl;
    }

    return 0;
}


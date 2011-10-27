/*
 *  SRC: NKOJ 2135
 * PROB: An Industrial Spy
 * ALGO: Prime
 * DATE: Aug 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::next_permutation;

const int MAX_N = 10000000;

int prm[670000];
bool isPrm[MAX_N];

int n, m, job;
char s[10];
int pos[10], used[10], chk[MAX_N];

int getPrime(int n, int* p, bool* b)
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

int generate(int prev, int depth)
{
    if (depth == m) {
        int cnt = 0;
        do {
            int num = 0;
            for (int i = 0; i < m; i++)
                num = num * 10 + s[pos[i]] - '0';
            if (isPrm[num] && chk[num] != job) {
                cnt++;
                chk[num] = job;
            }
        } while (next_permutation(pos, pos + m)) ;

        return cnt;
    }

    int cnt = 0;
    for (int i = prev + 1; i < n; i++)
        if (!used[i]) {
            used[i] = 1;
            pos[depth] = i;
            cnt += generate(i, depth + 1);
            used[i] = 0;
        }

    return cnt;
}

int main()
{
    getPrime(MAX_N, prm, isPrm);

    int jobs;
    scanf("%d", &jobs);
    for (job = 1; job <= jobs; job++) {
        scanf("%s", s);
        n = strlen(s);
        long long cnt = 0;
        for (m = 1; m <= n; m++) {
            memset(used, 0, sizeof(used));
            cnt += generate(-1, 0);
        }

        printf("%lld\n", cnt);
    }

    return 0;
}

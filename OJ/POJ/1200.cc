/*
 *  SRC: POJ 1200
 * PROB: Crazy Search
 * ALGO: Hash
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MOD = 16000001;
int pair[256];
bool hashTable[MOD];

int n, nc;
char s[16000001];

int hash(char *str)
{
    unsigned res = 0;
    for (int i = 0; i < n; i++)
        res = res * nc + pair[str[i]];

    return res % MOD;
}

int main()
{
    scanf("%d%d%s", &n, &nc, s);

    int cnt = 0, len = strlen(s);

    memset(pair, -1, sizeof(pair));
    for (int i = 0; i < len; i++) {
        if (pair[s[i]] == -1) pair[s[i]] = cnt++;
        if (cnt == nc) break;
    }

    cnt = 0;
    for (int i = 0; i + n <= len; i++) {
        int val = hash(s + i);
        if (!hashTable[val]) {
            hashTable[val] = 1;
            cnt++;
        }
    }

    printf("%d\n", cnt);

    return 0;
}

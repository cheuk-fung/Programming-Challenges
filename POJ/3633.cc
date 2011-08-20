/*
 *  SRC: POJ 3633
 * PROB: Copying DNA
 * ALGO: BFS
 * DATE: Aug 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

struct Node {
    int u, s;
} QBuf[1000000];

char S[20], T[20];
int sLen, tLen, final;
bool inS[20][20], inT[20][20][20][20];
bool vis[1 << 20];

Node* head;
Node* tail;

inline void expand(int v, int s)
{
    tail->u = v;
    tail->s = s;
    tail++;
    vis[v] = 1;
}

bool canExpand(int u, int l, int r)
{
    if (inS[l][r]) return 1;
    for (int i = 0; i < tLen; i++)
        if (u & (1 << i)) {
            int j = i;
            while (u & (1 << j)) j++;
            if (inT[l][r][i][j - 1]) return 1;
            i = j - 1;
        }

    return 0;
}

int bfs()
{
    memset(vis, 0, sizeof(vis));

    final = (1 << tLen) - 1;

    head = tail = QBuf;
    expand(0, 0);

    while (head != tail) {
        int u = head->u,
            s = head->s;
        head++;

        for (int i = 0; i < tLen; i++)
            if (!(u & (1 << i))) {
                int j = i, v = u;
                while (!(u & (1 << j)) && j < tLen) {
                    v |= (1 << j);
                    j++;
                }
                for (j--; j >= i; j--) {
                    if (vis[v] || !canExpand(u, i, j)) v ^= (1 << j);
                    else {
                        if (v == final) return s + 1;
                        expand(v, s + 1);
                    }
                }
            }
    }

    return -1;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%s%s", S, T);
        sLen = strlen(S);
        tLen = strlen(T);

        memset(inS, 0, sizeof(inS));
        for (int i = 0; i < tLen; i++)
            for (int j = i; j < tLen; j++) {
                int len = j - i + 1;
                for (int k = 0; k + len - 1 < sLen; k++) {
                    int chk = 0;
                    for  (int l = 0; l < len; l++, chk++)
                        if (T[i + l] != S[k + l]) break;
                    if (chk == len) inS[i][j] = 1;
                }
                for (int k = sLen; k - len + 1 >= 0; k--) {
                    int chk = 0;
                    for (int l = 0; l < len; l++, chk++)
                        if (T[i + l] != S[k - l]) break;
                    if (chk == len) inS[i][j] = 1;
                }
            }

        memset(inT, 0, sizeof(inT));
        for (int i = 0; i < tLen; i++)
            for (int j = i; j < tLen; j++) {
                int len = j - i + 1;
                for (int l = 0, r = l + len - 1; r < tLen; l++, r++) {
                    int chk = 0;
                    for (int k = 0; k < len; k++, chk++)
                        if (T[i + k] != T[l + k]) break;

                    if (chk != len) {
                        chk = 0;
                        for (int k = 0; k < len; k++, chk++)
                            if (T[i + k] != T[r - k]) break;
                    }

                    if (chk == len) {
                        for (int p = l; p >= 0; p--)
                            for (int q = r; q < tLen; q++)
                                inT[i][j][p][q] = 1;
                    }
                }
            }

        int ans = bfs();
        if (ans == -1) puts("impossible");
        else printf("%d\n", ans);
    }

    return 0;
}

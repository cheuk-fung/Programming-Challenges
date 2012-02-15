/*
 *  SRC: HDOJ 3722
 * PROB: Card Game
 * ALGO: KM
 * DATE: Oct 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAXN = 300;
const int INF = 0x3f3f3f3f;

int n;
int  w[MAXN][MAXN],
     lx[MAXN], ly[MAXN],
     match[MAXN], slack[MAXN];
bool visx[MAXN], visy[MAXN];

bool find_path(int x)
{
    visx[x] = true;
    for (int y = 0; y < n; y++) {
        if (visy[y]) continue;
        int t = lx[x] + ly[y] - w[x][y];
        if (t == 0) {
            visy[y] = true;
            if (match[y] == -1 || find_path(match[y])) {
                match[y] = x;
                return true;
            }
        }
        else if (slack[y] > t) slack[y] = t;
    }
    return false;
}

int KM()
{
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    memset(match, 0xff, sizeof(match));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (lx[i] < w[i][j]) lx[i] = w[i][j];

    for (int x = 0; x < n; x++) {
        memset(slack, 0x3f, sizeof(slack));
        while (1) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if (find_path(x)) break;

            int d = INF;
            for (int i = 0; i < n; i++)
                if (!visy[i] && slack[i] < d) d = slack[i];
            for (int i = 0; i < n; i++)
                if (visx[i]) lx[i] -= d;
            for (int i = 0; i < n; i++) {
                if (visy[i]) ly[i] += d;
                else slack[i] -= d;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) res += w[match[i]][i];
    return res;
}

char card[MAXN][1010];

int eval_w(char *a, char *b)
{
    int len_a = strlen(a) - 1;

    int res = 0;
    while (len_a >= 0 && *b && a[len_a] == *b) res++, len_a--, b++;
    return res;
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) scanf("%s", card[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i == j) w[i][j] = 0;
                else w[i][j] = eval_w(card[i], card[j]);
            }
        printf("%d\n", KM());
    }

    return 0;
}

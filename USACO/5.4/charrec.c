/*
ID: os.idea1
LANG: C
TASK: charrec
*/
#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

FILE *font, *fin, *fout;

char *charset = " abcdefghijklmnopqrstuvwxyz";
char fonts[27][20][21];
char image[1200][21];
int  n;

int  diff[27][20][1200];
int  g[1200][3];
int  f[1200], pre[1200];
char g_char[1200][3], f_char[1200];
char ans[1201];

inline int min(int a, int b) { return a < b ? a : b; }

int evla_diff(char *a, char *b)
{
    int res = 0;
    while (*a) {
        if (*a != *b) res++;
        a++, b++;
    }
    return res;
}

int main()
{
    font = fopen("font.in", "r");
    fin  = fopen("charrec.in", "r");
    fout = fopen("charrec.out", "w");

    int i;
    
    fscanf(font, "%*d");
    for (i = 0; i < 27; i++) {
        int j;
        for (j = 0; j < 20; j++)
            fscanf(font, "%s", fonts[i][j]);
    }

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++)
        fscanf(fin, "%s", image[i]);

    for (i = 0; i < 27; i++) {
        int j, k;
        for (j = 0; j < 20; j++)
            for (k = 0; k < n; k++)
                diff[i][j][k] = evla_diff(fonts[i][j], image[k]);
    }

    memset(g, 0x3f, sizeof(g));

    for (i = 0; i < n; i++) {
        int j, k;
        for (j = 0; j < 27; j++) {
            int cnt;
            if (i + 19 <= n) {
                int omit, l;
                for (omit = 0; omit < 20; omit++) {
                    for (k = l = cnt = 0; k < 20; k++, l++) {
                        if (k == omit) k++;
                        cnt += diff[j][k][i + l];
                    }
                    if (cnt < g[i][0]) {
                        g[i][0] = cnt;
                        g_char[i][0] = charset[j];
                    }
                }
            }
            if (i + 20 <= n) {
                for (k = 0, cnt = 0; k < 20; k++)
                    cnt += diff[j][k][i + k];
                if (cnt < g[i][1]) {
                    g[i][1] = cnt;
                    g_char[i][1] = charset[j];
                }
            }
            if (i + 21 <= n) {
                int dupl, l;
                for (dupl = 0; dupl < 20; dupl++) {
                    for (k = l = cnt = 0; k < 20; k++, l++) {
                        if (k != dupl) cnt += diff[j][k][i + l];
                        else {
                            cnt += min(diff[j][k][i + l], diff[j][k][i + l + 1]);
                            l++;
                        }
                    }
                    if (cnt < g[i][2]) {
                        g[i][2] = cnt;
                        g_char[i][2] = charset[j];
                    }
                }
            }
        }
    }

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    f[19] = f[0] + g[0][0];
    f_char[19] = g_char[0][0];
    f[20] = f[0] + g[0][1];
    f_char[20] = g_char[0][1];
    f[21] = f[0] + g[0][2];
    f_char[21] = g_char[0][2];
    pre[19] = pre[20] = pre[21] = 0;
    for (i = 22; i <= n; i++) {
        int t19 = f[i - 19] + g[i - 19][0],
            t20 = f[i - 20] + g[i - 20][1],
            t21 = f[i - 21] + g[i - 21][2];
        if (t19 < f[i]) {
            f[i] = t19;
            f_char[i] = g_char[i - 19][0];
            pre[i] = i - 19;
        }
        if (t20 < f[i]) {
            f[i] = t20;
            f_char[i] = g_char[i - 20][1];
            pre[i] = i - 20;
        }
        if (t21 < f[i]) {
            f[i] = t21;
            f_char[i] = g_char[i - 21][2];
            pre[i] = i - 21;
        }
    }

    int idx = n, ans_p = 0;
    while (idx) {
        ans[ans_p++] = f_char[idx];
        idx = pre[idx];
    }
    for (i = ans_p - 1; i >= 0; i--) putc(ans[i], fout);
    putc(10, fout);

    return 0;
}

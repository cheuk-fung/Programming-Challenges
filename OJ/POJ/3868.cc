/*
 *  SRC: POJ 3868
 * PROB: Garbling Game
 * ALGO: Math
 * DATE: Jul 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int ten[] = {1, 10, 100, 1000};

class Big_Integer {
    private:
        int len;
        int a[100];

    public:
        Big_Integer()
        {
            len = 0;
            memset(a, 0, sizeof(a));
        }

        Big_Integer(char *s)
        {
            len = -1;
            memset(a, 0, sizeof(a));

            char *t = s;
            while (*t) t++;
            t--;
            for (int i = 0; *(s + i); i++, t--) {
                if (i % 4 == 0) len++;
                a[len] += (*t - '0') * ten[i % 4];
            }
        }

        bool is_zero() const
        {
            return len == 0 && a[0] == 0;
        }

        int divide(int m)
        {
            int remain = 0;
            for (int i = len; i >= 0; i--) {
                int x = remain * 10000 + a[i];
                remain = x % m;
                a[i] = x / m;
            }

            while (len > 0 && a[len] == 0) len--;

            return remain;
        }

        void print() const
        {
            for (int i = len; i >= 0; i--) {
                printf("%04d", a[i]);
            }
            putchar(10);
        }
};

int tot, r, c;
char change[333][333];
int rcnt[100000], pcnt[100000], tcnt[100000];
int rperm[100000], pperm[100000], tperm[100000];
int rmat[333][333], pmat[333][333], tmat[333][333];

void rotate_left(int mat[333][333], int x, int y)
{
    int t = mat[x][y];
    mat[x][y] = mat[x][y + 1];
    mat[x][y + 1] = mat[x + 1][y + 1];
    mat[x + 1][y + 1] = mat[x + 1][y];
    mat[x + 1][y] = t;
}

void rotate_right(int mat[333][333], int x, int y)
{
    int t = mat[x][y];
    mat[x][y] = mat[x + 1][y];
    mat[x + 1][y] = mat[x + 1][y + 1];
    mat[x + 1][y + 1] = mat[x][y + 1];
    mat[x][y + 1] = t;
}

void gen(int mat[333][333], int *cnt, int *perm, int loop)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            mat[i][j] = i * c + j;

    for (int i = 0; i < r - 1; i++)
        for (int j = 0; j < c - 1; j++) {
            if (loop-- == 0) return ;

            cnt[mat[i][j]]++;
            switch (change[i][j]) {
                case 'L': rotate_left(mat, i, j); break;
                case 'R': rotate_right(mat, i, j);
            }
        }

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            perm[mat[i][j]] = i * c + j;
}

void multiply(int *perm, int *cnt, int *operm, int *ocnt)
{
    for (int i = 0; i < tot; i++) {
        tcnt[i] = (cnt[i] + ocnt[perm[i]]) % 100000;
        tperm[i] = operm[perm[i]];
    }
    for (int i = 0; i < tot; i++) {
        ocnt[i] = tcnt[i];
        operm[i] = tperm[i];
    }
}

int main()
{
    scanf("%d%d", &r, &c);
    tot = r * c;
    char s[111];
    scanf("%s", s);
    Big_Integer n(s);

    int loop = (r - 1) * (c - 1);
    for (int i = 0; i < r - 1; i++) scanf("%s", change[i]);

    gen(rmat, rcnt, rperm, n.divide(loop));
    gen(pmat, pcnt, pperm, loop);
    while (!n.is_zero()) {
        if (n.divide(2)) {
            multiply(pperm, pcnt, rperm, rcnt);
        }
        multiply(pperm, pcnt, pperm, pcnt);
    }

    for (int i = 0; i < tot; i++) printf("%d\n", rcnt[i]);

    return 0;
}

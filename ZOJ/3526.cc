/*
 *  SRC: ZOJ 3526
 * PROB: Weekend Party
 * ALGO: NULL
 * DATE: Oct 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int mat[10][10];
int perm[10];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        int A = 0, C = 0, G = 0, AC = 0, AG = 0, CG = 0, ACG = 0;
        for (int i = 0; i < n; i++) {
            char fav[10];
            scanf(" %*s %s", fav);
            int len = strlen(fav);
            if (len == 3) ACG++;
            else if (len == 2) {
                if (strcmp(fav, "AC") == 0 || strcmp(fav, "CA") == 0) {
                    AC++;
                } else if (strcmp(fav, "AG") == 0 || strcmp(fav, "GA") == 0) {
                    AG++;
                } else if (strcmp(fav, "CG") == 0 || strcmp(fav, "GC") == 0) {
                    CG++;
                }
            } else {
                if (fav[0] == 'A') A++;
                else if (fav[0] == 'C') C++;
                else if (fav[0] == 'G') G++;
            }
        }

        int idx = 0;
        if (A) perm[idx++] = 1;
        if (C) perm[idx++] = 2;
        if (G) perm[idx++] = 4;
        for (int i = 0; i < min(2, AC); i++) perm[idx++] = 3;
        for (int i = 0; i < min(2, AG); i++) perm[idx++] = 5;
        for (int i = 0; i < min(2, CG); i++) perm[idx++] = 6;

        memset(mat, 0, sizeof mat);
        for (int i = 0; i < idx; i++) {
            for (int j = 0; j < idx; j++) {
                if (perm[i] & perm[j]) mat[i][j] = 1;
            }
        }

        for (int i = 0; i < idx; i++) perm[i] = i;
        bool ok;
        do {
            ok = true;
            int t = ACG;
            for (int i = 0; i < idx; i++) {
                int j = (i + 1) % idx;
                if (!mat[perm[i]][perm[j]]) {
                    if (t) t--;
                    else {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) break;
        } while (next_permutation(perm, perm + idx));

        puts(ok ? "Yes" : "No");
    }

    return 0;
}


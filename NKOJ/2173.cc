/*
 *  SRC: NKOJ 2173
 * PROB: High Score
 * ALGO: String
 * DATE: Aug 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;
using std::swap;

char name[1010];
int len;

int get_best() {
    int best = len - 1;
    for (int i = 0; i < len; i++) {
        if (name[i] == 'A') {
            int j = i;
            while (name[j] == 'A') j++;
            best = min(best, (i ? i - 1 : 0) * 2 + len - j);
            i = j - 1;
        }
    }

    return best;
}

int main() {
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%s", name);
        len = strlen(name);
        int ans = 0;
        for (int i = 0; i < len; i++)
            ans += min(name[i] - 'A', 26 - (name[i] - 'A'));

        if (ans == 0 || len == 1)
        {
            printf("%d\n", ans);
            continue;
        }

        int best = get_best();
        for (int i = 1, j = len - 1; i < j; i++, j--) swap(name[i], name[j]);
        best = min(best, get_best());

        printf("%d\n", ans + best);
    }

    return 0;
}

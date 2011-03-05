/*
 *  SRC: POJ
 * TASK: Gone Fishing
 * ALGO: Greedy
 * DATE: Dec. 3, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

bool fishing()
{
    int n, h;
    scanf("%d", &n);
    if (!n) return false;
    scanf("%d", &h);
    h *= 12;

    int fi[n], di[n], ti[n];
    for (int i = 0; i < n; i++) scanf("%d", &fi[i]);
    for (int i = 0; i < n; i++) scanf("%d", &di[i]);
    ti[0] = 0;
    for (int i = 1; i < n; i++) {
	int tmp;
	scanf("%d", &tmp);
	ti[i] = ti[i - 1] + tmp;
    }

    int max = 0, ans[n];
    for (int i = 0; i < n; i++) ans[i] = 0;
    for (int stop = 0; stop < n; stop++) {
	int lake[stop + 1], fishtime[stop + 1], time = h - ti[stop], tot = 0;
	for (int i = 0; i <= stop; i++) {
	    lake[i] = fi[i];
	    fishtime[i] = 0;
	}
	for (int i = 0; i < time; i++) {
	    int maxfi = lake[0], now = 0;
	    for (int j = 1; j <= stop; j++)
		if (lake[j] > maxfi) {
		    maxfi = lake[j];
		    now = j;
		}
	    tot += maxfi;
	    lake[now] -= di[now];
	    if (lake[now] < 0) lake[now] = 0;
	    fishtime[now]++;
	}
	if (tot < max) continue;
	if (tot == max) {
	    int i;
	    for (i = 0; i <= stop; i++)
		if (ans[i] != fishtime[i]) break;
	    if (i > stop || ans[i] > fishtime[i]) continue;
	}
	for (int i = 0; i <= stop; i++) ans[i] = fishtime[i];
	max = tot;
    }
    printf("%d", ans[0] * 5);
    for (int i = 1; i < n; i++) printf(", %d", ans[i] * 5);
    printf("\nNumber of fish expected: %d\n\n", max);

    return true;
}

int main()
{
    while (fishing()) ;

    return 0;
}


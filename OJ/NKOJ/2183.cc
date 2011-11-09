/*
 *  SRC: NKOJ 2183
 * PROB: Exercise 3 食堂打饭
 * ALGO: Greedy
 * DATE: Oct 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include<cstdio>
#include<algorithm>
#include<queue>

using std::priority_queue;
using std::sort;

priority_queue<int> Q;

int n, m, a[10000];
double ans;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) Q.push(0);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        int u = Q.top();
        Q.pop();
        u -= a[i];
        ans -= u;
        Q.push(u);
    }
    printf("%.3f\n",ans / n);
    return 0;
}

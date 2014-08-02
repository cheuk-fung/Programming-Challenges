/*
 *  SRC: POJ 3253
 * PROB: Fence Repair
 * ALGO: Huffman
 * DATE: Sep 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;
using std::greater;

int n;
priority_queue< int, vector<int>, greater<int> > pq;

int main()
{
    scanf("%d", &n);
    for (int i = 0, t; i < n; i++) {
        scanf("%d", &t);
        pq.push(t);
    }

    if (n == 1) {
        printf("%d\n", pq.top());
        return 0;
    }

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        pq.push(a + b);
        ans += a + b;
    }

    printf("%lld\n", ans);

    return 0;
}

/*
 *  SRC: POJ 2823
 * PROB: Sliding Window
 * ALGO: Monotone Priority Queue
 * DATE: Jul 20, 2011 
 * COMP: c++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

struct Node {
    int val, time;
};

Node minQ[1000000], maxQ[1000000];
int minAns[10000000], maxAns[10000000];

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    int minHead = 0, minTail = 0;
    int maxHead = 0, maxTail = 0;
    for (int i = 0; i < k; i++) {
        int v;
        scanf("%d", &v);
        while (minHead < minTail) {
            if (minQ[minTail - 1].val >= v) minTail--;
            else break;
        }
        minQ[minTail].val = v;
        minQ[minTail++].time = i;

        while (maxHead < maxTail) {
            if (maxQ[maxTail - 1].val <= v) maxTail--;
            else break;
        }
        maxQ[maxTail].val = v;
        maxQ[maxTail++].time = i;
    }

    int cnt = 0;
    minAns[cnt] = minQ[minHead].val;
    maxAns[cnt++] = maxQ[maxHead].val;

    for (int i = k; i < n; i++) {
        int v;
        scanf("%d", &v);

        while (minHead < minTail) {
            if (minQ[minTail - 1].val >= v) minTail--;
            else break;
        }
        while (minHead < minTail) {
            if (minQ[minHead].time <= i - k) minHead++;
            else break;
        }
        minQ[minTail].val = v;
        minQ[minTail++].time = i;

        while (maxHead < maxTail) {
            if (maxQ[maxTail - 1].val <= v) maxTail--;
            else break;
        }
        while (maxHead < maxTail) {
            if (maxQ[maxHead].time <= i - k) maxHead++;
            else break;
        }
        maxQ[maxTail].val = v;
        maxQ[maxTail++].time = i;

        minAns[cnt] = minQ[minHead].val;
        maxAns[cnt++] = maxQ[maxHead].val;
    }

    printf("%d", minAns[0]);
    for (int i = 1; i < cnt; i++) printf(" %d", minAns[i]);
    putchar(10);

    printf("%d", maxAns[0]);
    for (int i = 1; i < cnt; i++) printf(" %d", maxAns[i]);
    putchar(10);

    return 0;
}

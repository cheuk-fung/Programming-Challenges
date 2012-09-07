/*
 *  SRC: HDOJ 4006
 * PROB: The kth great number
 * ALGO: Priority queue
 * DATE: Sep 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

priority_queue<int, vector<int>, greater<int> > pri_que;

int main()
{
    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        while (!pri_que.empty()) pri_que.pop();
        for (int i = 0; i < n; i++) {
            char opr;
            scanf(" %c", &opr);
            if (opr == 'I') {
                int d;
                scanf("%d", &d);
                pri_que.push(d);
                if ((int)pri_que.size() > k) pri_que.pop();
            } else {
                printf("%d\n", pri_que.top());
            }
        }
    }

    return 0;
}


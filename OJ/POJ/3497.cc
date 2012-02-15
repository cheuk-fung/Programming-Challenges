/*
 *  SRC: POJ 3497
 * PROB: Assemble
 * ALGO: Bisection
 * DATE: Feb 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Hardware {
    int p, q;
};

struct Link {
    Hardware hw;
    Link *next;
};
Link l_buf[1010],
     *l_head[1010],
     *l_tail;

map<string, int> hw_id;
int n, b, id = 0;
char c_buf[100];

void add_link(int id, const Hardware &hw)
{
    *l_tail = (Link){hw, l_head[id]};
    l_head[id] = l_tail++;
}

bool check(int min_q)
{
    int tot = 0;
    for (int i = 0; i < id; i++) {
        int min_p = INF;
        for (Link *l = l_head[i]; l; l = l->next)
            if (l->hw.q >= min_q && l->hw.p < min_p)
                min_p = l->hw.p;
        if (min_p == INF) return false;
        tot += min_p;
    }

    return tot <= b;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        id = 0;
        hw_id.clear();
        l_tail = l_buf;
        memset(l_buf, 0, sizeof(l_buf));
        memset(l_head, 0, sizeof(l_head));

        scanf("%d%d", &n, &b);
        Hardware hw;
        string s;
        for (int i = 0; i < n; i++) {
            scanf("%s%*s%d%d", c_buf, &hw.p, &hw.q);
            s = c_buf;
            if (!hw_id.count(s)) hw_id[s] = id++;
            add_link(hw_id[s], hw);
        }

        int l = 0, r = 1000000010;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        printf("%d\n", l);
    }

    return 0;
}

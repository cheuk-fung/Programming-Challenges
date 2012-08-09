/*
 *  SRC: HDOJ 4350
 * PROB: Card
 * ALGO: NULL
 * DATE: Aug 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<string> card;
int c[52], tc[52];
char strbuf[10];
vector<string> ans;

string tostring()
{
    string res;
    for (int i = 0; i < 52; i++) {
        sprintf(strbuf, " %d", c[i]);
        res += strbuf;
    }
    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        card.clear();
        ans.clear();

        for (int i = 0; i < 52; i++) {
            scanf("%d", c + i);
        }

        int n, l, r;
        scanf("%d%d%d", &n, &l, &r);

        string s = tostring();
        card.insert(s);
        ans.push_back(s);
        while (true) {
            memcpy(tc, c + l - 1, sizeof(int) * (r - l + 1));
            memcpy(tc + (r - l + 1), c, sizeof(int) * (l - 1));
            memcpy(tc + r, c + r, sizeof(int) * (52 - r + 1));
            memcpy(c, tc, sizeof(int) * 52);
            s = tostring();
            if (card.count(s)) break;
            card.insert(s);
            ans.push_back(s);
        }

        printf("Case #%d:%s\n", task, ans[n % ans.size()].c_str());
    }

    return 0;
}


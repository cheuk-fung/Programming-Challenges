/*
 *  SRC: HDOJ 4252
 * PROB: A Famous City
 * ALGO: stack
 * DATE: Jul 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <stack>

using namespace std;

stack<int> s;

int main()
{
    int task = 1;
    int n;
    while (~scanf("%d", &n)) {
        while (!s.empty()) s.pop();
        s.push(0);

        printf("Case %d: ", task++);

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int h;
            scanf("%d", &h);

            if (h > s.top()) {
                ans++;
                s.push(h);
            } else if (h < s.top()) {
                while (h < s.top()) {
                    s.pop();
                }
                if (h > s.top()) {
                    ans++;
                    s.push(h);
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}


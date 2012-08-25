/*
 *  SRC: HDOJ 4259
 * PROB: Double Dealing
 * ALGO: NULL
 * DATE: Aug 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int hash[1000], vis[1000];
vector<int> player[1000];

int main()
{
    int n, k;
    while (scanf("%d%d", &n, &k), n || k) {
        for (int i = 0; i < k; i++) {
            player[i].clear();
        }
        for (int i = 0; i < n; i++) {
            player[i % k].push_back(i);
            vis[i] = 0;
        }

        int cnt = 0;
        for (int i = 0; i < k; i++) {
            for (int j = player[i].size() - 1; j >= 0; j--) {
                hash[player[i][j]] = cnt++;
            }
        }

        long long ans = 1;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                long long size = 0;
                int j = i;
                while (!vis[j]) {
                    vis[j] = 1;
                    size++;
                    j = hash[j];
                }
                j = hash[j];
                long long g = __gcd(ans, size);
                ans = ans / g * size;
            }
        }

        printf("%I64d\n", ans);
    }

    return 0;
}


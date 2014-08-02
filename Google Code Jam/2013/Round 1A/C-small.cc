#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <ctime>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> triple;

int main()
{
    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        int R, N, M, K;
        cin >> R >> N >> M >> K;
        map<triple, set<int> > predict;
        for (int i = 2; i <= M; i++) {
            for (int j = 2; j <= M; j++) {
                for (int k = 2; k <= M; k++) {
                    triple now(i, pii(j, k));
                    for (int a = 0; a < 2; a++) {
                        for (int b = 0; b < 2; b++) {
                            for (int c = 0; c < 2; c++) {
                                predict[now].insert((a ? i : 1) * (b ? j : 1) * (c ? k : 1));
                            }
                        }
                    }
                }
            }
        }
        cout << "Case #" << task << ":" << endl;
        for (int i = 0; i < R; i++) {
            vector<int> sub;
            for (int j = 0; j < K; j++) {
                int v;
                cin >> v;
                sub.push_back(v);
            }
            for (map<triple, set<int> >::const_iterator it = predict.begin(); it != predict.end(); it++) {
                bool chk = true;
                for (int j = 0; j < K; j++) {
                    if (it->second.count(sub[j]) == 0) {
                        chk = false;
                        break;
                    }
                }
                if (chk) {
                    cout << it->first.first << it->first.second.first << it->first.second.second << endl;
                    goto next;
                }
            }
            cout << 222 << endl;
next:
            ;
        }
    }

    return 0;
}

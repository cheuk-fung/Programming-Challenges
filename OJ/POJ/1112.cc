/*
 *  SRC: POJ 1112
 * PROB: Team Them Up!
 * ALGO: DP
 * DATE: Oct 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

typedef pair< vector<int>, vector<int> > pvv;
bool mat[110][110];

bool check(const vector<int> &team)
{
    for (int i = 0; i < (int)team.size(); i++) {
        for (int j = i + 1; j < (int)team.size(); j++) {
            int u = team[i], v = team[j];
            if (!mat[u][v] || !mat[v][u]) return false;
        }
    }
    return true;
}

bool run(int n)
{
    bool avail[110];
    memset(avail, true, sizeof avail);
    vector<pvv> teams;

    while (true) {
        int person = -1;
        for (int i = 0; i < n; i++) {
            if (avail[i]) {
                person = i;
                break;
            }
        }
        if (person == -1) break;

        vector<int> team[2];
        team[0].push_back(person);

        bool vis[2][110];
        memcpy(vis[0], mat[person], sizeof vis[0]);
        memset(vis[1], true, sizeof vis[1]);
        vis[1][person] = avail[person] = false;

        int now = 0;
        bool add = true;
        while (add) {
            add =false;

            for (int i = 0; i < n; i++) {
                if (!avail[i]) continue;
                if (!vis[now][i]) {
                    if (!vis[now ^ 1][i]) return false;

                    add = true;
                    team[now ^ 1].push_back(i);
                    avail[i] = false;
                    for (int j = 0; j < n; j++) {
                        if (vis[now ^ 1][j] && !mat[i][j]) {
                            vis[now ^ 1][j] = false;
                        }
                    }
                }
            }
            now ^= 1;
        }

        if (team[0].size() >= team[1].size()) {
            teams.push_back(make_pair(team[0], team[1]));
        } else {
            teams.push_back(make_pair(team[1], team[0]));
        }
    }

    pvv f[110][110];
    f[0][(int)teams[0].first.size() - (int)teams[0].second.size()] = teams[0];
    for (int i = 1; i < (int)teams.size(); i++) {
        int diff = (int)teams[i].first.size() - (int)teams[i].second.size();
        for (int j = 0; j <= n; j++) {
            if (j - diff >= 0 && !f[i - 1][j - diff].first.empty()) {
                f[i][j] = teams[i];
                f[i][j].first.insert(f[i][j].first.end(), f[i - 1][j - diff].first.begin(), f[i - 1][j - diff].first.end());
                f[i][j].second.insert(f[i][j].second.end(), f[i - 1][j - diff].second.begin(), f[i - 1][j - diff].second.end());
            } else if (diff - j >= 0 && !f[i - 1][diff - j].first.empty()) {
                f[i][j] = teams[i];
                f[i][j].first.insert(f[i][j].first.end(), f[i - 1][diff - j].second.begin(), f[i - 1][diff - j].second.end());
                f[i][j].second.insert(f[i][j].second.end(), f[i - 1][diff - j].first.begin(), f[i - 1][diff - j].first.end());
            } else if (j + diff <= n && !f[i - 1][j + diff].first.empty()) {
                f[i][j].first = teams[i].second;
                f[i][j].second = teams[i].first;
                f[i][j].first.insert(f[i][j].first.end(), f[i - 1][j + diff].first.begin(), f[i - 1][j + diff].first.end());
                f[i][j].second.insert(f[i][j].second.end(), f[i - 1][j + diff].second.begin(), f[i - 1][j + diff].second.end());
            }
        }
    }

    for (int i = 0; i < n; i++) {
        pvv &now = f[teams.size() - 1][i];
        if (!now.first.empty()) {
            assert(check(now.first) && check(now.second));
            printf("%d", now.first.size());
            for (int j = 0; j < (int)now.first.size(); j++) {
                printf(" %d", now.first[j] + 1);
            }
            putchar(10);
            printf("%d", now.second.size());
            for (int j = 0; j < (int)now.second.size(); j++) {
                printf(" %d", now.second[j] + 1);
            }
            putchar(10);
            break;
        }
    }

    return true;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        memset(mat, false, sizeof mat);
        for (int i = 0; i < n; i++) {
            for (int j; scanf("%d", &j), j != 0; ) {
                mat[i][j - 1] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] && !mat[j][i]) mat[i][j] = false;
            }
        }

        if (!run(n)) puts("No solution");
    }

    return 0;
}


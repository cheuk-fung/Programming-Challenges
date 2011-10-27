/*
 *  SRC: HDOJ 3720
 * PROB: Arranging Your Team
 * ALGO: NULL
 * DATE: Oct 15, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::map;
using std::vector;

int m;
int v[23], add[23][23];
bool choose[23];
vector<int> pos[4];
map<string, int> name;
const int need[4] = { 4, 4, 2, 1 };

int best;

inline int get_pos(char c)
{
    switch (c) {
        case 'd': return 0;
        case 'm': return 1;
        case 's': return 2;
        case 'g': return 3;
    }
}

void choose_person(int p, int prev, int cnt)
{
    if (p == 4) {
        int res = 0;
        for (int i = 0; i < 23; i++)
            if (choose[i]) {
                res += v[i];
                for (int j = i + 1; j < 23; j++)
                if (choose[j]) res += add[i][j];
            }
        if (res > best) best = res;
        return ;
    }
    if (cnt == need[p]) return choose_person(p + 1, -1, 0);

    int res = 0;
    for (int i = prev + 1; i < pos[p].size(); i++) {
        choose[pos[p][i]] = true;
        choose_person(p, i, cnt + 1);
        choose[pos[p][i]] = false;
    }
}

bool work()
{
    memset(v, 0, sizeof(v));
    memset(add, 0, sizeof(add));
    memset(choose, 0, sizeof(choose));
    for (int i = 0; i < 4; i++) pos[i].clear();
    name.clear();

    char str[50];
    for (int i = 0; i < 23; i++) {
        if (scanf("%s", str) == EOF) return false;
        name[string(str)] = i;
        scanf("%d%s", v + i, str);
        pos[get_pos(str[0])].push_back(i);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%s", str);
        a = name[string(str)];
        scanf("%s", str);
        b = name[string(str)];
        scanf("%d", &add[a][b]);
        add[b][a] = add[a][b];
    }

    if (pos[0].size() < 4 || pos[1].size() < 4 || pos[2].size() < 2 || pos[3].size() < 1) {
        puts("impossible");
        return true;
    }

    best = -0x3f3f3f3f;
    choose_person(0, -1, 0);
    printf("%d\n", best);

    return true;
}

int main()
{
    while (work()) ;

    return 0;
}

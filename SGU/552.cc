#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

char property[4][20], key[4][10], value[4][10];
pair<string, string> info[4];
map<string, int> here;

void getinfo(int l)
{
    for (int j = 0; j < l; j++) {
        scanf("%s", property[j]);
        int k;
        for (k = 0; property[j][k] != '='; k++) ;
        property[j][k] = '\0';
        strcpy(key[j], property[j]);
        strcpy(value[j], property[j] + k + 1);
        info[j] = pair<string, string>(key[j], value[j]);
    }
    sort(info, info + l);
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int l;
        scanf("%d", &l);
        getinfo(l);
        for (int i = 1; i < 1 << l; i++) {
            string now = "";
            for (int j = 0; j < l; j++) {
                if (i & (1 << j)) now += info[j].first + "=" + info[j].second + " ";
            }
            here[now]++;
        }
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int l;
        scanf("%d", &l);
        getinfo(l);
        string now = "";
        for (int i = 0; i < l; i++) now += info[i].first + "=" + info[i].second + " ";
        printf("%d\n", here[now]);
    }

    return 0;
}

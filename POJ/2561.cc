/*
 *  SRC: POJ 2561
 * PROB: Language Cardinality
 * ALGO: String
 * DATE: Oct 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <string>
#include <set>
#include <utility>

using namespace std;

typedef pair<string, string> pss;

int n;
pss rules[110];
set<string> strings;
char buf[100];

struct too_many {};

void dfs(const string &u)
{
    for (int i = 0; i < n; i++) {
        size_t pos = -1;
        while ((pos = u.find(rules[i].first, pos + 1)) != string::npos) {
            string v = u;
            v.replace(pos, rules[i].first.length(), rules[i].second);
            if (strings.insert(v).second) {
                if (strings.size() > 1000) {
                    throw too_many();
                }
                dfs(v);
            }
        }
    }
}

int main()
{
    scanf("%s", buf);
    string init(buf);

    while (~scanf("%s", buf)) {
        string a = "";
        char *s = buf + 1;
        while (*s != '"') a += *s++;
        s += 4;
        string b = "";
        while (*s != '"') b += *s++;
        rules[n++] = pss(a, b);
    }

    strings.insert(init);
    try {
        dfs(init);
        printf("%d\n", strings.size());
    } catch (const too_many &) {
        puts("Too many.");
    }

    return 0;
}


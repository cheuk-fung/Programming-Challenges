/*
 *  SRC: HDOJ 4329
 * PROB: MAP
 * ALGO: NULL
 * DATE: Jul 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <map>

using namespace std;

char buf[10010];
char s[100], t[100];
map<string, set<string> > rel;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        rel.clear();

        int n;
        scanf("%d\n", &n);
        for (int i = 0; i < n; i++) {
            // size_t len;
            // int read = getline(&buf, &len, stdin);
            gets(buf);
            // buf[read - 1] = ' ';
            char *well = buf;
            sscanf(well, " %s", s);
            well += strlen(s);
            while (*well == ' ') well++;
            // printf("%s\n", s);
            while (~sscanf(well, " %s", t)) {
                // printf("%s\n", t);
                rel[s].insert(t);
                well += strlen(t);
                while (*well == ' ') well++;
            }
        }
        // putchar(10);

        double MAP = 0;
        for (int i = 0; i < n; i++) {
            // size_t len;
            // int read = getline(&buf, &len, stdin);
            gets(buf);
            char *well = buf;
            sscanf(well, " %s", s);
            well += strlen(s);
            while (*well == ' ') well++;
            // printf("%s\n", s);

            double AveP = 0;
            int r = 0;
            int cnt = 0;
            while (~sscanf(well, " %s", t)) {
                // printf("%s\n", t);
                well += strlen(t);
                while (*well == ' ') well++;

                r++;
                if (!rel[s].count(t)) continue;
                cnt++;
                AveP += 1.0 * cnt / r;
                rel[s].insert(t);
            }
            AveP /= rel[s].size();
            MAP += AveP;
        }
        MAP /= n;

        printf("Case #%d: %.6f\n", task, MAP);

    }

    return 0;
}

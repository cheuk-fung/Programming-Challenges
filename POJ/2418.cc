/*
 *  SRC: POJ 2418
 * PROB: Hardwood Species
 * ALGO: Hash
 * DATE: Sep 07, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <map>
#include <string>

using std::map;
using std::string;

char buf[50];
map<string, int> tree;
typedef map<string, int>::const_iterator mci;

int main()
{
    int cnt = 0;
    while (gets(buf)) {
        tree[buf]++;
        cnt++;
    }

    for (mci t = tree.begin(); t != tree.end(); t++)
        printf("%s %.4f\n", t->first.c_str(), t->second * 100.0 / cnt);

    return 0;
}

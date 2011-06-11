/*
 *  SRC: POJ 1002
 * PROB: 487-3279
 * ALGO: string
 * DATE: Dec 11, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char map[255];
int dir[100001];

int stdform(char* src)
{
    int dest = 0;
    while (*src) {
       if (*src == '-') {
	   src++;
	   continue;
       }
       dest = dest * 10 + map[*src++];
    }
    return dest;
}

int main()
{
    map['0'] = 0;
    map['1'] = 1;
    map['2'] = map['A'] = map['B'] = map['C'] = 2;
    map['3'] = map['D'] = map['E'] = map['F'] = 3;
    map['4'] = map['G'] = map['H'] = map['I'] = 4;
    map['5'] = map['J'] = map['K'] = map['L'] = 5;
    map['6'] = map['M'] = map['N'] = map['O'] = 6;
    map['7'] = map['P'] = map['R'] = map['S'] = 7;
    map['8'] = map['T'] = map['U'] = map['V'] = 8;
    map['9'] = map['W'] = map['X'] = map['Y'] = 9;

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
	char tmp[100];
	scanf("%s", tmp);
	dir[i] = stdform(tmp);
    }

    sort(dir, dir + n);

    bool flag = false;
    for (int i = 0; i < n; i++) {
	int tot = 0;
	while (i + 1 < n && dir[i] == dir[i + 1]) {
	    i++;
	    tot++;
	}
	if (tot) {
	    flag = true;
	    if (dir[i] / 1000000 == 0) putchar('0');
	    if (dir[i] / 100000 == 0) putchar('0');
	    printf("%d-", dir[i] / 10000);
	    dir[i] %= 10000;
	    if (dir[i] < 1000) putchar('0');
	    if (dir[i] < 100) putchar('0');
	    if (dir[i] < 10) putchar('0');
	    printf("%d %d\n", dir[i], tot + 1);
	}
    }
    if (flag == false) printf("No duplicates.\n");

    return 0;
}


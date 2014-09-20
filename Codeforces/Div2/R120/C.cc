#include <cstdio>
#include <string>

using namespace std;

int n, length;
bool error;
char line[1000000];
string types[1000000];

bool check()
{
    int cnt = 0;
    for (int i = 0; i < length; i++) {
        if (types[i] == "int") {
            cnt++;
        }
    }
    return cnt == n;
}

void findpair(int p, int *pos, bool print)
{
    if (types[p] != "pair") {
        error = true;
        *pos = -1;
        return ;
    }

    if (types[p + 1] == "int") {
        if (types[p + 2] == "int") {
            *pos = p + 3;
            if (print) printf("pair<int,int>");
        } else {
            if (print) printf("pair<int,");
            findpair(p + 2, pos, print);
            if (error) return ;
            if (print) printf(">");
        }
        return ;
    }

    if (print) printf("pair<");
    findpair(p + 1, pos, print);
    if (error) return ;
    if (types[*pos] == "int") {
        (*pos)++;
        if (print) printf(",int>");
    } else {
        if (print) printf(",");
        findpair(*pos, pos, print);
        if (error) return ;
        if (print) printf(">");
    }
}

int main()
{
    while (~scanf("%d\n", &n)) {
        gets(line);

        char *s = line;
        types[length = 0] = "";
        while (*s) {
            if (*s == ' ') {
                types[++length] = "";
            } else {
                types[length] += *s;
            }
            s++;
        }
        types[++length] = "";
        types[length + 1] = "";

        if (!check()) {
            puts("Error occurred");
            continue;
        }

        if (types[0] == "int") {
            if (length == 1) {
                puts("int");
            } else {
                puts("Error occurred");
            }
            continue;
        }

        error = false;
        int pos;
        findpair(0, &pos, false);
        if (error || pos != length) puts("Error occurred");
        else {
            findpair(0, &pos, true);
            putchar(10);
        }
    }

    return 0;
}


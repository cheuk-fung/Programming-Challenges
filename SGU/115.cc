#include <cstdio>
#include <ctime>

const int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(int argc, char *argv[])
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (m <= 0 || m > 12 || n <= 0 || n > month_days[m]) {
        puts("Impossible");
    } else {
        tm time = {0};
        time.tm_year = 2001 - 1900;
        time.tm_mon = m - 1;
        time.tm_mday = n;
        mktime(&time);
        printf("%d\n", time.tm_wday == 0 ? 7 : time.tm_wday);
    }

    return 0;
}

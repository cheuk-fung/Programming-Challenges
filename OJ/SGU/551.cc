#include <cassert>
#include <cstdio>

int main(int argc, char *argv[])
{
    int n, t1, t2;
    while (~scanf("%d%d%d", &n, &t1, &t2)) {
        int low = 0, high = n * t1;
        while (low < high) {
            int mid = (low + high - 1) >> 1;
            if (mid / t1 + mid / t2 >= n) high = mid;
            else low = mid + 1;
        }
        assert(low % t1 == 0 || low % t2 == 0);
        int cnt = low / t1 + low / t2;
        int time = low;
        if (low % t1 != 0) {
            cnt++;
            time += t1 - low % t1;
        } else if (low % t2 != 0) {
            cnt++;
            time += t2 - low % t2;
        }
        printf("%d %d\n", cnt, time);
    }

    return 0;
}

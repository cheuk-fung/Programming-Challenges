/*
 *  SRC: NKOJ
 * TASK: Defence Of The ACM
 * ALGO: SPFA
 * DATE: 03/28/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<cstdlib>
#include	<climits>
#include	<vector>

const long MAXN = 100000;

bool used[MAXN];
long query[MAXN];

struct Point {
    long p;
    long long d;

    Point(long pp, long long dd) : p(pp), d(dd) { }
};

struct Route {
    std::vector<Point> next;
    long long* lowest;

    Route() : lowest(0) { }
} map[MAXN];

void SPFA(long n, long start, long long* lowest)
{
    for (long i = 0; i < n; i++) {
        used[i] = false;
    }

    long open = 0, closed = -1;
    used[start] = true;
    query[open] = start;
    lowest[start] = 0;
    while (closed < open)
    {
        long src = query[++closed];
        used[src] = false;
        long len = map[src].next.size();
        for (long i = 0; i < len; i++) {
            long dest = map[src].next[i].p;
            long long dis = map[src].next[i].d;
            if (dis + lowest[src] < lowest[dest])
            {
                lowest[dest] = dis + lowest[src];
                if (used[dest] == false)
                {
                    used[dest] = true;
                    query[++open] = dest;
                }
            }
        }
    }
}

int main()
{
    long N, M, Q;
    scanf("%ld%ld%ld", &N, &M, &Q);
    for (long i = 0; i < M; i++) {
        long F, T, D;
        scanf("%ld%ld%ld", &F, &T, &D);
        map[F].next.push_back(Point(T, D));
        map[T].next.push_back(Point(F, D));
    }

    srand(M);
    for (long i = 0; i < Q; i++) {
        long F, T;
        scanf("%ld%ld", &F, &T);
        if (map[F].lowest) {
            printf("%lld\n", map[F].lowest[T]);
            continue;
        }
        if (map[T].lowest) {
            printf("%lld\n", map[T].lowest[F]);
            continue;
        }
        long a, b;
        if (rand() % 2) {
            a = F;
            b = T;
        }
        else {
            a = T;
            b = F;
        }
        map[a].lowest = new long long[N];
        for (long j = 0; j < N; j++)
            map[a].lowest[j] = (long long)MAXN * (long long)MAXN + 1;
        SPFA(N, a, map[a].lowest); 
        printf("%lld\n", map[a].lowest[b]);
    }

    return 0;
}				/* ----------  end of function main  ---------- */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 300;

struct Junction {
    char c;
    int r, tb, tp;
} junc[MAXN];

int mat[MAXN][MAXN];
int dist[MAXN], prev[MAXN];
int vis[MAXN];

inline char get_color(int x, int t)
{
    if (t < junc[x].r) return junc[x].c;
    t = (t - junc[x].r) % (junc[x].tb + junc[x].tp);
    if (junc[x].c == 'B') return t < junc[x].tp ? 'P' : 'B';
    return t < junc[x].tb ? 'B' : 'P';
}

inline int get_remain_time(int x, int t)
{
    if (t < junc[x].r) return junc[x].r - t;
    t = (t - junc[x].r) % (junc[x].tb + junc[x].tp);
    if (junc[x].c == 'B') {
        return t < junc[x].tp ? junc[x].tp - t : junc[x].tb + junc[x].tp - t;
    }
    return t < junc[x].tb ? junc[x].tb - t : junc[x].tb + junc[x].tp - t;
}

void dijkstra(int src, int n)
{
    memset(prev, 0xff, sizeof prev);
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);

    dist[src] = 0;
    for (int i = 0; i < n; i++) {
        int mind = INF;
        int u;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dist[j] < mind) {
                mind = dist[j];
                u = j;
            }
        }
        if (mind == INF) break;
        vis[u] = true;

        char cu = get_color(u, mind);
        int tu = get_remain_time(u, mind);
        for (int v = 0; v < n; v++) {
            if (!mat[u][v]) continue;
            char cv = get_color(v, mind);
            int d = mind;
            if (cu != cv) {
                int tv = get_remain_time(v, mind);
                d += min(tu, tv);
                int cnt = 0, ttu = tu;
                while (ttu == tv && cnt <= 2) {
                    cnt++;
                    ttu = get_remain_time(u, d);
                    tv = get_remain_time(v, d);
                    d += min(ttu, tv);
                }
                if (cnt > 2) continue;
            }
            d += mat[u][v];
            if (d < dist[v]) {
                dist[v] = d;
                prev[v] = u;
            }
        }
    }
}

void print_travel(int u)
{
    if (prev[u] != -1) {
        print_travel(prev[u]);
        putchar(' ');
    }
    printf("%d", u + 1);
}

int main(int argc, char *argv[])
{
    int src, dest;
    scanf("%d%d", &src, &dest);
    src--; dest--;

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf(" %c%d%d%d", &junc[i].c, &junc[i].r, &junc[i].tb, &junc[i].tp);
    }
    for (int i = 0; i < m; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        u--; v--;
        mat[u][v] = mat[v][u] = d;
    }

    dijkstra(src, n);
    if (dist[dest] == INF) {
        puts("0");
    } else {
        printf("%d\n", dist[dest]);
        print_travel(dest);
        putchar(10);
    }

    return 0;
}

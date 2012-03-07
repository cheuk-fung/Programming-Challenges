/*
 *  SRC: POJ 3009
 * PROB: Curling 2.0
 * ALGO: DFS
 * DATE: Mar 07, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);
    static final int dir[][] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    int ans;
    int w, h;
    int sx, sy, ex, ey;
    boolean[][] map;

    void dfs(int x, int y, int cnt)
    {
        if (cnt == 10) return ;

        for (int i = 0; i < 4; i++) {
            int xx = x, yy = y;
            while (true) {
                xx += dir[i][0];
                yy += dir[i][1];

                if (xx == ex && yy == ey) {
                    ans = Math.min(ans, cnt + 1);
                    return ;
                }

                if (!map[xx][yy]) break;
            }
            if (xx - dir[i][0] == x && yy - dir[i][1] == y) continue;
            if (0 < xx && xx <= h && 0 < yy && yy <= w) {
                map[xx][yy] = true;
                dfs(xx - dir[i][0], yy - dir[i][1], cnt + 1);
                map[xx][yy] = false;
            }
        }
    }

    void solve()
    {
        while (true) {
            w = cin.nextInt();
            h = cin.nextInt();
            if (w == 0 && h == 0) break;

            map = new boolean[h + 2][w + 2];
            for (int i = 1; i <= h; i++) {
                for (int j = 1; j <= w; j++) {
                    int t = cin.nextInt();
                    switch (t) {
                        case 0: map[i][j] = true; break;
                        case 2: map[i][j] = true; sx = i; sy = j; break;
                        case 3: map[i][j] = true; ex = i; ey = j;
                    }
                }
            }

            ans = Integer.MAX_VALUE;
            dfs(sx, sy, 0);
            System.out.println(ans == Integer.MAX_VALUE ? -1 : ans);
        }
    }

    void debug(Object...x)
    {
        System.out.println(Arrays.deepToString(x));
    }
}

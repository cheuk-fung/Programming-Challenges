/*
 *  SRC: POJ 1129
 * PROB: Channel Allocation
 * ALGO: DFS
 * DATE: Jul 23, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        while (new Prob().solve(cin)) ;
    }
}

class Prob
{
    private int n;
    private int ans = 0x3FFFFFF;
    private int rpt[];
    private boolean map[][];

    private boolean check(int p, int chal)
    {
        for (int i = 0; i < n; i++)
            if (map[p][i] && rpt[i] == chal) return false;

        return true;
    }

    private void dfs(int depth, int cnt)
    {
        if (cnt >= ans) return ;
        if (depth == n) {
            ans = cnt;
            return ;
        }
        
        for (int i = 1; i <= cnt; i++) {
            if (check(depth, i)) {
                rpt[depth] = i;
                dfs(depth + 1, cnt);
                rpt[depth] = 0;
            }
        }

        rpt[depth] = cnt + 1;
        dfs(depth + 1, cnt + 1);
        rpt[depth] = 0;
    }

    public boolean solve(Scanner cin)
    {
        n = cin.nextInt();
        if (n == 0) return false;

        rpt = new int[n];
        map = new boolean[n][n];
        for (int i = 0; i < n; i++) {
            String s = cin.next();
            for (int j = 2; j < s.length(); j++) map[i][s.charAt(j) - 'A'] = true;
        }

        dfs(0, 0);

        System.out.println(ans + " channel" + (ans > 1 ? "s" : "") + " needed.");

        return true;
    }
}

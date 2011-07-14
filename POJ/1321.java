/*
 *  SRC: POJ 1321
 * PROB: 棋盘问题
 * ALGO: DFS
 * DATE: Jul 14, 2011 
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
    private int n, k, c;
    private String[] board;
    private boolean[] visited;

    private void dfs(int row, int depth)
    {
        if (depth == 0) {
            c++;
            return ;
        }

        for (int i = row; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!visited[j] && board[i].charAt(j) == '#') {
                    visited[j] = true;
                    dfs(i + 1, depth - 1);
                    visited[j] = false;
                }
    }

    public boolean solve(Scanner cin)
    {
        n = cin.nextInt();
        k = cin.nextInt();

        if (n == -1 && k == -1) return false;

        visited = new boolean[n];
        board = new String[n];

        for (int i = 0; i < n; i++)
            board[i] = cin.next();

        dfs(0, k);

        System.out.println(c);

        return true;
    }
}

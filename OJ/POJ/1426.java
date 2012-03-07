/*
 *  SRC: POJ 1426
 * PROB: Find The Multiple
 * ALGO: BFS
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

class Node {
    int d;
    String s;

    Node(int dd, String ss)
    {
        d = dd;
        s = ss;
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    String bfs(int n)
    {
        Queue<Node> que = new LinkedList<Node>();
        boolean[] vis = new boolean[n];
        
        que.add(new Node(1, "1"));
        vis[1] = true;
        while (que.peek() != null) {
            Node u = que.remove();
            int currD = u.d * 10 % n;
            if (currD == 0) return u.s + "0";
            if (!vis[currD]) {
                que.add(new Node(currD, u.s + "0"));
                vis[currD] = true;
            }
            currD = (u.d * 10 + 1) % n;
            if (currD == 0) return u.s + "1";
            if (!vis[currD]) {
                que.add(new Node(currD, u.s + "1"));
                vis[currD] = true;
            }
        }

        return "";
    }

    void solve()
    {
        String[] ans = new String[201];
        ans[1] = "1";
        for (int i = 2; i <= 200; i++)
            ans[i] = bfs(i);

        while (true) {
            int n = cin.nextInt();
            if (n == 0) break;
            System.out.println(ans[n]);
        }
    }
}

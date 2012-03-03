/*
 *  SRC: NKOJ 1680
 * PROB: Multiple
 * ALGO: BFS
 * DATE: Mar 03, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.math.BigInteger;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Node {
    int d, v;
    Node fa;

    Node(int _d, int _v, Node _fa)
    {
        d = _d;
        v = _v;
        fa = _fa;
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    BigInteger generateAns(Node u)
    {
        if (u.fa == null) return BigInteger.valueOf(u.d);
        return generateAns(u.fa).multiply(BigInteger.TEN).add(BigInteger.valueOf(u.d));
    }

    BigInteger bfs(int n, int[] digit)
    {
        if (n == 0) return BigInteger.ZERO;

        boolean[] vis = new boolean[n];
        Queue<Node> queue = new LinkedList<Node>();

        for (int d : digit)
            if (d != 0 && !vis[d % n]) {
                int next = d % n;
                if (next == 0) return BigInteger.valueOf(d);
                queue.add(new Node(d, next, null));
                vis[next] = true;
            }

        while (queue.peek() != null) {
            Node u = queue.remove();
            for (int d : digit) {
                int next = (u.v * 10 + d) % n;
                if (next == 0)
                    return generateAns(u).multiply(BigInteger.TEN).add(BigInteger.valueOf(d));
                if (!vis[next]) {
                    queue.add(new Node(d, next, u));
                    vis[next] = true;
                }
            }
        }

        return BigInteger.ZERO;
    }

    void solve()
    {
        while (cin.hasNext()) {
            int n = cin.nextInt();
            int m = cin.nextInt();
            int[] digit = new int[m];
            for (int i = 0; i < m; i++) digit[i] = cin.nextInt();
            Arrays.sort(digit);

            System.out.println(bfs(n, digit));
        }
    }
}

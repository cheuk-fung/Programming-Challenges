/*
 *  SRC: NKOJ 1326
 * PROB: Trees Made to Order
 * ALGO: NULL
 * DATE: Mar 03, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);
    static final int MAXN = 500000000;
    static int[] f = new int[20];
    static int[] g = new int[20];

    String generate(int node, int index)
    {
        if (node == 0) return "";

        int leftNode = -1, rightNode = node;
        while (true) {
            int t = f[++leftNode] * f[--rightNode];
            if (index - t < 0) break;
            index -= t;
        }

        int leftOrder = index / f[rightNode];
        int rightOrder = index % f[rightNode];
        String left = generate(leftNode, leftOrder);
        if (left.compareTo("") != 0) left = "(" + left + ")";
        String right = generate(rightNode, rightOrder);
        if (right.compareTo("") != 0) right = "(" + right + ")";

        return left + "X" + right;
    }

    void solve()
    {
        f[0] = 1;
        int nodeCnt = 1;
        while (g[nodeCnt - 1] < MAXN) {
            for (int i = 0; i < nodeCnt; i++)
                f[nodeCnt] += f[i] * f[nodeCnt - 1 - i];
            g[nodeCnt] = g[nodeCnt - 1] + f[nodeCnt++];
        }

        while (true) {
            int order = cin.nextInt();
            if (order == 0) break;
            int node = 1;
            while (g[node] < order) node++;
            System.out.println(generate(node, order - g[node - 1] - 1));
        }
    }
}

/*
 *  SRC: POJ 1416
 * PROB: Shredding Company
 * ALGO: DFS
 * DATE: Mar 08, 2012
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

    int target;
    int sum, partCnt;
    int[] part, ansPart;
    int ansType;
    String s;

    void dfs(int pos, int tot, int lev)
    {
        if (tot > target) {
            return ;
        }
        if (pos == s.length()) {
            if (tot < sum) return ;
            if (tot > sum) {
                sum = tot;
                partCnt = lev;
                for (int i = 0; i < partCnt; i++)
                    ansPart[i] = part[i];
                ansType = 0;
            }
            else {
                ansType = 1;
            }
            return ;
        }

        for (int i = pos; i < s.length(); i++) {
            part[lev] = Integer.parseInt(s.substring(pos, i + 1));
            dfs(i + 1, tot + part[lev], lev + 1);
        }
    }

    void solve()
    {
        while (true) {
            target = cin.nextInt();
            s = cin.next();
            if (target == 0 && s.equals("0")) break;
            if (target == Integer.parseInt(s)) {
                System.out.println(target + " " + target);
                continue;
            }

            sum = 0;
            part = new int[10];
            ansPart = new int[10];
            ansType = -1;
            dfs(0, 0, 0);
            switch (ansType) {
                case -1:
                    System.out.println("error");
                    break;
                case 0:
                    System.out.print(sum);
                    for (int i = 0; i < partCnt; i++)
                        System.out.print(" " + ansPart[i]);
                    System.out.println();
                    break;
                case 1:
                    System.out.println("rejected");
            }
        }
    }
}

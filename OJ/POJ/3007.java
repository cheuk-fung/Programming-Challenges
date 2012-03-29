/*
 *  SRC: POJ 3007
 * PROB: Organize Your Train part II
 * ALGO: NULL
 * DATE: Mar 29, 2012
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

    void solve()
    {
        int tasks = cin.nextInt();

        while (tasks-- > 0) {
            String s = cin.next();

            Set<String> orders = new HashSet<String>();
            for (int i = 1; i < s.length(); i++) {
                String left = s.substring(0, i), right = s.substring(i),
                       rleft = new StringBuffer(left).reverse().toString(),
                       rright = new StringBuffer(right).reverse().toString();

                orders.add(left + right);
                orders.add(left + rright);
                orders.add(rleft + right);
                orders.add(rleft + rright);
                orders.add(right + left);
                orders.add(right + rleft);
                orders.add(rright + left);
                orders.add(rright + rleft);
            }

            System.out.println(orders.size());
        }
    }
}

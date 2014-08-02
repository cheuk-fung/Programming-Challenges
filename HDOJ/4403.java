/*
 *  SRC: HDOJ 4403
 * PROB: A very hard Aoshu problem
 * ALGO: NULL
 * DATE: Sep 22, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.Scanner;

class Main {
    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);
        String str;
        while (!(str = cin.next()).equals("END")) {
            int cnt = 0;
            for (int i = 1; i < str.length(); i++) {
                String left = str.substring(0, i);
                String right = str.substring(i);
                for (int ls = 0; ls < 1 << (left.length() - 1); ls++) {
                    long leftSum = getsum(left, ls);
                    for (int rs = 0; rs < 1 << (right.length() - 1); rs++) {
                        long rightSum = getsum(right, rs);
                        if (leftSum == rightSum) {
                            cnt++;
                        }
                    }
                }
            }
            System.out.println(cnt);
        }
    }

    private long getsum(String str, int s)
    {
        long sum = 0;
        int prev = 0;
        for (int b = 0; b < str.length() - 1; b++) {
            if ((s & (1 << b)) != 0) {
                sum += Long.parseLong(str.substring(prev, b + 1));
                prev = b + 1;
            }
        }
        sum += Long.parseLong(str.substring(prev));

        return sum;
    }
}

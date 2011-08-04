/*
 *  SRC: NKOJ p1273
 * PROB: Loansome Car Buyer
 * ALGO: NULL
 * DATE: Aug 01, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main
{
    final static double eps = 1e-12;

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        while (1 + 1 == 2) {
            int duration = cin.nextInt();
            if (duration < 0) break;
            double down = cin.nextDouble(), loan = cin.nextDouble();
            int records = cin.nextInt();
            double[] dec = new double[duration + 1];

            int prev = 0;
            double prevPer = 0;
            for (int i = 0; i < records; i++) {
                int curr = cin.nextInt();
                double currPer = cin.nextDouble();

                for (int j = prev + 1; j < curr; j++) dec[j] = prevPer;
                dec[curr] = currPer;

                prev = curr;
                prevPer = currPer;
            }
            for (int i = prev + 1; i <= duration; i++) dec[i] = prevPer;

            double car = (loan + down) * (1 - dec[0]);
            if (car - eps > loan) {
                System.out.println("0 months");
                continue;
            }
            down = loan / duration;
            for (int mon = 1; ; mon++) {
                car -= car * (mon > duration ? dec[duration] : dec[mon]);
                loan -= down;
                if (car - eps > loan) {
                    System.out.println(mon + " month" + (mon > 1 ? "s" : ""));
                    break;
                }
            }
        }
    }
}


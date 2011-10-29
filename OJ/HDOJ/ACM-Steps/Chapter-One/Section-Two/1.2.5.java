/*
 *  SRC: HDOJ ACM Steps
 * PROB: Lowest Bit
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int A = cin.nextInt();
        while (A != 0) {
            int ans = 1;
            while ((A & ans) == 0) ans <<= 1;
            System.out.println(ans);
            A = cin.nextInt();
        }
    }
}

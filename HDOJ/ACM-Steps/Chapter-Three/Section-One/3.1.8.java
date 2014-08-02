/*
 *  SRC: HDOJ ACM Steps
 * PROB: Queuing
 * ALGO: DP
 * DATE: Oct 31, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main(String args[]) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    void solve() throws IOException
    {
        PrintWriter out = new PrintWriter(System.out);
        Scanner in = new Scanner(System.in);

        final int maxL = 1000010;
        final long MOD = 2329089562800L;
        // MOD = 7*11*13*16*17*19*23*25*27*29
        long f[] = new long[maxL];
        f[0] = 1;
        f[1] = 2;
        f[2] = 4;
        f[3] = 6;
        for (int i = 4; i < maxL; i++)
            f[i] = (f[i - 1] + f[i - 3] + f[i - 4]) % MOD;
        // f[i - 1] + m, f[i - 3] + mmf, f[i - 4] + mmff

        while (in.hasNext())
            out.println(f[in.nextInt()] % in.nextInt());

        out.flush();
    }

    void debug(Object...x)
    {
        System.out.println(Arrays.deepToString(x));
    }
}

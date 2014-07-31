/*
ID: os.idea1
LANG: JAVA
TASK: vans
*/
import java.io.*;
import java.util.*;
import java.math.*;

class vans {
    static int n;
    static BigInteger[] f = new BigInteger[1010];
    static BigInteger ans;
    public static void main(String[] args) throws IOException
    {
        Scanner fin = new Scanner(new FileReader("vans.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("vans.out")));

        n = fin.nextInt();

        if (n == 1) {
            fout.println(0);
            fout.close();
            System.exit(0);
        }

        f[0] = BigInteger.ZERO;
        ans = f[1] = BigInteger.ONE;
        for (int i = 2; i < n; i++) {
            f[i] = BigInteger.ONE.add(f[i - 2]);
            for (int k = 2; k < i; k++)
                f[i] = f[i].add(f[i - k].multiply(BigInteger.valueOf(2 * (k - 1))));
            ans = ans.add(f[i]);
        }
        fout.println(ans.add(ans));
        fout.close();
    }
}

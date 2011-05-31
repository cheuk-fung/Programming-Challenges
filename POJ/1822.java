import java.util.Scanner;
import java.math.BigInteger;

class Main
{
    static BigInteger[][] combine;
    static BigInteger[][] f;

    public static void getCombine(int n)
    {
        combine = new BigInteger[n][];

        combine[0] = new BigInteger[] { BigInteger.ONE };

        for (int i = 1; i < n; i++) {
            combine[i] = new BigInteger[i + 1];
            combine[i][0] = BigInteger.ONE;
            combine[i][i] = BigInteger.ONE;
            for (int j = 1; j < i; j++)
                combine[i][j] = combine[i - 1][j].add(combine[i - 1][j - 1]);
        }
    }
    
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        
        int N = cin.nextInt(), K = cin.nextInt();

        getCombine(N + 1);

        f = new BigInteger[N + 1][];

        for (int i = 1; i <= N; i++) {
            f[i] = new BigInteger[N + 1];
            if (i <= K) f[i][1] = BigInteger.ONE;
            else f[i][1] = BigInteger.ZERO;
            for (int j = 2; j <= N; j++) {
                f[i][j] = BigInteger.ZERO;
                for (int k = 1; k <= K && i - k >= j - 1; k++) {
                    f[i][j] = f[i][j].add(f[i - k][j - 1].multiply(combine[i][k]));
                }
            }
        }

        BigInteger ans = BigInteger.ZERO;
        for (int j = 1; j <= N; j++) ans = ans.add(f[N][j]);

        System.out.println(ans);
    }
}


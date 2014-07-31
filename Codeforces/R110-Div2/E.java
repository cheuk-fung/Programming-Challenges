import java.util.Scanner;

public class E {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);
    static final int MOD = 1000000007;

    void solve()
    {
        int[][] f = new int[100][2501];
        for (int i = 0; i < 26; i++) f[0][i] = 1;
        for (int i = 1; i < 100; i++)
            for (int j = 0; j <= 2500; j++)
                if (f[i - 1][j] != 0)
                    for (int k = 0; k < 26; k++)
                        f[i][j + k] = (f[i][j + k] + f[i - 1][j]) % MOD;

        int t = cin.nextInt();
        while (t-- > 0) {
            String s = cin.next();
            int tot = 0;
            for (int i = 0; i < s.length(); i++)
                tot += s.charAt(i) - 'a';
            System.out.println(f[s.length() - 1][tot] - 1);
        }
    }
}

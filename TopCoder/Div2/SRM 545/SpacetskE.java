public class SpacetskE {
    private static final int MOD = 1000000007;

    private int gcd(int a, int b)
    {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }

        return a;
    }

    public int countsets(int L, int H, int K)
    {
        if (K == 1) return (L + 1) * (H + 1);

        int[][] C = new int[202][202];
        C[0][0] = 1;
        for (int i = 1; i < 202; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }

        int cnt = 0;
        for (int x = 0; x <= L; x++) {
            cnt = (cnt + C[H + 1][K]) % MOD;
            boolean[][] vis = new boolean[L + 1][H + 1];
            for (int j = H; j > 0; j--) {
                for (int i = 0; i <= L; i++) {
                    if (i == x || vis[i][j]) continue;
                    int r = gcd(Math.abs(i - x), j);
                    cnt = (cnt + C[r + 1][K]) % MOD;

                    int dx = (i - x) / r, dy = j / r;
                    for (int a = x, b = 0; a != i; a += dx, b += dy) vis[a][b] = true;
                }
            }
        }

        return cnt;
    }
}

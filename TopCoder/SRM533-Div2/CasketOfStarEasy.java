public class CasketOfStarEasy {
    public int maxEnergy(int[] weight)
    {
        int n = weight.length;
        int[][] f = new int[n][n];
        for (int l = 3; l <= n; l++)
            for (int i = 0; i < n; i++) {
                int j = i + l - 1;
                if (j >= n) break;
                for (int k = i + 1; k < j; k++)
                    f[i][j] = Math.max(f[i][j], f[i][k] + f[k][j] + weight[i] * weight[j]);
            }

        return f[0][n - 1];
    }
}

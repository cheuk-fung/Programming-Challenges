class GaussElimination {
    private BigFraction[] X;

    //  1: infinitely many solutions
    //  0: one solution
    // -1: no solution
    public int solve(BigFraction[][] A, BigFraction[] B)
    {
        int n = A.length;
        X = new BigFraction[n];

        for (int xc = 0; xc < n; xc++) {
            int row = xc;
            if (A[row][xc].isZero()) {
                for (int i = row + 1; i < n; i++) {
                    if (!A[i][xc].isZero()) {
                        row = i;
                        break;
                    }
                }
            }
            if (A[row][xc].isZero()) {
                if (B[row].isZero()) return 1;
                return -1;
            }

            if (row != xc) {
                for (int j = xc; j < n; j++) {
                    BigFraction tmp = A[xc][j];
                    A[xc][j] = A[row][j];
                    A[row][j] = tmp;
                }
                BigFraction tmp = B[xc];
                B[xc] = B[row];
                B[row] = tmp;
            }

            for (int i = xc + 1; i < n; i++) {
                BigFraction rate = A[i][xc].divide(A[xc][xc]);
                for (int j = xc; j < n; j++)
                    A[i][j] = A[i][j].subtract(rate.multiply(A[xc][j]));
                B[i] = B[i].subtract(rate.multiply(B[xc]));
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            X[i] = B[i];
            for (int j = n - 1; j > i; j--)
                X[i] = X[i].subtract(A[i][j].multiply(X[j]));
            X[i] = X[i].divide(A[i][i]);
        }

        return 0;
    }

    public BigFraction[] getAns() { return X; }

    public String toString()
    {
        String res = "";
        for (int i = 0; i < X.length - 1; i++)
            res += X[i] + " ";
        return res + X[X.length - 1];
    }
}

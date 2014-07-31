public class ANDEquation {
    public int restoreY(int[] A)
    {
        for (int i = 0; i < A.length; i++) {
            int r = -1;
            for (int j = 0; j < A.length; j++) {
                if (j != i) r &= A[j];
            }
            if (r == A[i]) return r;
        }
        return -1;
    }
}

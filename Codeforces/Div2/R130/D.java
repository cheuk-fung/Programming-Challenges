import java.util.*;

public class D {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int n = cin.nextInt();

        long[] p = new long[n];
        long[] v = new long[5];
        for (int i = 0; i < n; i++) p[i] = cin.nextLong();
        for (int i = 0; i < 5; i++) v[i] = cin.nextLong();

        long[] cnt = new long[5];
        long pnt = 0;
        for (int i = 0; i < n; i++) {
            pnt += p[i];
            for (int j = 4; j >= 0; j--) {
                if (pnt >= v[j]) {
                    cnt[j] += pnt / v[j];
                    pnt = pnt % v[j];
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            System.out.println(cnt[i]);
        }
        System.out.println(pnt);
    }
}

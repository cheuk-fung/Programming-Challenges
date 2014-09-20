import java.util.*;

public class B {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    Scanner cin = new Scanner(System.in);
    int n, k;

    boolean check(long v)
    {
        long kk = k;
        long tot = v;
        while (v / kk != 0) {
            tot += v / kk;
            kk *= k;
        }

        return tot >= n;
    }

    void solve()
    {
        while (cin.hasNext()) {
            n = cin.nextInt();
            k = cin.nextInt();

            long l = 0, r = n;
            while (l < r) {
                long mid = (l + r) >> 1;
                if (check(mid)) r = mid;
                else l = mid + 1;
            }

            System.out.println(l);
        }
    }
}

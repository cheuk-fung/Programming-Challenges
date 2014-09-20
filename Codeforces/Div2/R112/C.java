import java.util.*;

public class C {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    Scanner cin = new Scanner(System.in);

    void solve()
    {
        while (cin.hasNext()) {
            int k = cin.nextInt();
            String s = cin.next();

            long cnt = 0;
            if (k == 0) {
                String[] ss = s.split("1");
                for (int i = 0; i < ss.length; i++) {
                    cnt += (1L + ss[i].length()) * ss[i].length() / 2;
                }
                System.out.println(cnt);
                continue;
            }

            int oneCnt = 0;
            int l = 0, r = -1;
            while (r + 1 < s.length() && oneCnt < k) {
                if (s.charAt(++r) == '1') {
                    oneCnt++;
                }
            }

            if (oneCnt < k) {
                System.out.println(0);
                continue;
            }

            while (l < s.length() && r < s.length()) {
                long ll = 1;
                while (l < s.length() && s.charAt(l) == '0') {
                    l++;
                    ll++;
                }
                long rr = 1;
                r++;
                while ((r < s.length() && s.charAt(r) == '0')) {
                    r++;
                    rr++;
                }
                cnt += ll * rr;
                l++;
            }

            System.out.println(cnt);
        }
    }
}

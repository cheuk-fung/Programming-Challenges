import java.util.*;

public class A {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    void solve()
    {
        while (cin.hasNext()) {
            int n = cin.nextInt();
            int[] x = new int[n];
            int[] y = new int[n];
            for (int i = 0; i < n; i++) {
                x[i] = cin.nextInt();
                y[i] = cin.nextInt();
            }

            int cnt = 0;
            for (int i = 0; i < n; i++) {
                int flag = 0;
                for (int j = 0; j < n; j++) {
                    if (x[i] == x[j] && y[i] < y[j]) {
                        flag |= 1;
                    } else if (x[i] == x[j] && y[i] > y[j]) {
                        flag |= 2;
                    } else if (x[i] < x[j] && y[i] == y[j]) {
                        flag |= 4;
                    } else if (x[i] > x[j] && y[i] == y[j]) {
                        flag |= 8;
                    }
                }
                if (flag == 0xf) {
                    cnt++;
                }
            }

            System.out.println(cnt);
        }
    }
}

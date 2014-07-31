import java.util.Scanner;
import java.util.Vector;

public class D {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Suspect {
    String say = "Not defined";
    boolean crime = false;
    Vector<Integer> T = new Vector<Integer>();
    Vector<Integer> F = new Vector<Integer>();
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    void solve()
    {
        int n = cin.nextInt();
        int m = cin.nextInt();
        Suspect[] suspects = new Suspect[n];
        for (int i = 0; i < n; i++) suspects[i] = new Suspect();

        for (int i = 0; i < n; i++) {
            String line = cin.next();
            int idx = Integer.parseInt(line.substring(1)) - 1;
            if (line.charAt(0) == '+') suspects[idx].T.add(i);
            else suspects[idx].F.add(i);
        }

        int truth = 0;
        for (Suspect s : suspects) truth += s.F.size();

        int cnt = 0;
        for (Suspect s : suspects) {
            int truthI = truth + s.T.size() - s.F.size();
            if (truthI == m) {
                s.crime = true;
                cnt++;
            }
        }

        for (Suspect s : suspects) {
            if (s.crime) {
                for (int p : s.T)
                    if (cnt == 1) suspects[p].say = "Truth";
                for (int p : s.F)
                    if (cnt == 1) suspects[p].say = "Lie";
            }
            else {
                for (int p : s.T) suspects[p].say = "Lie";
                for (int p : s.F) suspects[p].say = "Truth";
            }
        }

        for (Suspect s : suspects)
            System.out.println(s.say);
    }
}

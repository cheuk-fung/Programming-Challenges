/*
 *  SRC: HDOJ 4119
 * PROB: Isabella's Message
 * ALGO: String
 * DATE: Sep 18, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Main().run();
    }

    void run()
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        for (int task = 1; task <= tasks; task++) {
            int n = cin.nextInt();
            char[][] mat = new char[n][];
            char[][] mask = new char[n][];
            for (int i = 0; i < n; i++) {
                mat[i] = cin.next().toCharArray();
            }
            for (int i = 0; i < n; i++) {
                mask[i] = cin.next().toCharArray();
            }

            int m = cin.nextInt();
            HashSet<String> dict = new HashSet<String>();
            for (int i = 0; i < m; i++) {
                dict.add(cin.next());
            }

            String[] ret = new String[4];
            for (int i = 0; i < 4; i++) {
                ret[i] = decrypt(mat, mask);
                mask = rotate(mask);
            }

            String ans = null;
            for (int i = 0; i < 4; i++) {
                String now = "";
                for (int j = 0; j < 4; j++) {
                    now += ret[(i + j) % 4];
                }
                String[] tmp = now.split("\\.");
                boolean ok = true;
                now = "";
                for (String str : tmp) {
                    if (str.equals("")) continue;
                    if (dict.contains(str)) {
                        now += " " + str;
                    } else {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    if (ans == null || now.compareTo(ans) < 0) ans = now;
                }
            }

            System.out.print("Case #" + task + ":");
            if (ans == null) {
                System.out.println(" FAIL TO DECRYPT");
            } else {
                System.out.println(ans);
            }
        }
    }

    String decrypt(char[][] mat, char[][] mask)
    {
        String res = "";
        int n = mat[0].length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mask[i][j] == '*') {
                    res += mat[i][j];
                }
            }
        }
        return res;
    }

    char[][] rotate(char[][] mask)
    {
        int n = mask[0].length;
        char[][] res = new char[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[j][n - i - 1] = mask[i][j];
            }
        }
        return res;
    }
}

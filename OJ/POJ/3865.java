/*
 *  SRC: POJ 3865
 * PROB: Database
 * ALGO: NULL
 * DATE: Mar 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

import java.util.*;
import java.io.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Prob {
    static final BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    void solve() throws IOException
    {
        String[] nm = in.readLine().split(" ");
        int n = Integer.parseInt(nm[0]);
        int m = Integer.parseInt(nm[1]);

        String[][] table = new String[n][];
        for (int i = 0; i < n; i++) {
            table[i] = in.readLine().split(",");
        }

        int ids = 0;
        HashMap<String, Integer> values = new HashMap<String, Integer>();
        Vector< Vector<Integer> > appear = new Vector< Vector<Integer> >();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (values.containsKey(table[i][j])) {
                    int id = values.get(table[i][j]);
                    for (int ii : appear.get(id)) {
                        if (ii != i) {
                            int cnt = 0;
                            int[] col = new int[2];
                            for (int k = 0; k < m; k++) {
                                if (table[i][k].equals(table[ii][k])) {
                                    col[cnt++] = k;
                                    if (cnt == 2) break;
                                }
                            }
                            if (cnt == 2) {
                                System.out.println("NO");
                                System.out.println((ii + 1) + " " + (i + 1));
                                System.out.println((col[0] + 1) + " " + (col[1] + 1));
                                return ;
                            }
                        }
                    }
                    appear.get(id).add(i);
                } else {
                    values.put(table[i][j], ids++);
                    appear.add(new Vector<Integer>());
                    appear.lastElement().add(i);
                }
            }
        }

        System.out.println("YES");
    }
}

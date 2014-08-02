/*
 *  SRC: HDOJ ACM Steps
 * PROB: 悼念512汶川大地震遇难同胞——老人是真饿了
 * ALGO: NULL
 * DATE: Oct 29, 2011
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.text.*;
import java.util.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class RiceComparator implements Comparator<Rice> {
    public int compare(Rice r1, Rice r2)
    {
        return r1.getP() - r2.getP();
    }
}

class Rice {
    int p, h;

    int getP() { return p; }
    int getH() { return h; }

    public Rice(int _p, int _h)
    {
        p = _p;
        h = _h;
    }
}

class Prob {
    static final DecimalFormat df = new DecimalFormat("0.00");

    public void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        int tasks = in.nextInt();
        while (tasks-- > 0) {
            int n = in.nextInt(),
                m = in.nextInt();
            Rice rices[] = new Rice[m];
            for (int i = 0; i < m; i++)
                rices[i] = new Rice(in.nextInt(), in.nextInt());
            Arrays.sort(rices, new RiceComparator());

            double ans = 0.0,
                   rest = n;
            for (Rice r:rices) {
                if (rest > r.getP() * r.getH()) {
                    ans += r.getH();
                    rest -= r.getP() * r.getH();
                }
                else {
                    ans += rest / r.getP();
                    break;
                }
            }
            System.out.println(df.format(ans));
        }
    }
}

class MyReader {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer in;

    boolean hasNext() throws IOException
    {
        if (in.hasMoreTokens()) return true;
        String line = br.readLine();
        if (line == null) return false;
        in = new StringTokenizer(line);
        return true;
    }

    String next() throws IOException
    {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }
}

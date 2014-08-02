/*
 *  SRC: HDOJ 3687
 * PROB: National Day Parade
 * ALGO: NULL
 * DATE: Nov 06, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;

class Main {
    public static void main(String args[]) throws IOException
    {
        new Prob().solve();
    }
}

class Point {
    int x, y;

    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    public String toString()
    {
        return "[" + x + ", " + y + "]";
    }
};

class PointComparator implements Comparator<Point> {
    public int compare(Point a, Point b)
    {
        if (a.x == b.x) return a.y - b.y;
        return a.x - b.x;
    }
}

class Prob {
    void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            int n = in.nextInt(),
                m = in.nextInt();
            if (n == 0 && m == 0) break;

            Point student[] = new Point[n * n];

            for (int i = 0; i < n * n; i++)
                student[i] = in.nextPoint();
            Arrays.sort(student, new PointComparator());

            int min = 0x3f3f3f3f;
            for (int k = 0; k + n <= m; k++) {
                int now = 0;
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        now += Math.abs(student[i * n + j].y - (k + j));
                min = Math.min(min, now);
            }

            out.println(min);
        }

        out.flush();
    }

    void debug(Object...x)
    {
        System.out.println(Arrays.deepToString(x));
    }
}

class MyReader {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer in;

    boolean hasNext() throws IOException
    {
        if (in == null || in.hasMoreTokens()) return true;
        String line = br.readLine();
        if (line == null) return false;
        in = new StringTokenizer(line);
        return true;
    }

    String next() throws IOException
    {
        while (in == null || !in.hasMoreTokens())
            in = new StringTokenizer(br.readLine());
        return in.nextToken();
    }

    int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }

    Point nextPoint() throws IOException
    {
        return new Point(nextInt() - 1, nextInt() - 1);
    }
}

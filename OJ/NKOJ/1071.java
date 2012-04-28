/*
 *  SRC: NKOJ 1071
 * PROB: 最大可分离值问题
 * ALGO: Computational Geometry
 * DATE: Apr 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    class Point {
        int x, y;

        Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        Point subtract(Point o)
        {
            return new Point(x - o.x, y - o.y);
        }
    }

    int cross(Point a, Point b)
    {
        return a.x * b.y - a.y * b.x;
    }

    boolean check(Point line, Vector<Point> S0, Vector<Point> Sk, int above)
    {
        for (Point a : S0) {
            for (Point b : Sk) {
                if (cross(line, b.subtract(a)) * above <= 0) {
                    return false;
                }
            }
        }

        return true;
    }

    void solve()
    {
        while (cin.hasNext()) {
            int n = cin.nextInt();
            Vector<Point>[] pointSet = new Vector[n + 1];
            Vector<Point> allOtherPoint = new Vector<Point>();

            for (int i = 0; i <= n; i++) {
                pointSet[i] = new Vector<Point>();

                String line = cin.next();
                String[] points = line.substring(0, line.length() - 2).split(";");
                for (String point : points) {
                    String[] xy = point.split(",");
                    pointSet[i].add(new Point(Integer.parseInt(xy[0]), Integer.parseInt(xy[1])));
                    if (i != 0) {
                        allOtherPoint.add(pointSet[i].lastElement());
                    }
                }
            }

            int ans = 0;
            for (int i = 0; i < allOtherPoint.size(); i++) {
                for (int j = i + 1; j < allOtherPoint.size(); j++) {
                    Point line = allOtherPoint.get(i).subtract(allOtherPoint.get(j));

                    int cnt = 0;
                    for (int k = 1; k <= n; k++) {
                        // check if all points in pointSet[k] is above pointSet[0]
                        if (check(line, pointSet[0], pointSet[k], 1)) {
                            cnt++;
                        }
                    }
                    ans = Math.max(ans, cnt);

                    cnt = 0;
                    for (int k = 1; k <= n; k++) {
                        // check if all points in pointSet[k] is below pointSet[0]
                        if (check(line, pointSet[0], pointSet[k], -1)) {
                            cnt++;
                        }
                    }
                    ans = Math.max(ans, cnt);
                }
            }

            System.out.println(ans);
        }
    }
}

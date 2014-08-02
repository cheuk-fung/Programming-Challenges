/*
 *  SRC: ZOJ 3544
 * PROB: Draw a Mess
 * ALGO: Disjoint set
 * DATE: Sep 26, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

class Main {
    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        MyReader cin = new MyReader();

        while (cin.hasNext()) {
            int n = cin.nextInt();
            int m = cin.nextInt();
            int q = cin.nextInt();

            Shape[] shapes = new Shape[q];
            for (int i = 0; i < q; i++) {
                String type = cin.next();
                switch (type.charAt(0)) {
                    case 'C':
                    case 'D':
                    case 'T':
                        shapes[q - 1 - i] = new Shape(type.charAt(0), cin.nextInt(), cin.nextInt(), cin.nextInt(), cin.nextInt() - 1);
                        break;
                    case 'R':
                        shapes[q - 1 - i] = new Shape(type.charAt(0), cin.nextInt(), cin.nextInt(), cin.nextInt(), cin.nextInt(), cin.nextInt() - 1);
                }
            }

            int[] pixels = new int[9];
            for (int x = 0; x < n; x++) {
                DisjointSet disjointSet = new DisjointSet(m + 1);
                for (Shape shape : shapes) {
                    int l = -1, r = -1;
                    switch (shape.type) {
                        case 'C': {
                            int t = shape.r * shape.r - (x - shape.xc) * (x - shape.xc);
                            if (t < 0) continue;
                            t = (int)Math.sqrt(t);
                            l = Math.max(0, shape.yc - t);
                            r = Math.min(m - 1, shape.yc + t);
                            break;
                        }
                        case 'D': {
                            int t = shape.r - Math.abs(x - shape.xc);
                            if (t < 0) continue;
                            l = Math.max(0, shape.yc - t);
                            r = Math.min(m - 1, shape.yc + t);
                            break;
                        }
                        case 'T': {
                            int h = shape.r >> 1;
                            if (!(shape.xc <= x && x <= shape.xc + h)) continue;
                            int t = shape.xc + h - x;
                            l = Math.max(0, shape.yc - t);
                            r = Math.min(m - 1, shape.yc + t);
                            break;
                        }
                        case 'R': {
                            if (!(shape.xc <= x && x <= shape.xc + shape.l - 1)) continue;
                            l = shape.yc;
                            r = Math.min(m - 1, shape.yc + shape.r - 1);
                        }
                    }
                    while (l <= r) {
                        l = disjointSet.find(l);
                        if (l <= r) {
                            pixels[shape.c]++;
                            disjointSet.join(l + 1, l);
                        }
                    }
                }
            }
            for (int i = 0; i < 9; i++) {
                System.out.print(pixels[i] + (i == 8 ? "\n" : " "));
            }
        }
    }

    class Shape {
        private char type;
        private int xc, yc, r, l, c;

        public Shape(char type, int xc, int yc, int r, int c)
        {
            this.type = type;
            this.xc = xc;
            this.yc = yc;
            this.r = r;
            this.c = c;
        }

        public Shape(char type, int xc, int yc, int l, int r, int c)
        {
            this.type = type;
            this.xc = xc;
            this.yc = yc;
            this.l = l;
            this.r = r;
            this.c = c;
        }
    }

    class DisjointSet {
        private int[] ancestor;

        public DisjointSet(int size)
        {
            ancestor = new int[size];
            Arrays.fill(ancestor, -1);
        }

        private int find(int u)
        {
            int r = u;
            while (ancestor[r] >= 0) r = ancestor[r];
            while (ancestor[u] >= 0) {
                int v = ancestor[u];
                ancestor[u] = r;
                u = v;
            }
            return r;
        }

        private void join(int u, int v)
        {
            int x = find(u);
            int y = find(v);
            if (x != y) {
                ancestor[x] += ancestor[y];
                ancestor[y] = x;
            }
        }
    }

    class MyReader {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer in;

        boolean hasNext()
        {
            while (in == null || !in.hasMoreTokens()) {
                try {
                    in = new StringTokenizer(br.readLine());
                } catch (Exception e) {
                    return false;
                }
            }
            return true;
        }

        String next()
        {
            if (hasNext()) return in.nextToken();
            return null;
        }

        int nextInt() { return Integer.parseInt(next()); }
    }
}

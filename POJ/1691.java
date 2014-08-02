/*
 *  SRC: POJ 1691
 * PROB: Painting A Board
 * ALGO: Memorize Search
 * DATE: Jul 12, 2012
 * COMP: jdk 6
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
    final static int INF = 0x3f3f3f3f;
    static Scanner cin = new Scanner(System.in);
    Rectangle[] rect;
    Vector<Integer>[] above;
    int[] f;

    class Rectangle {
        int id, x1, y1, x2, y2, c;
        Rectangle(int x1, int y1, int x2, int y2, int c)
        {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
            this.c  = c;
        }
    }

    boolean checkAbove(int painted, int x)
    {
        for (int i : above[x]) {
            if ((painted & (1 << i)) == 0) return false;
        }
        return true;
    }

    void search(int painted, int cnt)
    {
        if (cnt >= f[painted]) return ;
        f[painted] = cnt;

        for (int i = 0; i < rect.length; i++) {
            if ((painted & (1 << i)) > 0) continue;
            if (checkAbove(painted, i)) {
                int newPainted = painted;
                while (true) {
                    boolean isContinued = false;
                    for (int j = 0; j < rect.length; j++) {
                        if ((newPainted & (1 << j)) == 0 && rect[j].c == rect[i].c && checkAbove(newPainted, j)) {
                            newPainted |= 1 << j;
                            isContinued = true;
                        }
                    }
                    if (!isContinued) break;
                }
                search(newPainted, cnt + 1);
            }
        }
    }

    void solve()
    {
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int n = cin.nextInt();
            rect = new Rectangle[n];
            above = new Vector[n];
            for (int i = 0; i < n; i++) {
                rect[i] = new Rectangle(cin.nextInt(), cin.nextInt(), cin.nextInt(), cin.nextInt(), cin.nextInt());
                above[i] = new Vector<Integer>();
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == i) continue;
                    if (rect[i].x1 < rect[j].x1 && ((rect[i].y1 <= rect[j].y1 && rect[j].y1 < rect[i].y2) || (rect[i].y1 < rect[j].y2 && rect[j].y2 <= rect[i].y2))) {
                        above[j].add(i);
                    }
                }
            }

            f = new int[1 << n];
            Arrays.fill(f, INF);
            search(0, 0);
            System.out.println(f[(1 << n) - 1]);
        }
    }
}

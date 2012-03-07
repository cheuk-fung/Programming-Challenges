/*
 *  SRC: POJ 3087
 * PROB: Shuffle'm Up
 * ALGO: Trie
 * DATE: Mar 07, 2012
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

class Trie {
    int charsetSize;

    class Tnode {
        Tnode[] next;
        boolean exist;
    }
    Tnode root = new Tnode();

    Trie(int _charsetSize)
    {
        charsetSize = _charsetSize;
    }

    boolean insert(String s)
    {
        Tnode p = root;
        for (int i = 0; i < s.length(); i++) {
            int idx = s.charAt(i) - 'A';
            if (p.next == null) p.next = new Tnode[charsetSize];
            if (p.next[idx] == null) p.next[idx] = new Tnode();
            p = p.next[idx];
        }
        if (p.exist) return false;
        p.exist = true;

        return true;
    }
}

class Prob {
    static final Scanner cin = new Scanner(System.in);

    void solve()
    {
        int n = cin.nextInt();
TASK_LOOP:
        for (int task = 1; task <= n; task++) {
            int c = cin.nextInt();
            String s1 = cin.next();
            String s2 = cin.next();
            String target = cin.next();

            Trie trie = new Trie('H' - 'A' + 1);

            System.out.print(task + " ");
            for (int cnt = 1; ; cnt++) {
                String s12 = "";
                for (int i = 0; i < c; i++)
                    s12 += s2.substring(i,i + 1) + s1.substring(i,i + 1);
                if (s12.equals(target)) {
                    System.out.println(cnt);
                    continue TASK_LOOP;
                }

                if (!trie.insert(s12)) break;

                s1 = s12.substring(0, c);
                s2 = s12.substring(c);
            }

            System.out.println(-1);
        }
    }
}

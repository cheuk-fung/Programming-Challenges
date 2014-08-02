/*
 *  SRC: POJ 1625
 * PROB: Censored!
 * ALGO: AC Automaton
 * DATE: Aug 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

import java.util.*;
import java.io.*;
import java.math.BigInteger;

class ACAutomaton {
    private int charset;
    private int[] alphabet = new int[256];

    class Tnode {
        Tnode[] next = new Tnode[50];
        Tnode fail;
        boolean exist;
        int idx;
    }
    private Tnode root = new Tnode();
    private ArrayList<Tnode> nodes = new ArrayList<Tnode>();

    ACAutomaton()
    {
        root.idx = nodes.size();
        nodes.add(root);
    }

    void buildAlphabet(String s)
    {
        charset = s.length();
        for (int i = 0; i < s.length(); i++) {
            alphabet[s.charAt(i)] = i;
        }
    }

    void insert(String s)
    {
        Tnode p = root;
        for (char c : s.toCharArray()) {
            if (p.next[alphabet[c]] == null) {
                p.next[alphabet[c]] = new Tnode();
                p.next[alphabet[c]].idx = nodes.size();
                nodes.add(p.next[alphabet[c]]);
            }
            p = p.next[alphabet[c]];
        }
        p.exist = true;
    }

    void buildFail()
    {
        Queue<Tnode> que = new LinkedList<Tnode>();
        for (int i = 0; i < charset; i++) {
            if (root.next[i] != null) {
                root.next[i].fail = root;
                que.add(root.next[i]);
            } else {
                root.next[i] = root;
            }
        }

        while (!que.isEmpty()) {
            Tnode u = que.remove();
            u.exist |= u.fail.exist;
            for (int i = 0; i < charset; i++) {
                if (u.next[i] != null) {
                    u.next[i].fail = u.fail.next[i];
                    que.add(u.next[i]);
                } else {
                    u.next[i] = u.fail.next[i];
                }
            }
        }
    }

    BigInteger query(int m)
    {
        BigInteger[][] f = new BigInteger[m + 1][nodes.size()];
        f[0][0] = BigInteger.ONE;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < nodes.size(); j++) {
                if (f[i][j] == null || nodes.get(j).exist) continue;
                for (int k = 0; k < charset; k++) {
                    if (nodes.get(j).next[k].exist) continue;
                    int idx = nodes.get(j).next[k].idx;
                    if (f[i + 1][idx] == null) f[i + 1][idx] = BigInteger.ZERO;
                    f[i + 1][idx] = f[i + 1][idx].add(f[i][j]);
                }
            }
        }

        BigInteger res = BigInteger.ZERO;
        for (int i = 0; i < nodes.size(); i++) {
            if (f[m][i] != null) res = res.add(f[m][i]);
        }
        return res;
    }
}

class Main {
    void run()
    {
        try {
            BufferedReader bf = new BufferedReader(new InputStreamReader(System.in, "ISO-8859-1"));
            String[] args = bf.readLine().split(" ");
            int n = Integer.parseInt(args[0]);
            int m = Integer.parseInt(args[1]);
            int p = Integer.parseInt(args[2]);
            ACAutomaton ac = new ACAutomaton();
            ac.buildAlphabet(bf.readLine());
            for (int i = 0; i < p; i++) ac.insert(bf.readLine());
            ac.buildFail();
            BigInteger r = ac.query(m);
            System.out.println(r);
        } catch (IOException e) {
        }
    }

    public static void main(String[] args)
    {
        new Main().run();
    }
}

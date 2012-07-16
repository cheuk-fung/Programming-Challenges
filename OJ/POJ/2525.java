/*
 *  SRC: POJ 2525
 * PROB: Text Formalization
 * ALGO: String
 * DATE: Jul 16, 2012
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Prob().solve();
    }
}

class Trie {
    class Tnode {
        Tnode[] next = new Tnode[256];
        int id = -1;
    }
    Tnode root = new Tnode();

    void insert(String s, int id)
    {
        Tnode p = root;
        for (char c : s.toCharArray()) {
            if (p.next[c] == null) {
                p.next[c] = new Tnode();
            }
            p = p.next[c];
        }
        p.id = id;
    }

    int query(String s)
    {
        Tnode p = root;
        for (char c : s.toCharArray()) {
            if (p.next[c] == null) {
                return p.id;
            }
            p = p.next[c];
        }
        return p.id;
    }
}

class Prob {
    Scanner cin = new Scanner(System.in);
    PrintWriter out = new PrintWriter(System.out);

    String allToUpperCase(String s)
    {
        String r = "";
        for (char c : s.toCharArray()) {
            r += Character.toUpperCase(c);
        }
        return r;
    }

    void solve()
    {
        int c = cin.nextInt();
        int a = cin.nextInt();
        cin.nextLine();

        ArrayList<String> contractionKey = new ArrayList<String>();
        ArrayList<String> contractionValue = new ArrayList<String>();
        Trie contraction = new Trie();

        for (int i = 0; i < c; i++) {
            String[] words = cin.nextLine().split("->");
            String key = words[0].trim().replace("\"", "");
            String value = words[1].trim().replace("\"", "");
            contractionKey.add(key);
            contractionValue.add(value);
            if (contraction.query(key) == -1) {
                contraction.insert(key, contractionKey.size() - 1);
            }

            key = Character.toUpperCase(key.charAt(0)) + key.substring(1);
            value = Character.toUpperCase(value.charAt(0)) + value.substring(1);
            contractionKey.add(key);
            contractionValue.add(value);
            if (contraction.query(key) == -1) {
                contraction.insert(key, contractionKey.size() - 1);
            }

            key = allToUpperCase(key);
            value = allToUpperCase(value);
            contractionKey.add(key);
            contractionValue.add(value);
            if (contraction.query(key) == -1) {
                contraction.insert(key, contractionKey.size() - 1);
            }
        }

        ArrayList<String> acronymKey = new ArrayList<String>();
        ArrayList<String> acronymValue = new ArrayList<String>();
        Trie acronym = new Trie();
        for (int i = 0; i < a; i++) {
            String[] words = cin.nextLine().split("->");
            String key = words[0].trim().replace("\"", "");
            String value = words[1].trim().replace("\"", "");
            acronymKey.add(key);
            acronymValue.add(value);
            if (acronym.query(key) == -1) {
                acronym.insert(key, acronymKey.size() - 1);
            }
        }

        while (cin.hasNext()) {
            boolean[] usedAcronym = new boolean[a];
            for (String line = cin.nextLine(); !line.equals("#"); line = cin.nextLine()) {
                for (int pos = 0; pos != line.length(); pos++) {
                    String word = line.substring(pos);
                    int id = contraction.query(word);
                    if (id != -1) {
                        out.print(contractionValue.get(id));
                        pos += contractionKey.get(id).length() - 1;
                        continue;
                    }

                    id = acronym.query(word);
                    if (id != -1 && !usedAcronym[id]) {
                        out.print(acronymValue.get(id) + " (" + acronymKey.get(id) + ")");
                        pos += acronymKey.get(id).length() - 1;
                        usedAcronym[id] = true;
                        continue;
                    }

                    out.print(line.charAt(pos));
                }
                out.println();
            }
            out.println("#");
        }

        out.flush();
    }

    static void debug(Object...o)
    {
        System.out.println(Arrays.deepToString(o));
    }
}

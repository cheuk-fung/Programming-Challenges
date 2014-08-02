/*
 *  SRC: HDOJ 3901
 * PROB: Wildcard
 * ALGO: AC Automaton
 * DATE: Oct 28, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Main {
    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            String text = cin.nextLine();
            String[] pattern = cin.nextLine().split("\\*");

            boolean ok = true;
            int lastPosition = 0;
            for (String str : pattern) {
                ACAutomaton ac = new ACAutomaton();
                int firstPosition = -1;
                for (String s : str.split("\\?")) {
                    if (s.equals("")) {
                        firstPosition++;
                        continue;
                    }
                    ac.insert(s, ++firstPosition);
                    firstPosition += s.length();
                }
                ac.buildFail();

                lastPosition = ac.query(text, lastPosition);
                if (lastPosition != -1) lastPosition += str.length();
                if (lastPosition == -1 || lastPosition > text.length()) {
                    ok = false;
                    break;
                }
            }
            System.out.println(ok ? "YES" : "NO");
        }
        cin.close();
    }

    private class ACAutomaton {
        private class Tnode {
            Tnode[] next = new Tnode[26];
            Tnode fail;
            ArrayList<Integer> position = new ArrayList<Integer>();
        }
        Tnode root = new Tnode();
        int strcnt = 0;

        public void insert(String s, int firstPosition)
        {
            Tnode p = root;
            for (int i = 0; i < s.length(); i++) {
                int idx = s.charAt(i) - 'a';
                if (p.next[idx] == null) p.next[idx] = new Tnode();
                p = p.next[idx];
            }
            p.position.add(firstPosition + s.length() - 1);
            strcnt++;
        }

        public void buildFail()
        {
            Queue<Tnode> Q = new LinkedList<Tnode>();
            for (int i = 0; i < 26; i++) {
                if (root.next[i] != null) {
                    Q.add(root.next[i]);
                    root.next[i].fail = root;
                } else {
                    root.next[i] = root;
                }
            }
            while (!Q.isEmpty()) {
                Tnode u = Q.poll();
                for (int i = 0; i < 26; i++) {
                    if (u.next[i] != null) {
                        Q.add(u.next[i]);
                        u.next[i].fail = u.fail.next[i];
                    } else {
                        u.next[i] = u.fail.next[i];
                    }
                }
            }
        }

        public int query(String s, int firstPositon)
        {
            int[] cnt = new int[s.length()];
            Tnode p = root;
            for (int i = firstPositon; i < s.length(); i++) {
                p = p.next[s.charAt(i) - 'a'];
                for (int pos : p.position) {
                    if (i - pos >= 0) {
                        cnt[i - pos]++;
                    }
                }
            }
            for (int i = firstPositon; i < s.length(); i++) {
                if (cnt[i] == strcnt) {
                    return i;
                }
            }

            return -1;
        }
    }
}

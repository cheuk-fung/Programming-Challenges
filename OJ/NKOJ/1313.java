/*
 *  SRC: NKOJ p1313
 * PROB: Tautology
 * ALGO: enum & stack
 * DATE: Jun 5, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;
import java.util.Stack;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        while (1 + 1 == 2) {
            String s = cin.next();
            if (s.compareTo("0") == 0) break;

            new Prob().solve(s);
        }
    }
}

class Prob
{
    private String s;
    private boolean[] existed = new boolean[255];
    private char[] var = new char[5];
    private int vSum;
    private boolean[] value = new boolean[255];
    private boolean[] b = {false, true};
    private boolean flag = true;

    public boolean check()
    {
        Stack<Boolean> aStack = new Stack<Boolean>();
        for (int i = s.length() - 1; i >= 0; i--) {
            char c = s.charAt(i);
            boolean w, x;
            switch(c) {
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                    aStack.push(value[c]);
                    break;
                case 'N':
                    w = aStack.pop();
                    aStack.push(!w);
                    break;
                case 'K':
                    w = aStack.pop(); x = aStack.pop();
                    aStack.push(w && x);
                    break;
                case 'A':
                    w = aStack.pop(); x = aStack.pop();
                    aStack.push(w || x);
                    break;
                case 'E':
                    w = aStack.pop(); x = aStack.pop();
                    aStack.push(w == x);
                    break;
                case 'C':
                    w = aStack.pop(); x = aStack.pop();
                    if (w == true && x == false) aStack.push(false);
                    else aStack.push(true);
            }
        }

        return aStack.pop();
    }

    public void enumVar(int p)
    {
        if (p == vSum) {
            if (check() == false) {
                System.out.println("not");
                flag = false;
            }
            return ;
        }

        for (boolean i : b) {
            value[var[p]] = i;
            enumVar(p + 1);
            if (flag == false) return;
        }
    }

    public void solve(String ss)
    {
        s = ss;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch(c) {
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                    if (existed[c] == false) {
                        var[vSum++] = c;
                        existed[c] = true;
                    }
            }
        }

        enumVar(0);

        if (flag == true) System.out.println("tautology");
    }
}


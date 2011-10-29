/*
 *  SRC: HDOJ ACM Steps
 * PROB: 排名
 * ALGO: NULL
 * DATE: Oct 29, 2011
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.io.*;
import java.util.*;

class Main {
    public static void main(String[] args) throws IOException
    {
        new Prob().solve();
    }
}

class Student implements Comparable<Student> {
    String name;
    int score;

    Student(String _name, int _score)
    {
        name = _name;
        score = _score;
    }

    public String getName() { return name; }
    public int getScore() { return score; }

    public void print(PrintWriter out)
    {
        out.println(name + " " + score);
    }

    public int compareTo(Student other)
    {
        if (score == other.getScore())
            return name.compareTo(other.getName());
        return other.getScore() - score;
    }
}

class Prob {
    public void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        while (true) {
            int n = in.nextInt();
            if (n == 0) break;
            int m = in.nextInt(),
                g = in.nextInt(),
                score[] = new int[m];
            for (int i = 0; i < m; i++)
                score[i] = in.nextInt();

            Student students[] = new Student[n];
            for (int i = 0; i < n; i++) {
                String name = in.next();
                int cnt = in.nextInt(),
                    totScore = 0;
                for (int j = 0; j < cnt; j++)
                    totScore += score[in.nextInt() - 1];
                students[i] = new Student(name, totScore);
            }
            Arrays.sort(students);

            int pass_cnt = 0;
            for ( ; pass_cnt < n && students[pass_cnt].getScore() >= g; pass_cnt++) ;
            out.println(pass_cnt);
            for (int i = 0; i < pass_cnt; i++)
                students[i].print(out);

            out.flush();
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

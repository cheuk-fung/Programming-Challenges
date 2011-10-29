/*
 *  SRC: HDOJ ACM Steps
 * PROB: Rank
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

class StudentComparator implements Comparator<Student>{
    public int compare(Student a, Student b)
    {
        if (a.getMark() == b.getMark()) {
            if (a.getId() == Student.jackson) return -1;
            if (b.getId() == Student.jackson) return 1;
            return 0;
        }
        return b.getMark() - a.getMark();
    }
}

class Student {
    static int jackson;
    int id, mark;

    public int getId() { return id; }
    public int getMark() { return mark; }

    public Student(int _id, int _mark)
    {
        id = _id;
        mark = _mark;
    }
}

class Prob {
    static Student stu[] = new Student[1010];

    public void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        while (in.hasNext()) {
            Student.jackson = in.nextInt();

            int cnt = 0;
            while (true) {
                int id = in.nextInt(),
                    mark = in.nextInt();
                if (id == 0 && mark == 0) break;
                stu[cnt++] = new Student(id, mark);
            }
            Arrays.sort(stu, 0, cnt, new StudentComparator());

            for (int i = 0; i < cnt; i++)
                if (stu[i].getId() == Student.jackson) {
                    out.println(i + 1);
                    break;
                }
        }

        out.flush();
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

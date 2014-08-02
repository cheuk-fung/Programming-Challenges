/*
 *  SRC: HDOJ ACM Steps
 * PROB: 开门人和关门人
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

class ArrivalTimeComparator implements Comparator<Person> {
    public int compare(Person p1, Person p2)
    {
        return p1.getArrivalTime().compareTo(p2.getArrivalTime());
    }
}

class LeaveTimeComparator implements Comparator<Person> {
    public int compare(Person p1, Person p2)
    {
        return -p1.getLeaveTime().compareTo(p2.getLeaveTime());
    }
}

class Person {
    String id, arrivalTime, leaveTime;

    String getId() { return id; }
    String getArrivalTime() { return arrivalTime; }
    String getLeaveTime() { return leaveTime; }

    public Person(String _id, String _arrivalTime, String _leaveTime)
    {
        id = _id;
        arrivalTime = _arrivalTime;
        leaveTime = _leaveTime;
    }
}

class Prob {
    public void solve() throws IOException
    {
        MyReader in = new MyReader();
        PrintWriter out = new PrintWriter(System.out);

        int tasks = in.nextInt();
        while (tasks-- > 0) {
            int n = in.nextInt();
            Person p[] = new Person[n];
            for (int i = 0; i < n; i++)
                p[i] = new Person(in.next(), in.next(), in.next());
            Arrays.sort(p, new ArrivalTimeComparator());
            System.out.print(p[0].getId());
            Arrays.sort(p, new LeaveTimeComparator());
            System.out.println(" " + p[0].getId());
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

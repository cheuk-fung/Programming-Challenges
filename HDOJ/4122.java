/*
 *  SRC: HDOJ 4122
 * PROB: Alice's mooncake shop
 * ALGO: Monotone priority queue
 * DATE: Sep 27, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Calendar;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.StringTokenizer;

class Main {
    private int[] cost;

    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        MyReader in = new MyReader();

        HashMap<String, Integer> month = new HashMap<String, Integer>();
        month.put("Jan", 0);
        month.put("Feb", 1);
        month.put("Mar", 2);
        month.put("Apr", 3);
        month.put("May", 4);
        month.put("Jun", 5);
        month.put("Jul", 6);
        month.put("Aug", 7);
        month.put("Sep", 8);
        month.put("Oct", 9);
        month.put("Nov", 10);
        month.put("Dec", 11);

        Calendar calendar = Calendar.getInstance();
        calendar.clear();
        calendar.set(2000, 0, 1, 0, 0, 0);
        long first = calendar.getTimeInMillis();

        while (true) {
            int n = in.nextInt();
            int m = in.nextInt();
            if (n == 0 && m == 0) break;

            Order[] orders = new Order[n];
            for (int i = 0; i < n; i++) {
                String mon = in.next();
                int mday = in.nextInt();
                int year = in.nextInt();
                int hour = in.nextInt();
                calendar.clear();
                calendar.set(year, month.get(mon), mday, hour, 0, 0);
                long now = calendar.getTimeInMillis();
                orders[i] = new Order((int)((now - first) / 3600000), in.nextInt());
            }

            int T = in.nextInt();
            int S = in.nextInt();
            cost = new int[m];
            for (int i = 0; i < m; i++) {
                cost[i] = in.nextInt();
            }

            long ans = 0;
            Deque<Integer> deque = new LinkedList<Integer>();
            for (int i = 0, j = 0; i < m && j < n; i++) {
                while (!deque.isEmpty() && i - deque.peekFirst() > T) deque.removeFirst();
                while (!deque.isEmpty() && key(i, S) <= key(deque.peekLast(), S)) deque.removeLast();
                deque.addLast(i);
                while (j < n && orders[j].time == i) {
                    ans += (long)(i * S + key(deque.peekFirst(), S)) * orders[j++].amount;
                }
            }

            System.out.println(ans);
        }
    }

    private int key(int x, int S)
    {
        return cost[x] - S * x;
    }

    class Order {
        int time, amount;

        public Order(int time, int amount)
        {
            this.time = time;
            this.amount = amount;
        }
    }

    class MyReader {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer token;

        boolean hasNext()
        {
            while (token == null || !token.hasMoreTokens()) {
                try {
                    token = new StringTokenizer(br.readLine());
                } catch (Exception e) {
                    return false;
                }
            }
            return true;
        }

        String next()
        {
            if (hasNext()) return token.nextToken();
            return null;
        }

        int nextInt()
        {
            return Integer.parseInt(next());
        }
    }
}

/*
 *  SRC: HDOJ 4407
 * PROB: Sum
 * ALGO: Math
 * DATE: Sep 23, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.math.BigInteger;
import java.util.*;

class Main {
    public static void main(String[] args)
    {
        new Main().run();
    }

    private void run()
    {
        Scanner cin = new Scanner(System.in);

        Integer[] prime = getPrime((int)Math.sqrt(400000) + 1);
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            int n = cin.nextInt();
            int m = cin.nextInt();
            Map<Integer, Integer> change = new HashMap<Integer, Integer>();
            while (m-- > 0) {
                int type = cin.nextInt();
                if (type == 1) {
                    int x = cin.nextInt();
                    int y = cin.nextInt();
                    int p = cin.nextInt();
                    long sum = countCoPrime(y, p, prime) - countCoPrime(x - 1, p, prime);
                    for (Map.Entry<Integer, Integer> opr : change.entrySet()) {
                        if (x <= opr.getKey() && opr.getKey() <= y) {
                            if (gcd(opr.getValue(), p) == 1) {
                                sum += opr.getValue();
                            }
                            if (gcd(opr.getKey(), p) == 1) {
                                sum -= opr.getKey();
                            }
                        }
                    }
                    System.out.println(sum);
                } else {
                    change.put(cin.nextInt(),cin.nextInt());
                }
            }
        }
    }

    private int gcd(int a, int b)
    {
        while (b != 0) {
            int t = a;
            a = b;
            b = t % b;
        }
        return a;
    }

    private long countCoPrime(int x, int p, Integer[] prime)
    {
        ArrayList<Integer> factor = new ArrayList<Integer>();

        int t = p;
        for (int i = 0; i < prime.length && prime[i] * prime[i] <= t; i++) {
            if (t % prime[i] == 0) {
                factor.add(prime[i]);
                while (t % prime[i] == 0) {
                    t /= prime[i];
                }
            }
        }
        if (t != 1) factor.add(t);

        long r = 0;
        for (int s = 0; s < 1 << factor.size(); s++) {
            int sign = 1;
            long now = 1;
            for (int i = 0; i < factor.size(); i++) {
                if ((s & 1 << i) != 0) {
                    sign *= -1;
                    now *= factor.get(i);
                }
            }
            long sum = (now + now * (x / now)) * (x / now) / 2;
            r += sum * sign;
        }
        return r;
    }

    private Integer[] getPrime(int n)
    {
        boolean[] isPrime = new boolean[n];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        ArrayList<Integer> prime = new ArrayList<Integer>();
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) prime.add(i);
            for (int j = 0; j < prime.size() && i * prime.get(j) < n; j++) {
                isPrime[i * prime.get(j)] = false;
                if (i % prime.get(j) == 0) break;
            }
        }
        return prime.toArray(new Integer[prime.size()]);
    }
}

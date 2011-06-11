/*
 *  SRC: POJ 2240
 * PROB: Arbitrage
 * ALGO: Floyd
 * DATE: Jun 6, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int t = 0;
        
        while (1 + 1 == 2) {
            int n = cin.nextInt();
            if (n == 0) break;
            new Prob().solve(++t, n, cin);
        }
    }
}

class Prob 
{
    public static final double EPS = 1e-12;

    public double[][] dist;

    public void floyd(int n)
    {
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i][j] < dist[i][k] * dist[k][j] + EPS)
                        dist[i][j] = dist[i][k] * dist[k][j];
    }

    public void solve(int t, int n, Scanner cin)
    {
        Map<String, Integer> names = new HashMap<String, Integer>();

        dist = new double[n][];
        for (int i = 0; i < n; i++) {
            dist[i] = new double[n];
            String name = cin.next();
            names.put(name, i);
        }

        int m = cin.nextInt();
        for (int i = 0; i < m; i++) {
            String a = cin.next();
            double rate = cin.nextDouble();
            String b = cin.next();
            dist[names.get(a)][names.get(b)] = rate;
        }

        floyd(n);

        for (int i = 0; i < n; i++) {
            if (dist[i][i] > 1.0 - EPS) {
                System.out.println("Case " + t + ": Yes");
                return ;
            }
        }

        System.out.println("Case " + t + ": No");
    }
}

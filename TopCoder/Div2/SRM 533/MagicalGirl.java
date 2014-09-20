import java.util.*;

public class MagicalGirl {
    public double maxExpectation(int M, int[] day, int[] win, int[] gain)
    {
        int N = day.length;
        Witch[] w = new Witch[N + 1];

        // f[i][j] denotes expectation in case after the i-th witch appears,
        // my total Life Points is j.
        double[][] f = new double[N + 1][M + 1];

        w[0] = new Witch(0, 0, 0);
        for (int i = 1; i <= N; i++)
            w[i] = new Witch(day[i - 1], win[i - 1] / 100.0, gain[i - 1]);
        Arrays.sort(w, 1, N + 1);

        for (int i = N; i >= 0; i--)
            for (int j = 1; j <= M; j++) {
                if (i == N || j - (w[i + 1].day - w[i].day) <= 0)
                    f[i][j] = w[i].day + j;
                else f[i][j] = Math.max(f[i + 1][j - (w[i + 1].day - w[i].day)], // Don't fight with the (i + 1)-th witch.
                                        w[i + 1].day * (1.0 - w[i + 1].win) + // Fight but lose.
                                        f[i + 1][Math.min(M, j - (w[i + 1].day - w[i].day) + w[i + 1].gain)] * w[i + 1].win); // Fight and win.
            }

        return f[0][M];
    }
}

class Witch implements Comparable {
    int day, gain;
    double win;

    Witch(int _day, double _win, int _gain)
    {
        day = _day;
        win = _win;
        gain = _gain;
    }

    public int compareTo(Object other)
    {
        return day - ((Witch)other).day;
    }
}


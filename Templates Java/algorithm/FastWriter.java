package algorithm;

import java.io.PrintWriter;
import java.util.Arrays;

public class FastWriter extends PrintWriter {

    public FastWriter() {
        super(System.out);
    }

    public void println(double[] a) {
        for (var i = 0; i < a.length; i++) {
            print(a[i]);
            print(i + 1 < a.length ? ' ' : '\n');
        }
    }

    public void println(int[] a) {
        for (var i = 0; i < a.length; i++) {
            print(a[i]);
            print(i + 1 < a.length ? ' ' : '\n');
        }
    }

    public void println(long[] a) {
        for (var i = 0; i < a.length; i++) {
            print(a[i]);
            print(i + 1 < a.length ? ' ' : '\n');
        }
    }

    public <T> void println(T[] a) {
        for (var i = 0; i < a.length; i++) {
            print(a[i]);
            print(i + 1 < a.length ? ' ' : '\n');
        }
    }

    public void debug(String name, Object o) {
        String value = Arrays.deepToString(new Object[] { o });
        value = value.substring(1, value.length() - 1);
        System.err.println(name + " => " + value);
    }

}

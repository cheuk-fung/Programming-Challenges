package algorithm;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.stream.Collectors;

public class ArrayUtils {

    public static int[] of(int n, int defaultValue) {
        var a = new int[n];
        Arrays.fill(a, defaultValue);
        return a;
    }

    public static long[] of(int n, long defaultValue) {
        var a = new long[n];
        Arrays.fill(a, defaultValue);
        return a;
    }

    public static int max(int[] a) {
        return Arrays.stream(a).max().getAsInt();
    }

    public static long max(long[] a) {
        return Arrays.stream(a).max().getAsLong();
    }

    public static <T extends Comparable<? super T>> T max(T[] a) {
        return Collections.max(Arrays.asList(a));
    }

    public static int min(int[] a) {
        return Arrays.stream(a).min().getAsInt();
    }

    public static long min(long[] a) {
        return Arrays.stream(a).min().getAsLong();
    }

    public static <T extends Comparable<? super T>> T min(T[] a) {
        return Collections.max(Arrays.asList(a));
    }

    public static void sort(int[] a) {
        var al = Arrays.stream(a).boxed().collect(Collectors.toCollection(ArrayList::new));
        Collections.shuffle(al);
        Collections.sort(al);

        for (var i = 0; i < a.length; i++) {
            a[i] = al.get(i);
        }
    }

    public static void sort(long[] a) {
        var al = Arrays.stream(a).boxed().collect(Collectors.toCollection(ArrayList::new));
        Collections.shuffle(al);
        Collections.sort(al);

        for (var i = 0; i < a.length; i++) {
            a[i] = al.get(i);
        }
    }

    public static void reverse(int[] a) {
        for (int l = 0, r = a.length - 1; l <= r; l++, r--) {
            var t = a[l];
            a[l] = a[r];
            a[r] = t;
        }
    }

    public static void reverse(long[] a) {
        for (int l = 0, r = a.length - 1; l <= r; l++, r--) {
            var t = a[l];
            a[l] = a[r];
            a[r] = t;
        }
    }

}

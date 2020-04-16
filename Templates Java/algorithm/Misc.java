package algorithm;

import java.util.Comparator;
import java.util.function.IntPredicate;
import java.util.function.IntToLongFunction;
import java.util.function.IntUnaryOperator;

public class Misc {

    public static final double EPS = 1e-12;

    public static final Comparator<Double> EPS_COMPARATOR = (x, y) -> {
        if (x + EPS < y) {
            return -1;
        } else if (x - EPS > y) {
            return 1;
        } else {
            return 0;
        }
    };

    public static int compare(double x, double y) {
        return EPS_COMPARATOR.compare(x, y);
    }

    /**
     * Returns the index of the first element in the range <b>[left, right)</b> which <i>leftShouldAdvance</i> tested to
     * be <i>false</i>.
     */
    public static int binarySearch(int left, int right, IntPredicate leftShouldAdvance) {
        while (left < right) {
            var mid = left + (right - left) / 2;
            if (leftShouldAdvance.test(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

    /**
     * Returns the index of the first element in <i>a</i> which >= <i>x</i>.
     */
    public static int lowerBound(int[] a, int x) {
        return binarySearch(0, a.length, mid -> a[mid] < x);
    }

    public static int lowerBound(long[] a, long x) {
        return binarySearch(0, a.length, mid -> a[mid] < x);
    }

    /**
     * Returns the index of the first element in <i>a</i> which > <i>x</i>.
     */
    public static int upperBound(int[] a, int x) {
        return binarySearch(0, a.length, mid -> a[mid] <= x);
    }

    public static int upperBound(long[] a, long x) {
        return binarySearch(0, a.length, mid -> a[mid] <= x);
    }

    /**
     * Searches for the maximum value of a unimodal function f(x).
     * <p>
     * A function f(x) is a <b>unimodal function</b> if for some value m, it is <b>monotonically increasing</b> for x ≤
     * m and <b>monotonically decreasing</b> for x ≥ m. In that case, the maximum value of f(x) is f(m) and there are no
     * other local maxima.
     */
    public static int ternarySearchMaxInt(int left, int right, IntUnaryOperator f) {
        return binarySearch(left, right, mid -> f.applyAsInt(mid) < f.applyAsInt(Math.min(mid + 1, right - 1)));
    }

    public static int ternarySearchMaxLong(int left, int right, IntToLongFunction f) {
        return binarySearch(left, right, mid -> f.applyAsLong(mid) < f.applyAsLong(Math.min(mid + 1, right - 1)));
    }

}

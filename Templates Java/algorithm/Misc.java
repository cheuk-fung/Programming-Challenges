package algorithm;

import java.util.Comparator;
import java.util.function.Function;
import java.util.function.Predicate;

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

    public static int binarySearch(int left, int right, Predicate<Integer> leftShouldAdvance) {
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
     * Search for the maximum value of a unimodal function f(x).
     * <p>
     * A function f(x) is a <b>unimodal function</b> if for some value m, it is <b>monotonically increasing</b> for x ≤
     * m and <b>monotonically decreasing</b> for x ≥ m. In that case, the maximum value of f(x) is f(m) and there are no
     * other local maxima.
     */
    public static int ternarySearch(int left, int right, Function<Integer, Integer> f) {
        return binarySearch(left, right, mid -> f.apply(mid) < f.apply(Math.min(mid + 1, right - 1)));
    }

}

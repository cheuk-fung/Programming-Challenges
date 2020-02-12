package algorithm;

import java.util.Comparator;
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

}

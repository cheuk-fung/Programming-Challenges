import java.util.*;

class RMQ<T extends Comparable<T>> {

    private final int n;
    private final List<T> values;
    private final Comparator<T> comparator;
    private final int[][] ranges;

    public RMQ(List<T> values) {
        this(values, Comparator.naturalOrder());
    }

    public RMQ(List<T> values, Comparator<T> comparator) {
        this.values = values;
        this.comparator = comparator;
        this.n = values.size();
        this.ranges = new int[leftMostOneBit(n) + 1][];

        build();
    }

    private int leftMostOneBit(int x) {
        return Integer.SIZE - 1 - Integer.numberOfLeadingZeros(x);
    }

    private void build() {
        ranges[0] = new int[n];
        for (var i = 0; i < n; i++) {
            ranges[0][i] = i;
        }

        for (var i = 1; 1 << i <= n; i++) {
            ranges[i] = new int[n - (1 << i) + 1];
            for (var j = 0; j + (1 << i) <= n; j++) {
                ranges[i][j] = betterIndex(ranges[i - 1][j], ranges[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    private int betterIndex(int l, int r) {
        return comparator.compare(values.get(l), values.get(r)) < 0 ? l : r;
    }

    public int queryIndex(int l, int r) {
        var exponent = leftMostOneBit(r - l);
        return betterIndex(ranges[exponent][l], ranges[exponent][r - (1 << exponent)]);
    }

    public T query(int l, int r) {
        return values.get(queryIndex(l, r));
    }

}

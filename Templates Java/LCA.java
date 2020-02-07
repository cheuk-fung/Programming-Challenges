import java.util.*;

class LCA {

    private final List<Node> nodes;
    private final List<Node> eulerTour;
    private RMQ<Node> rmq;

    public LCA(int n) {
        this.nodes = new ArrayList<>(n);
        this.eulerTour = new ArrayList<>(n * 2 - 1);

        for (var i = 0; i < n; i++) {
            nodes.add(new Node(i));
        }
    }

    public void addEdge(int u, int v) {
        addEdge(u, v, 1);
    }

    public void addEdge(int u, int v, int weight) {
        nodes.get(u).addNeighbor(nodes.get(v), weight);
    }

    public void addBidirectedEdges(int u, int v) {
        addBidirectedEdges(u, v, 1);
    }

    public void addBidirectedEdges(int u, int v, int weight) {
        addEdge(u, v, weight);
        addEdge(v, u, weight);
    }

    public void build() {
        build(0);
    }

    public void build(int root) {
        dfs(nodes.get(root), new Node(-1), 0, 0);
        rmq = new RMQ<>(eulerTour);
    }

    public int query(int x, int y) {
        var l = nodes.get(x).firstSeenInEulerTour;
        var r = nodes.get(y).firstSeenInEulerTour;
        if (l > r) {
            var t = l;
            l = r;
            r = t;
        }

        return rmq.query(l, r + 1).label;
    }

    public int parent(int u) {
        return nodes.get(u).parent.label;
    }

    public int distance(int x, int y) {
        return nodes.get(x).distance + nodes.get(y).distance - nodes.get(query(x, y)).distance * 2;
    }

    private int dfs(Node u, Node parent, int preOrderIndex, int distance) {
        u.parent = parent;
        u.distance = distance;
        u.preOrderIndex = preOrderIndex;
        u.firstSeenInEulerTour = eulerTour.size();
        eulerTour.add(u);

        var subTreeSize = 1;
        for (var e : u.neighbors) {
            var v = e.neighbor;
            if (v.label != parent.label) {
                subTreeSize += dfs(v, u, preOrderIndex + subTreeSize, u.distance + e.weight);
                eulerTour.add(u);
            }
        }

        return subTreeSize;
    }

    private static class Node implements Comparable<Node> {

        final int label;
        final List<Edge> neighbors = new ArrayList<>();

        Node parent;
        int distance;
        int preOrderIndex;
        int firstSeenInEulerTour;

        Node(int label) {
            this.label = label;
        }

        public void addNeighbor(Node neighbor, int weight) {
            neighbors.add(new Edge(neighbor, weight));
        }

        @Override
        public int compareTo(Node o) {
            return Integer.compare(this.preOrderIndex, o.preOrderIndex);
        }

        @Override
        public java.lang.String toString() {
            return "LCA.Node("
                    + "label=" + this.label + ", "
                    + "neighbors=" + this.neighbors + ", "
                    + "parent=" + this.parent + ", "
                    + "distance=" + this.distance + ", "
                    + "preOrderIndex=" + this.preOrderIndex + ", "
                    + "firstSeenInEulerTour=" + this.firstSeenInEulerTour
                    + ")";
        }

    }

    private static class Edge {

        Node neighbor;
        int weight;

        Edge(Node neighbor, int weight) {
            this.neighbor = neighbor;
            this.weight = weight;
        }

        @Override
        public java.lang.String toString() {
            return "LCA.Edge(neighbor=" + this.neighbor.label + ", weight=" + this.weight + ")";
        }

    }

    private static class RMQ<T extends Comparable<T>> {

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

}

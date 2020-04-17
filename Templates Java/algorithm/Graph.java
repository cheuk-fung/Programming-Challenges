package algorithm;

import algorithm.Tree;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public abstract class Graph<T> {

    public final int n;
    final List<List<T>> adjacencyList;

    Graph(int n) {
        this.n = n;
        this.adjacencyList = new ArrayList<>(n);

        for (var i = 0; i < n; i++) {
            this.adjacencyList.add(new ArrayList<>());
        }
    }

    public static UnweightedGraph unweighted(int n) {
        return new UnweightedGraph(n);
    }

    public static <T> WeightedGraph<T> weighted(int n) {
        return new WeightedGraph<>(n);
    }

    public List<T> neighbors(int u) {
        return adjacencyList.get(u);
    }

    public abstract int neighborId(T neighbor);

    public int degree(int u) {
        return neighbors(u).size();
    }

    public Tree asTree(int root) {
        return new Tree(this, root);
    }

    @Override
    public String toString() {
        String adj = IntStream.range(0, n)
                .mapToObj(i -> "    " + i + ": " + neighbors(i))
                .collect(Collectors.joining(",\n"));
        return "Graph {\n"
                + "  nodeCount: " + n + ",\n"
                + "  adjacencyList: {\n"
                + adj + "\n"
                + "  }\n"
                + "}";
    }

    public static class UnweightedGraph extends Graph<Integer> {

        UnweightedGraph(int n) {
            super(n);
        }

        public void addEdge(int u, int v) {
            adjacencyList.get(u).add(v);
        }

        public void addBidirectedEdges(int u, int v) {
            addEdge(u, v);
            addEdge(v, u);
        }


        @Override
        public int neighborId(Integer neighbor) {
            return neighbor;
        }

    }

    public static class WeightedGraph<T> extends Graph<Edge<T>> {

        WeightedGraph(int n) {
            super(n);
        }

        public void addEdge(int u, int v, T w) {
            adjacencyList.get(u).add(Edge.of(v, w));
        }

        public void addBidirectedEdges(int u, int v, T w) {
            addEdge(u, v, w);
            addEdge(v, u, w);
        }

        @Override
        public int neighborId(Edge<T> neighbor) {
            return neighbor.v;
        }

    }

    public static class Edge<T> {

        public final int v;
        public final T w;

        public Edge(int v, T w) {
            this.v = v;
            this.w = w;
        }

        public static <T> Edge<T> of(int v, T w) {
            return new Edge<>(v, w);
        }

        public int getV() {
            return v;
        }

        public T getW() {
            return w;
        }

        @Override
        public String toString() {
            return String.format("(%s, %s)", v, w);
        }

    }

}

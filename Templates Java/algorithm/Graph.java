package algorithm;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Graph<T> {

    public final int nodes;
    private final List<List<Edge<T>>> adjacencyList;
    private final T defaultWeight;

    Graph(int nodes, T defaultWeight) {
        this.nodes = nodes;
        this.adjacencyList = new ArrayList<>(nodes);
        this.defaultWeight = defaultWeight;

        for (var i = 0; i < nodes; i++) {
            this.adjacencyList.add(new ArrayList<>());
        }
    }

    public static Graph<Integer> ofInt(int nodes) {
        return new Graph<Integer>(nodes, 1);
    }

    public static Graph<Double> ofDouble(int nodes) {
        return new Graph<Double>(nodes, 1.0);
    }

    public void addEdge(int u, int v) {
        addEdge(u, v, defaultWeight);
    }

    public void addEdge(int u, int v, T weight) {
        adjacencyList.get(u).add(Edge.of(v, weight));
    }

    public void addBidirectedEdges(int u, int v) {
        addBidirectedEdges(u, v, defaultWeight);
    }

    public void addBidirectedEdges(int u, int v, T weight) {
        addEdge(u, v, weight);
        addEdge(v, u, weight);
    }

    public List<Edge<T>> neighbors(int u) {
        return adjacencyList.get(u);
    }

    @Override
    public String toString() {
        String adj = IntStream.range(0, nodes)
                .mapToObj(i -> "    " + i + ": " + adjacencyList.get(i))
                .collect(Collectors.joining(",\n"));
        return "Graph {\n"
                + "  nodes: " + nodes + ",\n"
                + "  adjacencyList: {\n"
                + adj + "\n"
                + "  }\n"
                + "}";
    }

    public static class Edge<T> {

        public final int neighbor;
        public final T weight;

        Edge(int neighbor, T weight) {
            this.neighbor = neighbor;
            this.weight = weight;
        }

        public static <T> Edge<T> of(int neighbor, T weight) {
            return new Edge<>(neighbor, weight);
        }

        public int getNeighbor() {
            return neighbor;
        }

        public T getWeight() {
            return weight;
        }

        @Override
        public String toString() {
            return String.format("(%s, %s)", neighbor, weight);
        }

    }

}

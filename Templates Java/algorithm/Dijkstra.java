package algorithm;

import algorithm.ArrayUtils;
import algorithm.Graph;
import algorithm.IntPair;

import java.util.Comparator;
import java.util.PriorityQueue;

public class Dijkstra {

    private final Graph.WeightedGraph<Integer> graph;

    public Dijkstra(Graph.WeightedGraph<Integer> graph) {
        this.graph = graph;
    }

    public int[] startFrom(int start) {
        var dist = ArrayUtils.of(graph.n, -1);
        dist[start] = 0;

        PriorityQueue<IntPair> queue = new PriorityQueue<>(Comparator.comparing(IntPair::getB));
        queue.add(IntPair.of(start, 0));

        while (!queue.isEmpty()) {
            var pair = queue.poll();
            var u = pair.a;

            if (pair.b > dist[u]) {
                continue;
            }

            for (var edge : graph.neighbors(u)) {
                var v = edge.v;
                var d = edge.w + dist[u];
                if (dist[v] == -1 || d < dist[v]) {
                    dist[v] = d;
                    queue.add(IntPair.of(v, d));
                }
            }
        }

        return dist;
    }

}

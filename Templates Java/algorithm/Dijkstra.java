package algorithm;

import algorithm.Graph;
import algorithm.IntPair;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

public class Dijkstra {

    private final Graph<Integer> graph;

    public Dijkstra(Graph<Integer> graph) {
        this.graph = graph;
    }

    public int[] startFrom(int start) {
        var dist = new int[graph.nodes];
        Arrays.fill(dist, -1);
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
                var v = edge.neighbor;
                var d = edge.weight + dist[u];
                if (dist[v] == -1 || d < dist[v]) {
                    dist[v] = d;
                    queue.add(IntPair.of(v, d));
                }
            }
        }

        return dist;
    }

}

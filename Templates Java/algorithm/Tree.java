package algorithm;

import algorithm.Graph;

import java.util.ArrayList;
import java.util.List;
import java.util.function.IntConsumer;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Tree {

    public final Graph<Object> graph;
    public final int n;
    public final int root;
    public int[] parents;

    public int[] depths;
    public int[] subTreeSizes;

    public int[] preOrderIds;
    private int currentPreOrderId;

    public int[] firstSeenInEulerTour;
    public List<Integer> eulerTour;

    @SuppressWarnings("unchecked")
    public Tree(Graph<?> graph, int root) {
        this.graph = (Graph<Object>) graph;
        this.n = graph.n;
        this.root = root;
        this.parents = new int[n];
    }

    public Tree saveDepth() {
        this.depths = new int[n];
        return this;
    }

    public Tree saveSubTreeSize() {
        this.subTreeSizes = new int[n];
        return this;
    }

    public Tree savePreOrderIds() {
        this.preOrderIds = new int[n];
        return this;
    }

    public Tree saveEulerTour() {
        this.firstSeenInEulerTour = new int[n];
        this.eulerTour = new ArrayList<>(n * 2 - 1);
        return this;
    }

    public Tree build() {
        dfs(root, -1, 0);
        return this;
    }

    private void dfs(int u, int parent, int depth) {
        parents[u] = parent;

        if (preOrderIds != null) {
            preOrderIds[u] = currentPreOrderId++;
        }

        if (eulerTour != null) {
            firstSeenInEulerTour[u] = eulerTour.size();
            eulerTour.add(u);
        }

        forEachChild(u, v -> {
            dfs(v, u, depth + 1);

            if (eulerTour != null) {
                eulerTour.add(u);
            }
        });

        if (depths != null) {
            depths[u] = depth;
        }

        if (subTreeSizes != null) {
            subTreeSizes[u] = 1;
            forEachChild(u, v -> subTreeSizes[u] += subTreeSizes[v]);
        }
    }

    public void forEachChild(int u, IntConsumer consumer) {
        for (var neighbor : graph.neighbors(u)) {
            var v = graph.neighborId(neighbor);
            if (v != parents[u]) {
                consumer.accept(v);
            }
        }
    }

    public boolean isLeaf(int u) {
        return u == root ? false : graph.neighbors(u).size() == 1;
    }

    @Override
    public String toString() {
        String nodes = IntStream.range(0, n)
                .mapToObj(u -> {

                    List<String> parts = new ArrayList<>();
                    parts.add("parent: " + parents[u]);

                    if (depths != null) {
                        parts.add("depth: " + depths[u]);
                    }

                    if (subTreeSizes != null) {
                        parts.add("subTreeSize: " + subTreeSizes[u]);
                    }

                    if (preOrderIds != null) {
                        parts.add("preOrderId: " + preOrderIds[u]);
                    }

                    if (firstSeenInEulerTour != null) {
                        parts.add("firstSeenInEulerTour: " + firstSeenInEulerTour[u]);
                    }

                    List<Integer> children = new ArrayList<>();
                    forEachChild(u, children::add);
                    parts.add("children: " + children);

                    String node = String.join(",\t", parts);
                    return "    " + u + ": { " + node + " }";
                })
                .collect(Collectors.joining(",\n"));

        return "Tree {\n"
                + "  nodeCount: " + n + ",\n"
                + "  nodes: {\n"
                + nodes + "\n"
                + "  },\n"
                + "  eulerTour: " + eulerTour + "\n"
                + "}";
    }

}

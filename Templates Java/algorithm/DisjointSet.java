package algorithm;

import java.util.Arrays;

public class DisjointSet {

    private final int[] parent;

    public DisjointSet(int n) {
        this.parent = new int[n];

        Arrays.fill(parent, -1);
    }

    public void union(int u, int v) {
        var x = find(u);
        var y = find(v);
        if (x != y) {
            parent[x] += parent[y];
            parent[y] = x;
        }
    }

    public int find(int u) {
        var root = u;
        while (parent[root] >= 0) {
            root = parent[root];
        }

        while (parent[u] >= 0) {
            var p = parent[u];
            parent[u] = root;
            u = p;
        }

        return root;
    }

    public int size(int u) {
        return -parent[find(u)];
    }

}

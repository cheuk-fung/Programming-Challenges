package algorithm;

import algorithm.Tree;
import algorithm.RMQ;

import java.util.Comparator;

public class LCA {

    private final Tree tree;
    private final RMQ<Integer> rmq;

    public LCA(Tree tree) {
        this.tree = tree.savePreOrderIds().saveEulerTour().build();
        this.rmq = new RMQ<>(tree.eulerTour, Comparator.comparing(u -> tree.preOrderIds[u]));
    }

    public int query(int x, int y) {
        var l = tree.firstSeenInEulerTour[x];
        var r = tree.firstSeenInEulerTour[y];
        if (l > r) {
            var t = l;
            l = r;
            r = t;
        }

        return rmq.query(l, r + 1);
    }

}

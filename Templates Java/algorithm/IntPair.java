package algorithm;

import algorithm.Pair;

public class IntPair extends Pair<Integer, Integer> {

    public IntPair(Integer a, Integer b) {
        super(a, b);
    }

    public static IntPair of(int a, int b) {
        return new IntPair(a, b);
    }

}

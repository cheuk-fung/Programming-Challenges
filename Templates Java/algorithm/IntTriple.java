package algorithm;

import algorithm.Triple;

public class IntTriple extends Triple<Integer, Integer, Integer> {

    IntTriple(Integer a, Integer b, Integer c) {
        super(a, b, c);
    }

    public static IntTriple of(int a, int b, int c) {
        return new IntTriple(a, b, c);
    }

}

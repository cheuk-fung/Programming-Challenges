package algorithm;

public class Triple<T, U, V> {

    public T a;
    public U b;
    public V c;

    public Triple(T a, U b, V c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public static <T, U, V> Triple<T, U, V> of(T a, U b, V c) {
        return new Triple<>(a, b, c);
    }

    public T getA() {
        return a;
    }

    public U getB() {
        return b;
    }

    public V getC() {
        return c;
    }

    @Override
    public String toString() {
        return "Triple(a=" + this.getA() + ", b=" + this.getB() + ", c=" + this.getC() + ")";
    }

}

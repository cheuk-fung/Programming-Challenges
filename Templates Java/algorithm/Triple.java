package algorithm;

import java.util.Objects;

public class Triple<T, U, V> {

    public T a;
    public U b;
    public V c;

    Triple(T a, U b, V c) {
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
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (!(obj instanceof Triple)) return false;

        var other = (Triple<?, ?, ?>) obj;
        return Objects.equals(a, other.a) && Objects.equals(b, other.b) && Objects.equals(c, other.c);
    }

    @Override
    public int hashCode() {
        final var PRIME = 59;
        var result = 1;
        result = result * PRIME + (a == null ? 43 : a.hashCode());
        result = result * PRIME + (b == null ? 43 : b.hashCode());
        result = result * PRIME + (c == null ? 43 : c.hashCode());
        return result;
    }

    @Override
    public String toString() {
        return String.format("(%s, %s, %s)", a, b, c);
    }

}

package algorithm;

import java.util.Objects;

public class Pair<T, U> {

    public T a;
    public U b;

    Pair(T a, U b) {
        this.a = a;
        this.b = b;
    }

    public static <T, U> Pair<T, U> of(T a, U b) {
        return new Pair<>(a, b);
    }

    public T getA() {
        return a;
    }

    public U getB() {
        return b;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (!(obj instanceof Pair)) return false;

        var other = (Pair<?, ?>) obj;
        return Objects.equals(a, other.a) && Objects.equals(b, other.b);
    }

    @Override
    public int hashCode() {
        final var PRIME = 59;
        var result = 1;
        result = result * PRIME + (a == null ? 43 : a.hashCode());
        result = result * PRIME + (b == null ? 43 : b.hashCode());
        return result;
    }

    @Override
    public String toString() {
        return String.format("(%s, %s)", a, b);
    }

}

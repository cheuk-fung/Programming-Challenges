package algorithm;

public class StringUtils {

    public static String reverse(String s) {
        return new StringBuilder().append(s).reverse().toString();
    }

    public static String reverseBinary(int i) {
        return reverse(Integer.toBinaryString(i));
    }

    public static String reverseBinary(long i) {
        return reverse(Long.toBinaryString(i));
    }

}

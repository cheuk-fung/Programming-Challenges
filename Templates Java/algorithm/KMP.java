package algorithm;

public class KMP {

    private final char[] pattern;
    private final int[] fallbacks;

    private KMP(char[] pattern, int[] fallbacks) {
        this.pattern = pattern;
        this.fallbacks = fallbacks;
    }

    public static KMP build(String pattern) {
        var s = pattern.toCharArray();
        var fallbacks = new int[s.length];

        fallbacks[0] = -1;
        for (int i = 1, j = -1; i < s.length; i++) {
            while (j >= 0 && s[j + 1] != s[i]) {
                j = fallbacks[j];
            }
            if (s[j + 1] == s[i]) {
                j++;
            }
            fallbacks[i] = j;
        }

        return new KMP(s, fallbacks);
    }

    public int match(String text) {
        var s = text.toCharArray();
        var count = 0;

        for (int i = 0, j = -1; i < s.length; i++) {
            while (j >= 0 && pattern[j + 1] != s[i]) {
                j = fallbacks[j];
            }
            if (pattern[j + 1] == s[i]) {
                j++;
            }
            if (j + 1 == pattern.length) {
                count++;
                j = fallbacks[j];
            }
        }

        return count;
    }

    public int fallback(int i) {
        return fallbacks[i];
    }

}

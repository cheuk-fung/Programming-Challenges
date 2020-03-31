package algorithm;

import java.util.Arrays;

public class Prime {

    public static int[] generate(int max) {
        var isPrime = new boolean[max + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;

        var count = 0;
        var prime = new int[max + 1];
        for (var i = 2; i <= max; i++) {
            if (isPrime[i]) {
                prime[count++] = i;
            }

            for (var j = 0; j < count && i * prime[j] <= max; j++) {
                isPrime[i * prime[j]] = false;
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }

        return Arrays.copyOf(prime, count);
    }

}

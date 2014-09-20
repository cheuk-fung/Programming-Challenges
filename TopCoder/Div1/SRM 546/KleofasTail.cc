class KleofasTail {
    private:
        int countbit(long long x)
        {
            int cnt = 0;
            while (x) {
                cnt++;
                x >>= 1;
            }
            return cnt;
        }

        long long count(long long l, long long r)
        {
            if (l == r) return 0;

            long long res = 0;
            int bit = countbit(r - 1) - countbit(l);
            for (int i = 0; i < bit; i++) {
                res += 1ll << i;
            }
            if ((r - 1) >> bit > l) {
                res += (1ll << bit);
            } else if ((r - 1) >> bit == l) {
                res += r - (l << bit);
            }
            return res;
        }

    public:
        long long countGoodSequences(long long K, long long A, long long B)
        {
            if (K == 0) return B - A + 1;
            if (K > B) return 0;
            long long res = count(K, B + 1) + (K & 1 ? 0 : count(K + 1, B + 1));
            if (K < A) res -= count(K, A) + (K & 1 ? 0 : count(K + 1, A));
            return res;
        }
};


/*
 *  SRC: NKOJ
 * TASK: Harder than usual
 * ALGO: Heap Sort
 * DATE: 03/30/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<algorithm>

inline bool greater(long a, long b)
{
    return a > b;
}

int main()
{
    long N, K;
    scanf("%ld%ld", &N, &K);
    long A[K];
    for (long i = 0; i < K; i++) scanf("%ld", &A[i]);

    std::make_heap(A, A + K, greater);

    for (long i = K; i < N; i++) {
        long t;
        scanf("%ld", &t);
        if (t > A[0]) {
            std::pop_heap(A, A + K, greater);
            A[K - 1] = t;
            std::push_heap(A, A + K, greater);
        }
    }

    printf("%ld\n", A[0]);

    return 0;
}				/* ----------  end of function main  ---------- */


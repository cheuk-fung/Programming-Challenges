#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int MOD = 1000000007;

inline int getidx(char c)
{
    if (islower(c)) return c - 'a';
    return c - 'A' + 26;
}

class Matrix {
    public:
        int M[52][52];
        int n; // n * n

        Matrix &operator*=(Matrix &);
} F, T, R;

Matrix &Matrix::operator*=(Matrix &O)
{
    memset(R.M, 0, sizeof M);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                R.M[i][j] = (R.M[i][j] + (long long)M[i][k] * O.M[k][j]) % MOD;
            }
        }
    }
    memmove(M, R.M, sizeof M);
    return *this;
}

char strbuf[5];

int main()
{
    long long n;
    int m, k;
    cin >> n >> m >> k;
    if (n == 1) {
        cout << m << endl;
        return 0;
    }

    T.n = m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            T.M[i][j] = 1;
        }
    }
    for (int i = 0; i < k; i++) {
        cin >> strbuf;
        T.M[getidx(strbuf[0])][getidx(strbuf[1])] = 0;
    }
    F = T;
    n -= 2;
    while (n) {
        if (n & 1) F *= T;
        T *= T;
        n >>= 1;
    }

    int ans = 0;
    for (int i = 0; i < F.n; i++) {
        for (int j = 0; j < F.n; j++) {
            ans = (ans + F.M[i][j]) % MOD;
        }
    }
    cout << ans << endl;

    return 0;
}

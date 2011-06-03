/*
 *  SRC: POJ
 * TASK: Exponentiation
 * ALGO: BigInteger
 * DATE: 05/10/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>

class BigNum
{
    private:
        /* ====================  DATA MEMBERS  ======================================= */
        static int maxSize;
        static int bound;
        int size;
        int* num;

    public:

        /* ====================  LIFECYCLE     ======================================= */
        BigNum(int = 0);                       /* constructor */
        BigNum(const BigNum&);                 /* copy constructor */

        /* ====================  ACCESSORS     ======================================= */
        void print(int) const;

        /* ====================  MUTATORS      ======================================= */
        void upgrade(int);

        /* ====================  OPERATORS     ======================================= */
        friend BigNum operator*(const BigNum&, const BigNum&);
}; /* -----  end of class BigNum  ----- */

BigNum::BigNum(int n) : size(0)
{
    num = new int[maxSize];
    for (int i = 0; i < maxSize; i++) num[i] = 0;
    while (n) {
        num[size++] = n % bound;
        n /= bound;
    }
    while (num[size]) size++;
}  /* -----  end of method BigNum::BigNum  (constructor)  ----- */

BigNum::BigNum(const BigNum& other) : size(other.size)
{
    num = new int[maxSize];
    for (int i = 0; i < other.size; i++) num[i] = other.num[i];
    for (int i = other.size; i < maxSize; i++) num[i] = 0;
}  /* -----  end of method BigNum::BigNum  (copy constructor)  ----- */

void BigNum::print(int dec) const
{
    if (size == 1 && num[0] == 0) putchar('0');
    else {
        if (dec > size) {
            putchar('.');
            for (int i = size; i < dec; i++) putchar('0');
        }
        int back = 0;
        while (num[back] == 0 && back < dec) back++;
        for (int i = size - 1; i >= back; i--) {
            if (i > 0 && i == dec - 1) putchar('.');
            printf("%d", num[i]);
        }
    }
    printf("\n");
}		/* -----  end of method BigNum::print  ----- */

inline void BigNum::upgrade(int p)
{
    while (num[p] >= bound) {
        num[p + 1] += num[p] / bound;
        num[p++] %= bound;
    }
}		/* -----  end of method BigNum::upgrade  ----- */

BigNum operator*(const BigNum& a, const BigNum& b)
{
    BigNum r;
    for (int i = 0; i < a.size; i++)
        for (int j = 0; j < b.size; j++)
            r.num[i + j] += a.num[i] * b.num[j];
    r.size = a.size + b.size;
    while (r.size  > 1 && r.num[r.size - 1] == 0) r.size--;
    for (int i = 0; i < r.size; i++) r.upgrade(i);
    while (r.num[r.size]) r.size++;

    return r;
}		/* -----  end of function operator*  ----- */

int BigNum::maxSize = 2000;
int BigNum::bound = 10;

int main()
{
    char s[10];
    int n;
    while (scanf("%s%d", &s, &n) != EOF) {
        int r = 0, pos = strlen(s) - 1, len = strlen(s);
        for (int i = 0; i < len; i++) {
            if (s[i] != '.') r = r * 10 + s[i] - '0';
            else pos = i;
        }        

        BigNum R(r), res(1);
        for (int i = 0; i < n; i++) res = res * R;

        res.print((len - 1 - pos) * n);
    }

    return 0;
}


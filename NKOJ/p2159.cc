/*
 *  SRC: NKOJ
 * TASK: Get your chance 
 * ALGO: Math
 * DATE: 03/29/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>

namespace BNum {
    template<typename T> inline T min(T a, T b)
    {
        return a < b ? a : b;
    } /* -----  end of template function min  ----- */


    template<typename T> inline T max(T a, T b)
    {
        return a > b ? a : b;
    } /* -----  end of template function max  ----- */

    class BigNum {
        private:
            static long maxSize;
            static long bound;
            static BigNum zero;
            long size;
            int sign; // 1 for non-negative and -1 for negative
            long* num;

        public:
            BigNum(long long = 0);
            /* BigNum(const char*); */
            BigNum(const BigNum&);

            BigNum& operator=(long long);
            /* BigNum& operator=(const char*); */
            BigNum& operator=(const BigNum&);

            ~BigNum() { if (num) delete[] num; }

            static void setMax(long, long);

            void upgrade(long);
            void downgrade(long);
            void print() const;
            void swap(BigNum&, BigNum&);

            friend int compare(const BigNum&, const BigNum&);
            // Return 1 for a > b, 0 for a == b and -1 for a < b.
            friend bool operator==(const BigNum&, const BigNum&);
            /*
             * friend bool operator!=(const BigNum&, const BigNum&);
             * friend bool operator>=(const BigNum&, const BigNum&);
             * friend bool operator<=(const BigNum&, const BigNum&);
             * friend bool operator>(const BigNum&, const BigNum&);
             * friend bool operator<(const BigNum&, const BigNum&);
             */

            BigNum& operator+=(long);
            BigNum& operator+=(const BigNum&);
            BigNum& operator-=(long); // only for  a - b when a >= b
            BigNum& operator-=(const BigNum&);
            BigNum& operator*=(long);
            BigNum& operator*=(const BigNum&);
            BigNum& operator/=(long);
            BigNum& operator/=(const BigNum&);

            /*
             * friend BigNum operator+(const BigNum&, long);
             * friend BigNum operator+(long, const BigNum&);
             * friend BigNum operator+(const BigNum&, const BigNum&);
             * friend BigNum operator-(const BigNum&, long);
             * friend BigNum operator-(const BigNum&, const BigNum&);
             * friend BigNum operator*(const BigNum&, long);
             * friend BigNum operator*(long, const BigNum&);
             */
            friend BigNum operator*(const BigNum&, const BigNum&);
            /* friend BigNum operator/(const BigNum&, long); */
            friend BigNum operator/(BigNum, BigNum);
    };

    BigNum::BigNum(long long n) : size(0)
    {
        if (n < 0) {
            sign = -1;
            n = -n;
        }
        else sign = 1;
        num = new long[maxSize];
        for (long i = 0; i < maxSize; i++) num[i] = 0;
        while (n) {
            num[size++] = n % bound;
            n /= bound;
        }
        if (size == 0) size++;
    }		/* -----  end of function BigNum::BigNum  ----- */

    BigNum::BigNum(const BigNum& m) : size(m.size), sign(m.sign)
    {
        num = new long[maxSize];
        for (long i = 0; i < m.size; i++) num[i] = m.num[i];
        for (long i = m.size; i < maxSize; i++) num[i] = 0;
    }		/* -----  end of function BigNum::BigNum  ----- */

    BigNum& BigNum::operator=(long long n)
    {
        for (long i = 0; i < size; i++) num[i] = 0;
        if (n < 0) {
            sign = -1;
            n = -n;
        }
        else sign = 1;
        size = 0;
        while (n) {
            num[size++] = n % bound;
            n /= bound;
        }
        if (size == 0) size++;

        return *this;
    }		/* -----  end of function BigNum::operator=  ----- */

    BigNum& BigNum::operator=(const BigNum& m)
    {
        for (long i = 0; i < m.size; i++) num[i] = m.num[i];
        for (long i = m.size; i < size; i++) num[i] = 0;
        sign = m.sign;
        size = m.size;

        return *this;
    }		/* -----  end of function BigNum::operator=  ----- */

    inline void BigNum::setMax(long t_maxSize, long t_bound)
    {
        maxSize = t_maxSize;
        bound = t_bound;
    }		/* -----  end of function BigNum::setMax----- */

    inline void BigNum::upgrade(long p)
    {
        while (num[p] >= bound) {
            num[p + 1] += num[p] / bound;
            num[p++] %= bound;
        }
    }		/* -----  end of function BigNum::upgrade  ----- */

    inline void BigNum::downgrade(long p)
    {
        while (num[p] < 0) {
            num[p + 1] += num[p] / bound - 1;
            num[p] %= bound;
            num[p++] += bound;
        }
    }		/* -----  end of function BigNum::downgrade  ----- */

    void BigNum::print() const 
    {
        if (sign == -1) printf("-");
        printf("%ld", num[size - 1]);
        for (long i = size - 2; i >= 0; i--) {
            long t = bound / 10;
            while (num[i] < t) {
                printf("0");
                t /= 10;
            }
            printf("%ld", num[i]);
        }
        printf("\n");
    }		/* -----  end of function BigNum::print  ----- */

    inline void BigNum::swap(BigNum& a, BigNum& b)
    {
        long t_size = a.size;
        a.size = b.size;
        b.size = t_size;

        int t_sign = a.sign;
        a.sign = b.sign;
        b.sign = t_sign;

        long* t_num = a.num;
        a.num = b.num;
        b.num = t_num;
    }		/* -----  end of function BigNum::swap  ----- */

    int compare(const BigNum& a, const BigNum& b)
    {
//        if (a.sign == 1 && b.sign == -1) return 1;
//        if (a.sign == -1 && b.sign == 1) return -1;
        if (a.sign != b.sign) return a.sign - b.sign;
        int res;
        if (a.sign == 1) res = 1;
        else res = -1;
        if (a.size > b.size) return res;
        if (a.size < b.size) return -res;
        for (long i = a.size - 1; i >= 0; i--) {
            if (a.num[i] > b.num[i]) return res;
            if (a.num[i] < b.num[i]) return -res;
        }
        return 0;
    }		/* -----  end of function compare  ----- */

    bool operator==(const BigNum& a, const BigNum& b)
    {
        if (a.sign != b.sign || a.size != b.size) return false;
        for (long i = a.size - 1; i >= 0; i--)
            if (a.num[i] != b.num[i]) return false;
        return true;
    }		/* -----  end of function operator==  ----- */

    bool operator!=(const BigNum& a, const BigNum& b)
    {
        return !(a == b);
    }		/* -----  end of function operator!=  ----- */

    bool operator>=(const BigNum& a, const BigNum& b)
    {
        if (compare(a, b) >= 0) return true;
        else return false;
    }		/* -----  end of function operator>=  ----- */

    bool operator>(const BigNum& a, const BigNum& b)
    {
        if (compare(a, b) > 0) return true;
        else return false;
    }		/* -----  end of function operator>  ----- */

    bool operator<=(const BigNum& a, const BigNum& b)
    {
        if (compare(a, b) <= 0) return true;
        else return false;
    }		/* -----  end of function operator<=  ----- */

    bool operator<(const BigNum& a, const BigNum& b)
    {
        if (compare(a, b) < 0) return true;
        else return false;
    }		/* -----  end of function operator<  ----- */

    BigNum& BigNum::operator+=(long m)
    {
        if (sign == 1 && m < 0) {
            operator-=(-m);
            return *this;
        }

        if (sign == -1 && m >= 0) {
            sign = -sign;
            operator-=(m);
            if (*this != zero) sign = -sign;

            return *this;
        }

        if (m < 0) m = -m;
        if (m > bound) { // you may change "bound" here to fit your problem
            operator+=(BigNum(m));
            return *this;
        }
        num[0] += m;
        upgrade(0);
        while (num[size]) size++;

        return *this;
    }		/* -----  end of function BigNum::operator+=  ----- */

    BigNum& BigNum::operator+=(const BigNum& m)
    {
        if (sign == 1 && m.sign == -1) {
            BigNum t = m;
            t.sign = 1;
            operator-=(t);

            return *this;
        }

        if (sign == -1 && m.sign == 1 ) {
            sign = -sign;
            operator-=(m);
            if (*this != zero) sign = -sign;

            return *this;
        }

        size = max(size, m.size);
        for (long i = 0; i < size; i++) num[i] += m.num[i];
        for (long i = 0; i < size; i++) upgrade(i);
        while (num[size]) size++;

        return *this;
    }		/* -----  end of function BigNum::operator+=  ----- */

    BigNum operator+(const BigNum& a, long b)
    {
        BigNum r = a;
        return r += b;
    }		/* -----  end of function operator+  ----- */

    BigNum operator+(long a, const BigNum& b)
    {
        BigNum r = b;
        return r += a;
    }		/* -----  end of function operator+  ----- */

    BigNum operator+(const BigNum& a, const BigNum& b)
    {
        BigNum r = a;
        return r += b;
    }		/* -----  end of function operator+  ----- */

    BigNum& BigNum::operator-=(long m)
    {
        if (sign == 1 && m < 0) {
            operator+=(-m);
            return *this;
        }

        if (sign == -1 && m >= 0) {
            sign = -sign;
            operator+=(m);
            if (*this != zero) sign = -sign;

            return *this;
        }

        if (m < 0) m = -m;
        int t_sign = sign;
        sign = 1;
        int cmp = compare(*this, m);
        if (cmp == 0) {
            *this = zero;
            return *this;
        }
        if (cmp > 0) {
            num[0] -= m;
            downgrade(0);
            while (size > 1 && !num[size - 1]) size--;
            sign = t_sign;

            return *this;
        }
        BigNum t = BigNum(m);
        t -= *this;
        *this = t;
        sign = -t_sign;

        return *this;
    }		/* -----  end of function BigNum::operator-=  ----- */

    BigNum& BigNum::operator-=(const BigNum& m)
    {
        if (sign == 1 && m.sign == -1) {
            BigNum t = m;
            t.sign = 1;
            operator+=(t);

            return *this;
        }
        
        if (sign == -1 && m.sign == 1) {
            sign = -sign;
            operator+=(m);
            if (*this != zero) sign = -sign;

            return *this;
        }

        BigNum t = m;
        t.sign = 1;
        int tmp_sign = sign;
        sign = 1;
        int cmp = compare(*this, t);
        if (cmp == 0) {
            *this = zero;
            return *this;
        }
        if (cmp > 0) sign = tmp_sign;
        else {
            swap(*this, t);
            sign = -tmp_sign;
        }
        for (long i = 0; i < t.size; i++) num[i] -= t.num[i];
        for (long i = 0; i < t.size; i++) downgrade(i);
        while (size > 1 && !num[size - 1]) size--;

        return *this;
    }		/* -----  end of function BigNum::operator-=  ----- */

    BigNum operator-(const BigNum& a, long b)
    {
        BigNum r = a;
        return r -= b;
    }		/* -----  end of function operator-  ----- */

    BigNum operator-(const BigNum& a, const BigNum& b)
    {
        BigNum r = a;
        return r -= b;
    }		/* -----  end of function operator-  ----- */

    BigNum& BigNum::operator*=(long m)
    {
        if (*this == zero) return *this;
        if (m == 0) {
            *this = zero;
            return *this;
        }
        if (m >= bound || -m >= bound) {
            operator*=(BigNum(m));
            return *this;
        }
        
        long t_m = m;
        if (m < 0) m = -m;
        for (long i = 0; i < size; i++) num[i] *= m;
        for (long i = 0; i < size; i++) upgrade(i);
        while (num[size]) size++;

        if (t_m < 0) sign = -sign;

        return *this;
    }		/* -----  end of function BigNum::operator*=  ----- */

    BigNum& BigNum::operator*=(const BigNum& m)
    {
        *this = *this * m;
        return *this;
    }		/* -----  end of function BigNum::operator*=  ----- */

    BigNum operator*(const BigNum& a, long b)
    {
        BigNum r = a;
        return r *= b;
    }		/* -----  end of function operator*  ----- */

    BigNum operator*(long a, const BigNum& b)
    {
        BigNum r = b;
        return r *= a;
    }		/* -----  end of function operator*  ----- */

    BigNum operator*(const BigNum& a, const BigNum& b)
    {
        if (a == BigNum::zero || b == BigNum::zero) {
            return BigNum::zero;
        }
        BigNum r = 0;
        for (long i = 0; i < a.size; i++)
            for (long j = 0; j < b.size; j++)
                r.num[i + j] += a.num[i] * b.num[j];
        r.size = a.size + b.size;
        while (r.size  > 1 && r.num[r.size] == 0) r.size--;
        for (long i = 0; i < r.size; i++) r.upgrade(i);
        while (r.num[r.size]) r.size++;

        if (b.sign == -1) r.sign = -a.sign;
        else r.sign = a.sign;

        return r;
    }		/* -----  end of function operator*  ----- */

    BigNum& BigNum::operator/=(long m)
    {
        long t_m = m;
        if (m < 0) m = -m;

        long long rest = 0;
        for (long i = size - 1; i >= 0; i--) {
            rest = rest * bound + num[i];
            num[i] = rest / m;
            rest %= m;
        }
        while (size > 1 && !num[size - 1]) size--;

        int t_sign = sign;
        sign = 1;
        if (*this == zero) return *this;

        if (t_m < 0) sign = -t_sign;
        else sign = t_sign;

        return *this;
    }		/* -----  end of function BigNum::operator/=  ----- */

    BigNum& BigNum::operator/=(const BigNum& m)
    {
        *this = *this / m;
        return *this;
    }		/* -----  end of function BigNum::operator/=  ----- */

    BigNum operator/(const BigNum& a, long b)
    {
        BigNum r = a;
        return r /= b;
    }		/* -----  end of function operator/  ----- */

    BigNum operator/(BigNum a, BigNum b)
    {
        int ta_sign = a.sign, tb_sign = b.sign;
        a.sign = b.sign = 1;

        BigNum low = 0, high = a, mid = 0, ans = 0;
        while (low < high) {
            mid = (low + high + 1) / 2;
            ans = b * mid;
            int cmp = compare(ans, a);
            if (cmp == 0) { // ans == a
                low = mid;
                break;
            }
            if (cmp == -1) low = mid; // ans < a
            else high = mid - 1;
        }

        if (low == BigNum::zero) return BigNum::zero;
        if (tb_sign == -1) low.sign = -ta_sign;
        else low.sign = ta_sign;

        return low;
    }		/* -----  end of function operator/  ----- */
}		/* -----  end of namespace BNum  ----- */

using namespace BNum;

long BigNum::maxSize = 10;
long BigNum::bound = 10000;
BigNum BigNum::zero = 0;

BigNum x[100000];
BigNum d;
BigNum da, da1, da2;
BigNum db, db1, db2;
BigNum qa, qb;

bool work()
{

    long n;
    if (scanf("%ld", &n) == -1) return false;
    for (long i = 0; i < n; i++) {
        long long t;
        scanf("%lld", &t);
        x[i] = t;
    }

    if (n == 1) {
        printf("YES\n");
        printf("0\n");
        return true;
    }

    if (n == 2) {
        printf("YES\n");
        if (x[0] == 0 && x[1] != 0) printf("1\n");
        else printf("0\n");
        return true;
    }

    // n == 3
    if (x[0] == x[1] && x[1] == x[2]) {
        d = da = db = 0;
    }
    else {
//        da = x[0] * x[2] - x[1] * x[1];
//        db = 2 * x[1] - (x[0] + x[2]);
        da1 = x[0] * x[2]; da2 = x[1] * x[1];
        db1 = 2 * x[1]; db2 = x[0] + x[2];
        int cmp = compare(da1, da2);
        if (cmp > 0) { // da > 0
            if (db1 <= db2) { // db <= 0
                printf("NO\n");
                printf("\n");
                return true;
            }
            else { // db > 0
                da = da1 - da2;
                db = db1 - db2;
            }
        }
        else if (cmp < 0) { // da < 0
            if (db1 >= db2) { // db >= 0
                printf("NO\n");
                printf("\n");
                return true;
            }
            else { // db < 0
                da = da2 - da1;
                db = db2 - db1;
            }
        }
        else { // da == 0
            da = 0;
            if (db1 >= db2) db = db1 - db2;
            else db = db2 - db1;
        }
        d = da / db;
        if (d * db != da) {
            printf("NO\n");
            printf("\n");
            return true;
        }
    }
    if (x[0] == x[1] && x[1] == x[2] && x[2] == 0) {
        qa = qb = 0;
    }
    else {
        qa = x[1] + d;
        qb = x[0] + d;
        if (qb == 0) {
            printf("NO\n");
            printf("\n");
            return true;
        }
    }
    for (long i = 3; i < n; i++) {
        if ((x[i - 1] + d) * qa != (x[i] + d) * qb) {
            printf("NO\n");
            printf("\n");
            return true;
        }
    }
    printf("YES\n");
    d.print();

    return true;
}				/* ----------  end of function work ---------- */

int main()
{
    while (1 + 1 == 2) {
        if (work() == false) break;
    }

    return 0;
}				/* ----------  end of function main  ---------- */


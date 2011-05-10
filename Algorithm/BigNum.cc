/*
 * =====================================================================================
 * 
 *       Filename:  BigNum.cc
 * 
 *    Description:  A class for calculating Big Numbers.
 *                  Only for (long) Integer.
 *
 *        Created:  03/29/2011 23:26:05
 *       Compiler:  g++
 * 
 *         Author:  Leewings Ac (Zhuofeng Wu), osideal {at} gmail.com
 * 
 * =====================================================================================
 */

/*
 * #include	<cstdio>
 */

namespace BNum {

    /*
     * =====================================================================================
     *        Class:  BigNum
     *  Description:  A class for calculating Big Numbers.
     *                Only for (long) Integer.
     * =====================================================================================
     */
    class BigNum
    {
        private:
            /* ====================  DATA MEMBERS  ======================================= */
            static long maxSize;
            static long bound;
            static BigNum zero;
            long size;
            mutable int sign; /* 1 for non-negative and -1 for negative */
            long* num;

        public:

            /* ====================  LIFECYCLE     ======================================= */
            BigNum(long long = 0);                 /* constructor */
            BigNum(const BigNum&);                 /* copy constructor */
            ~BigNum();                             /* destructor */

            /* ====================  ACCESSORS     ======================================= */
            int get_sign() const;
            void print() const;

            friend int compare(const BigNum&, const BigNum&);
            /* Return 1 for a > b, 0 for a == b and -1 for a < b. */
            friend void swap(BigNum&, BigNum&);

            /* ====================  MUTATORS      ======================================= */
            static void setMax(long, long);

            void upgrade(long);
            void downgrade(long);

            /* ====================  OPERATORS     ======================================= */

            BigNum& operator=(long long);     /* assignment operator */
            BigNum& operator=(const BigNum&); /* assignment operator */

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
            BigNum& operator-=(long);
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
            friend BigNum operator/(const BigNum&, const BigNum&);
    }; /* -----  end of class BigNum  ----- */

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
    }  /* -----  end of method BigNum::BigNum  (constructor)  ----- */

    BigNum::BigNum(const BigNum& other) : size(other.size), sign(other.sign)
    {
        num = new long[maxSize];
        for (long i = 0; i < other.size; i++) num[i] = other.num[i];
        for (long i = other.size; i < maxSize; i++) num[i] = 0;
    }  /* -----  end of method BigNum::BigNum  (copy constructor)  ----- */

    BigNum::~BigNum()
    {
        if (num) delete[] num;
    }  /* -----  end of method BigNum::~BigNum  (destructor)  ----- */

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
    }  /* -----  end of method BigNum::operator=  (assignment operator)  ----- */

    BigNum& BigNum::operator=(const BigNum& other)
    {
        if (this != &other) {
            for (long i = 0; i < other.size; i++) num[i] = other.num[i];
            for (long i = other.size; i < size; i++) num[i] = 0;
            sign = other.sign;
            size = other.size;
        }
        return *this;
    }  /* -----  end of method BigNum::operator=  (assignment operator)  ----- */

    inline void BigNum::setMax(long t_maxSize, long t_bound)
    {
        maxSize = t_maxSize;
        bound = t_bound;
    }		/* -----  end of method BigNum::setMax  ----- */

    inline int BigNum::get_sign() const
    {
        return sign;
    }		/* -----  end of method BigNum::get_sign  ----- */

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
            if (num[i]) printf("%ld", num[i]);
        }
        printf("\n");
    }		/* -----  end of method BigNum::print  ----- */

    inline void BigNum::upgrade(long p)
    {
        while (num[p] >= bound) {
            num[p + 1] += num[p] / bound;
            num[p++] %= bound;
        }
    }		/* -----  end of method BigNum::upgrade  ----- */

    inline void BigNum::downgrade(long p)
    {
        while (num[p] < 0) {
            long inc = num[p] / bound;
            if (inc * bound != num[p]) inc--;
            num[p + 1] += inc;
            num[p] %= bound;
            if (num[p] < 0) num[p] += bound;
            p++;
        }
    }		/* -----  end of method BigNum::downgrade  ----- */

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
        if (m > bound) { /* you may change "bound" here to fit your problem */
            operator+=(BigNum(m));
            return *this;
        }
        num[0] += m;
        upgrade(0);
        while (num[size]) size++;

        return *this;
    }		/* -----  end of method BigNum::operator+=  ----- */

    BigNum& BigNum::operator+=(const BigNum& m)
    {
        if (sign == 1 && m.sign == -1) {
            m.sign = -m.sign;
            operator-=(m);
            m.sign = -m.sign;

            return *this;
        }

        if (sign == -1 && m.sign == 1 ) {
            sign = -sign;
            operator-=(m);
            if (*this != zero) sign = -sign;

            return *this;
        }

        size = size > m.size ? size : m.size;
        for (long i = 0; i < size; i++) num[i] += m.num[i];
        for (long i = 0; i < size; i++) upgrade(i);
        while (num[size]) size++;

        return *this;
    }		/* -----  end of method BigNum::operator+=  ----- */

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
    }		/* -----  end of method BigNum::operator-=  ----- */

    BigNum& BigNum::operator-=(const BigNum& m)
    {
        if (sign == 1 && m.sign == -1) {
            m.sign = -m.sign;
            operator+=(m);
            m.sign = -m.sign;

            return *this;
        }
        
        if (sign == -1 && m.sign == 1) {
            sign = -sign;
            operator+=(m);
            if (*this != zero) sign = -sign;

            return *this;
        }

        int t_sign = sign, tm_sign = m.sign;
        sign = m.sign = 1;
        int cmp = compare(*this, m);
        if (cmp == 0) {
            *this = zero;
            m.sign = tm_sign;

            return *this;
        }
        if (cmp > 0) {
            sign = t_sign;
            for (long i = 0; i < m.size; i++) num[i] -= m.num[i];
        }
        else {
            sign = -t_sign;
            size = m.size;
            for (long i = 0; i < m.size; i++) num[i] = m.num[i] - num[i];
        }
        for (long i = 0; i < m.size; i++) downgrade(i);
        while (size > 1 && !num[size - 1]) size--;

        m.sign = tm_sign;

        return *this;
    }		/* -----  end of method BigNum::operator-=  ----- */

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
        
        if (m < 0) {
            sign = -sign;
            m = -m;
        }
        for (long i = 0; i < size; i++) num[i] *= m;
        for (long i = 0; i < size; i++) upgrade(i);
        while (num[size]) size++;

        return *this;
    }		/* -----  end of method BigNum::operator*=  ----- */

    BigNum& BigNum::operator*=(const BigNum& m)
    {
        *this = *this * m;
        return *this;
    }		/* -----  end of method BigNum::operator*=  ----- */

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
        while (r.size  > 1 && r.num[r.size - 1] == 0) r.size--;
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
    }		/* -----  end of method BigNum::operator/=  ----- */

    BigNum& BigNum::operator/=(const BigNum& m)
    {
        *this = *this / m;
        return *this;
    }		/* -----  end of method BigNum::operator/=  ----- */

    BigNum operator/(const BigNum& a, long b)
    {
        BigNum r = a;
        return r /= b;
    }		/* -----  end of function operator/  ----- */

    BigNum operator/(const BigNum& a, const BigNum& b)
    {
        int ta_sign = a.sign, tb_sign = b.sign;
        a.sign = b.sign = 1;

        BigNum low = 0, high = a, mid = 0, ans = 0;
        while (low < high) {
            mid = (low + high + 1) / 2;
            ans = b * mid;
            int cmp = compare(ans, a);
            if (cmp == 0) { /* ans == a */
                low = mid;
                break;
            }
            if (cmp == -1) low = mid; /* ans < a */
            else high = mid - 1;
        }

        a.sign = ta_sign;
        b.sign = tb_sign;

        if (low == BigNum::zero) return BigNum::zero;
        if (b.sign == -1) low.sign = -a.sign;
        else low.sign = a.sign;

        return low;
    }		/* -----  end of function operator/  ----- */

    int compare(const BigNum& a, const BigNum& b)
    {
        /*
         * if (a.sign == 1 && b.sign == -1) return 1;
         * if (a.sign == -1 && b.sign == 1) return -1;
         */
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

    inline void swap(BigNum& a, BigNum& b)
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
    }		/* -----  end of function swap  ----- */

    long BigNum::maxSize = 0;
    long BigNum::bound = 0;
    BigNum BigNum::zero = 0;

}		/* -----  end of namespace BNum  ----- */


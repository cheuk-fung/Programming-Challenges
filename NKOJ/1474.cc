/*
 *  SRC: NKOJ 1474
 * PROB: Modular multiplication of polynomials
 * ALGO: NULL
 * DATE: Aug 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

class Polynomial {
    private:
        short degree;
        short poly[2000];

    public:
        void read() {
            scanf("%hd", &degree);
            for (short i = --degree; i >= 0; i--)
                scanf("%hd", &poly[i]);
        }

        void write() const {
            printf("%hd ", degree + 1);
            for (short i = degree; i >= 0; i--)
                printf("%hd ", poly[i]);
            putchar(10);
        }

        Polynomial operator *(const Polynomial& other) const {
            Polynomial r;
            r.degree = degree + other.degree;
            memset(r.poly, 0, sizeof(short) * (r.degree + 1));
            for (short i = 0; i <= degree; i++) {
                if (!poly[i]) continue;
                for (short j = 0; j <= other.degree; j++) {
                    if (!other.poly[j]) continue;
                    r.poly[i + j] ^= 1;
                }
            }
            return r;
        }

        Polynomial& operator %=(const Polynomial& other) {
            while (degree >= other.degree) {
                short offset = degree - other.degree;
                for (short i = 0; i <= other.degree; i++)
                    poly[i + offset] ^= other.poly[i];
                while (degree && !poly[degree]) degree--;
            }
            return *this;
        }
};

Polynomial f, g, h;

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        f.read();
        g.read();
        h.read();
        ((f * g) %= h).write();
    }

    return 0;
}

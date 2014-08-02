/*
 *  SRC: POJ 3569
 * PROB: Equation
 * ALGO: Expression
 * DATE: Aug 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <stack>
#include <vector>

using std::pair;
using std::stack;
using std::vector;

typedef pair<long long, long long> pii; // first * x + second
vector<pii> check_zero;
typedef vector<pii>::const_iterator vci;


inline pii operator +(const pii& a, const pii& b)
{
    return pii(a.first + b.first, a.second + b.second);
}

inline pii operator *(const pii& a, const pii& b)
{
    pii res;
    res.first = a.first * b.second + b.first * a.second;
    res.second = a.second * b.second;
    return res;
}

struct Expression {
    pii up, down;

    Expression() { }
    Expression(const pii& _up, const pii& _down) : up(_up), down(_down) { }

    Expression operator -() const
    {
        return Expression(pii(-up.first, -up.second), down);
    }

    Expression operator +(const Expression& other) const
    {
        Expression res;
        res.up = up * other.down + other.up * down;
        res.down = down * other.down;
        return res;
    }

    Expression operator -(const Expression& other) const
    {
        return operator +(-other);
    }

    Expression operator *(const Expression& other) const
    {
        Expression res;
        res.up = up * other.up;
        res.down = down * other.down;
        return res;
    }

    Expression operator /(const Expression& other) const
    {
        return operator *(Expression(other.down, other.up));
    }
};

long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    char expr[1000];
    gets(expr);
    stack<Expression> S;
    for (int i = 0, len = strlen(expr); i < len; i += 2) {
        char c = expr[i];
        if (c == 'X') {
            S.push(Expression(pii(1, 0), pii(0, 1)));
            check_zero.push_back(S.top().down);
            continue;
        }
        if (isdigit(c)) {
            S.push(Expression(pii(0, c - '0'), pii(0, 1)));
            check_zero.push_back(S.top().down);
            continue;
        }

        Expression b = S.top(); S.pop();
        Expression a = S.top(); S.pop();

        switch(c) {
            case '+': S.push(a + b); check_zero.push_back(S.top().down); break;
            case '-': S.push(a - b); check_zero.push_back(S.top().down); break;
            case '*': S.push(a * b); check_zero.push_back(S.top().down); break;
            case '/': S.push(a / b); check_zero.push_back(S.top().down);
        }
    }

    pii x = S.top().up;
    if (x.first == 0) {
        if (x.second == 0) puts("MULTIPLE");
        else puts("NONE");
    }
    else {
        long long div = gcd(llabs(x.first), llabs(x.second));
        x.first /= div;
        x.second /= div;

        for (vci vi = check_zero.begin(); vi != check_zero.end(); vi++)
            if (vi->first * x.second == vi->second * x.first) {
                puts("NONE");
                return 0;
            }

        printf("X = %s%lld/%lld\n", 
                -x.first * x.second >= 0 ? "" : "-", \
                llabs(x.second), llabs(x.first));
    }

    return 0;
}

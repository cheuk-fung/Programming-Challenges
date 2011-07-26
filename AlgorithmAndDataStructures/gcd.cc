int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int extendedEuclid(int a, int b, int* x, int* y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;

        return a;
    }

    int r = extendedEuclid(b, a % b, x, y);
    int t = *x;
    *x = *y;
    *y = t - a / b * *y;

    return r;
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

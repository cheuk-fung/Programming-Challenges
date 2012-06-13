// we can use __gcd() in <algorithm>
int gcd(int a, int b)
{
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// ax + by = gcd(a, b)
int extended_euclid(int a, int b, int *x, int *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;

        return a;
    }

    int r = extended_euclid(b, a % b, x, y);
    int t = *x;
    *x = *y;
    *y = t - a / b * *y;

    return r;
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

// ver[] has been sorted by clockwise or counterclockwise
Point g_center(Point *ver, int n)
{
    Point res(0, 0);
    ver[n] = ver[0];

    double area = 0;
    for (int i = 1; i <= n; i++) {
        Point &a = ver[i - 1],
              &b = ver[i];
        double t = cross(a, b);
        area += t / 2.0;
        res.x += (a.x + b.x) * t;
        res.y += (a.y + b.y) * t;
    }
    res.x /= (6.0 * area);
    res.y /= (6.0 * area);

    return res;
}

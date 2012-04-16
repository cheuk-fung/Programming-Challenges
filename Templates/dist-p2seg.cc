inline double dist_p2seg(const Point &v, const Point &a, const Point &b)
{
    if (ls(dot(v - a, b - a), 0.0)) return dist(v, a);
    if (ls(dot(v - b, a - b), 0.0)) return dist(v, b);
    double area = fabs(cross(v - a, b - a));
    if (eq0(area)) return fmin(dist(v, a), dist(v, b));
    return area / dist(a, b);
}

inline double dist_p2seg(const Point &p, const Point &a, const Point &b)
{
    if (ls(dot(p - a, b - a), 0.0)) return dist(p, a);
    if (ls(dot(p - b, a - b), 0.0)) return dist(p, b);
    double area = fabs(cross(p - a, b - a));
    if (eq0(area)) return fmin(dist(p, a), dist(p, b));
    return area / dist(a, b);
}

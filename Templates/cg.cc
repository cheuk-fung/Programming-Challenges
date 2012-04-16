// Constants
const double eps = 1e-8;
const double pi = acos(-1.0f);
const double DINF = 1.0/0.0f;

// Functions
inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline bool greq(double x, double y) { return x + eps >= y; }
inline bool lseq(double x, double y) { return x - eps <= y; }
inline double fmax(double x, double y) { return gr(x, y) ? x : y; }
inline double fmin(double x, double y) { return ls(x, y) ? x : y; }

inline double dot(const Vec &u, const Vec &v) { return u.x * v.x + u.y * v.y; }
inline double cross(const Vec &u, const Vec &v) { return u.x * v.y - u.y * v.x; }

inline double dot(const Vec &u, const Vec &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
inline Vec cross(const Vec &u, const Vec &v)
{
    return Vec(u.y * v.z - u.z * v.y,
               u.z * v.x - u.x * v.z,
               u.x * v.y - u.y * v.x);
}

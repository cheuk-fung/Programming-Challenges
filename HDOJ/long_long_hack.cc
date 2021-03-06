// method 0
// usage: scanf(LLD" "LLD"\n", &a, &b);
//        printf(LLD" "LLD"\n", a, b);
#ifdef ONLINE_JUDGE
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

// method 1
// usage: myscanf("%lld %lld\n", a, b);
//        myprintf("%lld %lld\n", a, b);
#include <cstdarg>

inline void myscanf(string s, ...)
{
    va_list ap;
    va_start(ap, s);
#ifdef ONLINE_JUDGE
    int pos;
    while ((pos = s.find("lld")) != string::npos) {
        s.replace(pos, 3, "I64d");
    }
#endif
    vscanf(s.c_str(), ap);
}

inline void myprintf(string s, ...)
{
    va_list ap;
    va_start(ap, s);
#ifdef ONLINE_JUDGE
    int pos;
    while ((pos = s.find("lld")) != string::npos) {
        s.replace(pos, 3, "I64d");
    }
#endif
    vprintf(s.c_str(), ap);
}

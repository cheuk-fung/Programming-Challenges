#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int INF = 0x3f3f3f3f;
template<class T> inline int SIZE(const T &x) { return x.size(); }

int cnt[100010];

string s;
int ansl, ansr, anscnt;

void check(int l, int r)
{
    if (l >= r) return ;

    stack<int> S;
    for (int i = l; i <= r; i++) {
        if (s[i] == ')' || s[i] == ']') S.pop();
        else S.push(i);
    }
    if (S.empty()) {
        if (cnt[r + 1] - cnt[l] > anscnt) {
            ansl = l;
            ansr = r;
            anscnt = cnt[r + 1] - cnt[l];
        }
    } else {
        while (!S.empty()) {
            check(S.top() + 1, r);
            r = S.top() - 1;
            S.pop();
        }
        check(l, r);
    }
}

int main()
{
    while (cin >> s) {
        anscnt = 0;
        for (int i = 0; i < SIZE(s); i++) {
            cnt[i + 1] = cnt[i] + (s[i] == '[');
        }

        stack<int> S;
        int nowl = INF, nowr = INF;
        for (int i = 0; i < SIZE(s); i++) {
            if (s[i] == ')' || s[i] == ']') {
                if (S.empty() || (s[i] == ')' && s[S.top()] != '(') || (s[i] == ']' && s[S.top()] != '[')) {
                    if (nowl != INF && cnt[nowr + 1] - cnt[nowl] > anscnt) {
                        check(nowl, nowr);
                    }
                    nowl = nowr = INF;
                    while (!S.empty()) S.pop();
                } else {
                    nowl = min(nowl, S.top());
                    nowr = i;
                    S.pop();
                }
            } else {
                S.push(i);
            }
        }
        if (nowl != INF && cnt[nowr + 1] - cnt[nowl] > anscnt) {
            check(nowl, nowr);
        }

        cout << anscnt << endl;
        if (anscnt) {
            cout << s.substr(ansl, ansr - ansl + 1) << endl;
        } else {
            cout << endl;
        }
    }

    return 0;
}

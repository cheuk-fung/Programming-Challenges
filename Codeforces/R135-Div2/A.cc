#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int cnt[512];
char s[1010];

int main()
{
    int k;
    cin >> k >> s;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        cnt[s[i]]++;
    }

    string s;
    for (int i = 'a'; i <= 'z'; i++) {
        if (cnt[i] % k != 0) {
            puts("-1");
            return 0;
        }
        for (int j = 0; j < cnt[i] / k; j++) {
            s += (char)i;
        }
    }
    for (int i = 0; i < k; i++) cout << s;
    cout << endl;


    return 0;
}


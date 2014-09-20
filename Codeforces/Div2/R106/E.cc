#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

string s;
vector<int> prn, f(1010), g(1010);

template<class ForwardIterator>
void kmp_init(ForwardIterator first, ForwardIterator last)
{
    prn.clear();
    prn.push_back(0);
    ForwardIterator curr = first + 1;
    for (int j = 0; curr != last; curr++) {
        while (j > 0 && *(first + j) != *curr) j = prn[j - 1];
        if (*(first + j) == *curr) j++;
        prn.push_back(j);
    }
}

template<class ForwardIterator>
void kmp(ForwardIterator first_a, ForwardIterator last_a, \
         ForwardIterator first_b, ForwardIterator last_b, \
         vector<int> *pos)
{
    for (int i = 0; i < pos->size(); i++) (*pos)[i] = INF;
    ForwardIterator curr_a = first_a;
    for ( ; curr_a != last_a; curr_a++) {
        if (*curr_a == *first_b) {
            (*pos)[0] = curr_a - first_a;
            break;
        }
    }
    if ((*pos)[0] == INF) return ;

    curr_a = first_a;
    for (int j = 0; curr_a != last_a; curr_a++) {
        while (j > 0 && *(first_b + j) != *curr_a) j = prn[j - 1];
        if ((*pos)[j] == INF) (*pos)[j] = curr_a - first_a;
        if (*(first_b + j) == *curr_a) j++;
    }
}

int main()
{
    cin >> s;

    int m, cnt = 0;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string word;
        cin >> word;
        kmp_init(word.begin(), word.end());
        kmp(s.begin(), s.end(), word.begin(), word.end(), &f);
        kmp_init(word.rbegin(), word.rend());
        kmp(s.rbegin(), s.rend(), word.rbegin(), word.rend(), &g);
        for (int i = 0; i + 1 < word.length(); i++)
            if (f[i] + g[word.length() - i - 2] < s.length() - 1) {
                cnt++;
                break;
            }
    }
    cout << cnt << endl;

    return 0;
}


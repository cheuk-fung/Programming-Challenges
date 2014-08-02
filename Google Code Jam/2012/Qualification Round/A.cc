#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

char mapping[256];
string G;

string sample_input[] = {
    "ejp mysljylc kd kxveddknmc re jsicpdrysi",
    "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd",
    "de kr kd eoya kw aej tysr re ujdr lkgc jv"
};
string sample_output[] = {
    "our language is impossible to understand",
    "there are twenty six factorial possibilities",
    "so it is okay if you want to just give up"
};

int main()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < sample_input[i].length(); j++) {
            mapping[sample_input[i][j]] = sample_output[i][j];
        }
    }
    mapping['q'] = 'z';
    mapping['z'] = 'q';
    mapping[' '] = ' ';

    int tasks;
    cin >> tasks;
    getline(cin, G);
    for (int task = 0; task < tasks; task++) {
        getline(cin, G);
        cout << "Case #" << task + 1 << ": ";
        for (int i = 0; i < G.length(); i++) {
            cout << mapping[G[i]];
        }
        cout << endl;
    }

    return 0;
}


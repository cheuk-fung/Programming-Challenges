#include <iostream>
#include <algorithm>

using namespace std;

bool check(char c, char mat[4][5])
{
    bool rdia = true;
    bool ldia = true;
    for (int i = 0; i < 4; i++) {
        bool row = true;
        bool col = true;
        for (int j = 0; j < 4; j++) {
            row &= mat[i][j] == c || mat[i][j] == 'T';
            col &= mat[j][i] == c || mat[j][i] == 'T';
        }
        if (row || col) return true;

        rdia &= mat[i][i] == c || mat[i][i] == 'T';
        ldia &= mat[i][3 - i] == c || mat[i][3 - i] == 'T';
    }

    return rdia || ldia;
}

bool count(char c, char mat[4][5])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[i][j] == c) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        char mat[4][5];
        for (int i = 0; i < 4; i++) cin >> mat[i];
        int status = 3;
        if (check('X', mat)) status = 0;
        else if (check('O', mat)) status = 1;
        else if (count('.', mat)) status = 2;
        cout << "Case #" << task << ": ";
        switch (status) {
            case 0: cout << "X won"; break;
            case 1: cout << "O won"; break;
            case 2: cout << "Draw"; break;
            default: cout << "Game has not completed";
        }
        cout << endl;
    }

    return 0;
}

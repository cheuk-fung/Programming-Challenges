/*
 *  SRC: ZOJ 3594
 * PROB: Sexagenary Cycle
 * ALGO: NULL
 * DATE: Apr 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>

using namespace std;

string heavenly[] = {
    "", "Jia", "Yi", "Bing", "Ding", "Wu", "Ji", "Geng", "Xin", "Ren", "Gui"
};
string earthly[] = {
    "", "zi", "chou", "yin", "mao", "chen", "si", "wu", "wei", "shen", "you", "xu", "hai"
};

int main()
{
    int tasks;
    cin >> tasks;

    while (tasks--) {
        int n;
        cin >> n;
        if (n < 0) n++;

        int h = (n - 3) % 10;
        if (h <= 0) h += 10;
        int e = (n - 3) % 12;
        if (e <= 0) e += 12;
        cout << heavenly[h] << earthly[e] << endl;
    }

    return 0;
}


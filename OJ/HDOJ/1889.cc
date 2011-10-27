/*
 *  SRC: HDOJ 1889
 * PROB: Reaux! Sham! Beaux! 
 * ALGO: NULL
 * DATE: Aug 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> rsp;

inline int judge(int a, int b)
{
    if (a == 1 && b == 2) return 1;
    if (a == 2 && b == 1) return 0;

    if (a == 1 && b == 3) return 0;
    if (a == 3 && b == 1) return 1;

    if (a == 2 && b == 3) return 1;
    if (a == 3 && b == 2) return 0;

    return 0;
}

int main()
{
    rsp["Kamen"] = 1;
    rsp["Rock"] = 1;
    rsp["Pierre"] = 1;
    rsp["Stein"] = 1;
    rsp["Ko"] = 1;
    rsp["Koe"] = 1;
    rsp["Sasso"] = 1;
    rsp["Roccia"] = 1;
    rsp["Guu"] = 1;
    rsp["Kamien"] = 1;
    rsp["Piedra"] = 1;

    rsp["Nuzky"] = 2;
    rsp["Scissors"] = 2;
    rsp["Ciseaux"] = 2;
    rsp["Schere"] = 2;
    rsp["Ollo"] = 2;
    rsp["Olloo"] = 2;
    rsp["Forbice"] = 2;
    rsp["Choki"] = 2;
    rsp["Nozyce"] = 2;
    rsp["Tijera"] = 2;

    rsp["Papir"] = 3;
    rsp["Paper"] = 3;
    rsp["Feuille"] = 3;
    rsp["Papier"] = 3;
    rsp["Papir"] = 3;
    rsp["Carta"] = 3;
    rsp["Rete"] = 3;
    rsp["Paa"] = 3;
    rsp["Papier"] = 3;
    rsp["Papel"] = 3;

    int cnt = 1;
    while (1 + 1 == 2) {
        string p1, p2;
        cin >> p1 >> p1;
        cin >> p2 >> p2;

        string a, b;
        int win1 = 0, win2 = 0;
        while (cin >> a, a != "-" && a != ".") {
            cin >> b;
            win1 += judge(rsp[a], rsp[b]);
            win2 += judge(rsp[b], rsp[a]);
        }

        cout << "Game #" << cnt++ << ":\n";
        cout << p1 << ": " << win1 << " point" << (win1 == 1 ? "" : "s") << "\n";
        cout << p2 << ": " << win2 << " point" << (win2 == 1 ? "" : "s") << "\n";
        if (win1 == win2) cout << "TIED GAME\n\n";
        else cout << "WINNER: " << (win1 > win2 ? p1 : p2) << "\n\n";

        if (a == ".") break;


    }


    return 0;
}

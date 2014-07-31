#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int len[4];
int shift2;
int left3, right3;
int left_shift3, right_shift3;

int calc()
{
    int h[4][4];
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 4; j++)
            cin >> h[i][j];

    len[0] = 0;
    len[1] = h[0][1];

    int diff = abs(h[0][1] - h[0][2]);
    if (h[1][2] < diff || ((h[1][2] - diff) & 1)) return -1;
    shift2 = (h[1][2] - diff) / 2;
    len[2] = max(h[0][1], h[0][2]) + shift2;
    if (h[0][1] > h[0][2]) shift2 += diff;

    diff = abs(h[0][1] - h[0][3]);
    if (h[1][3] < diff || ((h[1][3] - diff) & 1)) return -1;
    right3 = (h[1][3] - diff) / 2;
    if (h[0][3] > h[0][1]) right3 += h[0][3] - h[0][1];
    left3 = h[0][3] - right3;
    int left_diff3 = abs(left3 - (len[1] - shift2));
    left_shift3 = min(shift2, len[1] - left3);
    right_shift3 = 0;
    if (left_diff3 > h[2][3]) return -1;
    if (left_diff3 == h[2][3]) {
        if (right3 != len[2] - len[1]) return -1;
        len[3] = len[2];
    } else {
        int right_diff3 = abs(len[2] - len[1] - right3);
        diff = left_diff3 + right_diff3;
        if (h[2][3] < diff || ((h[2][3] - diff) & 1)) return -1;

        int left_can_shift3 = min(left_shift3, min(len[1] - shift2, left3));
        if (left_can_shift3 >= (h[2][3] - diff) / 2) {
            len[3] = len[1] + right3;
            left_shift3 -= (h[2][3] - diff) / 2;
        } else {
            diff += left_can_shift3 * 2;
            left_shift3 -= left_can_shift3;
            right_shift3 = (h[2][3] - diff) / 2;
            if (len[2] - len[1] > right3) right_shift3 += len[2] - len[1] - right3;
            len[3] = len[1] + right_shift3 + right3;
        }
    }

    return *max_element(len, len + 4);
}

int main()
{
    int r = calc();
    cout << r << endl;
    if (r != -1) {
        for (int i = 0; i < r; i++) putchar('a');
        putchar(10);

        for (int i = 0; i < len[1]; i++) putchar('b');
        for (int i = len[1]; i < r; i++) putchar('a');
        putchar(10);

        for (int i = 0; i < shift2; i++) putchar('a');
        for (int i = shift2; i < len[2]; i++) putchar('b');
        for (int i = len[2]; i < r; i++) putchar('a');
        putchar(10);

        for (int i = 0; i < left_shift3; i++) putchar('a');
        for (int i = 0; i < left3; i++) putchar('b');
        for (int i = left_shift3 + left3; i < len[1]; i++) putchar('a');
        for (int i = 0; i < right_shift3; i++) putchar('a');
        for (int i = 0; i < right3; i++) putchar('b');
        for (int i = len[1] + right_shift3 + right3; i < r; i++) putchar('a');
        putchar(10);
    }

    return 0;
}


/*
 *  SRC: POJ 2792
 * PROB: Brackets Removal
 * ALGO: Expression
 * DATE: Aug 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <stack>

using std::stack;

char expr[1010];

bool check(int a, int b, int len)
{
    int prev = a - 1,
        next = b + 1;
    while (prev >= 0 && expr[prev] == ' ') prev--;

    bool flag = 0;
    int cnt = 0;
    for (int i = a + 1; i < b; i++) {
        switch(expr[i]) {
            case '(': cnt++; break;
            case ')': cnt--; break;
            case '+': case '-':
                      if (cnt == 0) flag = 1;
        }
        if (flag) break;
    }

    if (prev < 0 || expr[prev] == '(' || expr[prev] == '+') {
        if (!flag) return true;
        if (next < len && (expr[next] == '*' || expr[next] == '/')) return false;
        return true;
    }

    if (expr[prev] == '-') {
        if (!flag) return true;
        if (next < len && (expr[next] == '*' || expr[next] == '/')) return false;
        cnt = 0;
        for (int i = a + 1; i < b; i++)
            switch(expr[i]) {
                case '(': cnt++; break;
                case ')': cnt--; break;
                case '+': if (cnt == 0) expr[i] = '-'; break;
                case '-': if (cnt == 0) expr[i] = '+'; break;
            }
        return true;
    }

    if (flag) return false;

    if (expr[prev] == '*') return true;

    cnt = 0;
    for (int i = a + 1; i < b; i++) {
        switch(expr[i]) {
                case '(': cnt++; break;
                case ')': cnt--; break;
                case '*': if (cnt == 0) expr[i] = '/'; break;
                case '/': if (cnt == 0) expr[i] = '*'; break;
        }
    }
    return true;
}

int main()
{

    scanf("%s", expr);
    int len = strlen(expr);

    stack<int> left;
    for (int i = 0; i < len; i++) {
        if (expr[i] == '(') {
            left.push(i);
            continue;
        }
        if (expr[i] == ')') {
            if (check(left.top(), i, len)) {
                expr[left.top()] = ' ';
                expr[i] = ' ';
            }
            left.pop();
        }
    }

    for (int i = 0; i < len; i++)
        if (expr[i] != ' ') putchar(expr[i]);
    putchar(10);

    return 0;
}

/*
 *  SRC: POJ 1686
 * PROB: Lazy Math Instructor
 * ALGO: Expression
 * DATE: Aug 01, 2011 
 * COMP: c++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stack>

using std::stack;

int priority[255];
stack<char> opr;
stack<int> num;

int val[255];
char a[1000], b[1000];

inline void calcNum()
{
    int b = num.top(); num.pop();
    int a = num.top(); num.pop();
    switch(opr.top()) {
        case '+': num.push(a + b); break;
        case '-': num.push(a - b); break;
        case '*': num.push(a * b);
    }
    opr.pop();
}

int calc(char* s)
{
    opr.push('(');
    while (*s) {
        if (*s == ' ') {
            s++;
            continue;
        }

        if (('0' <= *s && *s <= '9') || ('a' <= *s && *s <= 'z') || ('A' <= *s && *s <= 'Z')) num.push(val[*s]);
        else {
            if (*s == ')') {
                while (opr.top() != '(') calcNum();
                opr.pop();
            }
            else {
                while (opr.top() != '(' && priority[*s] <= priority[opr.top()]) calcNum();
                opr.push(*s);
            }
        }

        s++;
    }

    int res = num.top();
    num.pop();

    return res;
}

bool check()
{
    int len = strlen(a);
    a[len++] = ')';
    a[len++] = '\0';

    len = strlen(b);
    b[len++] = ')';
    b[len++] = '\0';

    for (int k = 0; k < 10; k++) {
        for (int i = 'a'; i <= 'z'; i++) val[i] = rand() % 100;
        for (int i = 'A'; i <= 'Z'; i++) val[i] = val['a' + i - 'A'];
        if (calc(a) != calc(b)) return false;
    }

    return true;
}

int main()
{
    srand(time(0));

    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['('] = 100;
    priority[')'] = 0;
    for (int i = '0'; i <= '9'; i++) val[i] = i - '0';

    int CASE;
    scanf("%d\n", &CASE);
    while (CASE--) {
        gets(a);
        gets(b);
        if (check()) puts("YES");
        else puts("NO");
    }

    return 0;
}

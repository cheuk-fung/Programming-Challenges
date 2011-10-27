/*
ID: os.idea1
LANG: C
TASK: preface
*/
#include <stdio.h>

int n;
long sum[255];

void translate(int p)
{
    if (p >= 1000)
    {
        sum['M'] += p / 1000;
        p %= 1000;
    }
    if (p >= 900)
    {
        sum['C']++;
        sum['M']++;
        p %= 100;
    }
    if (p >= 500)
    {
        sum['D']++;
        sum['C'] += p / 100 - 5;
        p %= 100;
    }
    if (p >= 400)
    {
        sum['C']++;
        sum['D']++;
        p %= 100;
    }
    if (p >= 100)
    {
        sum['C'] += p / 100;
        p %= 100;
    }
    if (p >= 90)
    {
        sum['X']++;
        sum['C']++;
        p %= 10;
    }
    if (p >= 50)
    {
        sum['L'] += 1;
        sum['X'] += p / 10 - 5;
        p %= 10;
    }
    if (p >= 40)
    {
        sum['X']++;
        sum['L']++;
        p %= 10;
    }
    if (p >= 10)
    {
        sum['X'] += p / 10;
        p %= 10;
    }
    switch (p)
    {
        case 1: sum['I']++;
                break;
        case 2: sum['I'] += 2;
                break;
        case 3: sum['I'] += 3;
                break;
        case 4: sum['I']++;
                sum['V']++;
                break;
        case 5: sum['V']++;
                break;
        case 6: sum['V']++;
                sum['I']++;
                break;
        case 7: sum['V']++;
                sum['I'] += 2;
                break;
        case 8: sum['V']++;
                sum['I'] += 3;
                break;
        case 9: sum['I']++;
                sum['X']++;
                break;
    }
}

int main()
{
    FILE *fin=fopen("preface.in","r");
    FILE *fout=fopen("preface.out","w");

    fscanf(fin, "%d", &n);

    int i;
    for (i = 1; i <= n; i++)
        translate(i);

    if (sum['I']) fprintf(fout, "I %ld\n", sum['I']);
    if (sum['V']) fprintf(fout, "V %ld\n", sum['V']);
    if (sum['X']) fprintf(fout, "X %ld\n", sum['X']);
    if (sum['L']) fprintf(fout, "L %ld\n", sum['L']);
    if (sum['C']) fprintf(fout, "C %ld\n", sum['C']);
    if (sum['D']) fprintf(fout, "D %ld\n", sum['D']);
    if (sum['M']) fprintf(fout, "M %ld\n", sum['M']);

    fclose(fin); fclose(fout);

    return 0;
}

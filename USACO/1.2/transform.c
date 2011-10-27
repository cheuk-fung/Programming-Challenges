/*
ID: os.idea1
LANG: C
TASK: transform
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

long n;
char a[11][11],b[11][11],c[11][11];

void turn()
{
    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++) c[i][j]=a[i][j];
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)  a[j][n-1-i]=c[i][j];
}

void turnover()
{
    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++) c[i][j]=a[i][j];
    for (i=0;i<n;i++)
        for (j=0;j<n;j++) a[i][j]=c[i][n-1-j];
}

int check()
{
    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            if (a[i][j]!=b[i][j]) return 0;
    return 1;
}

long change()
{
    turn();
    if (check()) return 1;
    turn();
    if (check()) return 2;
    turn();
    if (check()) return 3;
    turn();
    turnover();
    if (check()) return 4;
    turn();
    if (check()) return 5;
    turn();
    if (check()) return 5;
    turn();
    if (check()) return 5;
    turn();
    turnover();
    if (check()) return 6;
    return 7;
}

int main()
{
    FILE *fin=fopen("transform.in","r");
    FILE *fout=fopen("transform.out","w");

    long i,j;
    fscanf(fin,"%d",&n);
    for (i=0;i<n;i++) fscanf(fin,"%s",&a[i]);
    for (i=0;i<n;i++) fscanf(fin,"%s",&b[i]);
    fprintf(fout,"%d\n",change());
    fclose(fin); fclose(fout);

    return 0;
}

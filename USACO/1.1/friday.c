/*
ID: os.idea1
LANG: C
TASK: friday
*/
#include <stdio.h>
#include <string.h>

int rn(int y)
{
    if (y%400==0) return 1;
    if (y%100==0) return 0;
    if (y%4==0) return 1;
    return 0;
}

int main()
{
    FILE *fin=fopen("friday.in","r");
    FILE *fout=fopen("friday.out","w");

    int n;
    fscanf(fin,"%d",&n);

    int md[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};
    int y,m,wd[8],d=0,td;
    memset(wd,0,sizeof(wd));
    for (y=1900;y<=1900+n-1;y++)
    {
        if (rn(y)) md[2]=29; else md[2]=28;
        for (m=1;m<=12;m++)
        {
            td=(d+13)%7;
            wd[td]++;
            d=(d+md[m])%7;
        }
    }
    fprintf(fout,"%d %d %d %d %d %d %d\n",wd[6],wd[0],wd[1],wd[2],wd[3],wd[4],wd[5]);

    fclose(fin); fclose(fout);
    return 0;
}

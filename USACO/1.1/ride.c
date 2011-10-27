/*
ID: os.idea1
LANG: C
TASK: ride
*/
#include <stdio.h>
#include <string.h>

long getit(char s[])
{
    long tot=1;
    int i;
    for (i=0;i<strlen(s);i++) tot*=s[i]-'A'+1;

    return tot%47;
}

int main()
{
    FILE *fin=fopen("ride.in","r");
    FILE *fout=fopen("ride.out","w");

    char s1[10],s2[10];
    fscanf(fin,"%s%s",s1,s2);

    if (getit(s1)==getit(s2)) fprintf(fout,"GO\n");
    else fprintf(fout,"STAY\n");

    return 0;
}

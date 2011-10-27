/*
ID: os.idea1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

int timeline[1000001];

int main()
{
    FILE *fin=fopen("milk2.in","r");
    FILE *fout=fopen("milk2.out","w");

    long n,i,max=0,min=LONG_MAX;
    memset(timeline,0,sizeof(timeline));
    fscanf(fin,"%d",&n);
    for (i=0;i<n;i++)
    {
        long a,b;
        fscanf(fin,"%d %d",&a,&b);
        max=(max>b)?max:b;
        min=(min<a)?min:a;
        long j;
        for (j=a;j<b;j++) timeline[j]=1;
    }
    int yes=0,no=0,j=0,k=0;
    for (i=min;i<max;i++)
    {
        if (timeline[i])
        {
            j++; k=0;
        }
        if (!timeline[i])
        {
            k++; j=0;
        }
        yes=(j>yes)?j:yes;
        no=(k>no)?k:no;
    }
    fprintf(fout,"%d %d\n",yes,no);

    fclose(fin); fclose(fout);

    return 0;
}


/*
ID: os.idea1
LANG: C
TASK: gift1
*/
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin=fopen("gift1.in","r");
    FILE *fout=fopen("gift1.out","w");

    int np,i,money[10];
    char name[10][15],tn[15];
    fscanf(fin,"%d",&np);
    for (i=0;i<np;i++) fscanf(fin,"%s",name[i]);

    memset(money,0,sizeof(money));
    for (i=0;i<np;i++)
    {
        fscanf(fin,"%s",tn);
        int a,b,j,k;
        fscanf(fin,"%d%d",&a,&b);
        if (b==0) continue;
        for (j=0;j<np;j++)
            if (!strcmp(name[j],tn)) break;
        money[j]-=a/b*b;
        a/=b;
        for (j=0;j<b;j++)
        {
            fscanf(fin,"%s",tn);
            for (k=0;k<np;k++)
                if (!strcmp(name[k],tn)) break;
            money[k]+=a;
        }
    }

    for (i=0;i<np;i++) fprintf(fout,"%s %d\n",name[i],money[i]);

    fclose(fin); fclose(fout);
    return 0;
}

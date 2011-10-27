/*
ID: os.idea1
LANG: C
TASK: crypt1
*/
#include <stdio.h>

int main()
{
    FILE *fin=fopen("crypt1.in","r");
    FILE *fout=fopen("crypt1.out","w");

    long n,ns,num[10]={0},i;
    fscanf(fin,"%d",&n);
    for (i=0;i<n;i++)
    {
        long temp;
        fscanf(fin,"%d",&temp);
        num[temp]=1;
    }
    long j,k,a,b,tot=0;
    for (i=0;i<=9;i++)
    {
        if (!num[i]) continue;
        for (j=0;j<=9;j++)
        {
            if (!num[j]) continue;
            for (k=0;k<=9;k++)
            {
                if (!num[k]) continue;
                long one=i*100+j*10+k;
                for (a=0;a<=9;a++)
                {
                    if (!num[a]) continue;
                    long t=one*a;
                    if (t>999) break;
                    if (t<100) continue;
                    if (!num[t%10]) continue;
                    t/=10;
                    if (!num[t%10]) continue;
                    t/=10;
                    if (!num[t%10]) continue;

                    for (b=0;b<=9;b++)
                    {
                        if (!num[b]) continue;
                        t=one*b;
                        if (t>999) break;
                        if (t<100) continue;
                        if (!num[t%10]) continue;
                        t/=10;
                        if (!num[t%10]) continue;
                        t/=10;
                        if (!num[t%10]) continue;

                        long two=a*10+b;
                        t=one*two;
                        if (t>9999) break;
                        if (t<1000) break;
                        if (!num[t%10]) continue;
                        t/=10;
                        if (!num[t%10]) continue;
                        t/=10;
                        if (!num[t%10]) continue;
                        t/=10;
                        if (!num[t%10]) continue;
                        tot++;
                    }
                }
            }
        }
    }
    fprintf(fout,"%d\n",tot);

    fclose(fin); fclose(fout);

    return 0;
}

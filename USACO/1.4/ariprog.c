/*
ID: os.idea1
LANG: C
TASK: ariprog
*/

long pre[125001]={0},f[125001]={0},ta[100],tb[100];

#include <stdio.h>
#include <string.h>

void qsort(long l,long r)
{
    long i=l,j=r,mida=ta[(l+r)/2],midb=tb[(l+r)/2],tmpa,tmpb;
    while (i<=j)
    {
        while (tb[i]<midb || (tb[i]==midb && ta[i]<mida)) i++;
        while (tb[j]>midb || (tb[j]==midb && ta[j]>mida)) j--;
        if (i<=j)
        {
             tmpa=ta[i]; tmpb=tb[i];
             ta[i]=ta[j]; tb[i]=tb[j];
             ta[j]=tmpa; tb[j]=tmpb;
             i++; j--;
        }
    }
    if (i<r) qsort(i,r);
    if (j>l) qsort(l,j);
}

int main()
{
    FILE *fin=fopen("ariprog.in","r");
    FILE *fout=fopen("ariprog.out","w");

    long a,b,n,m,i,j;
    fscanf(fin,"%ld %ld",&n,&m);
    long check=0,mm=m*m<<1;
    for (i=0;i<=m;i++)
        for (j=0;j<=m;j++)
            pre[i*i+j*j]=1;
    for (i=j=0;i<=mm;i++)
        if (pre[i]) f[j++]=i;

    for (a=0;a<j;a++)
        for (i=a+1;i<j;i++)
        {
            b=f[i]-f[a];
            if (f[a]+(n-1)*b>mm) break;
            long k=0,tmp=f[a];
            while (k<n && pre[tmp])
            {
                tmp+=b;
                k++;
            }
            if (k==n)
            {
                ta[check]=f[a];
                tb[check++]=b;
            }
        }
    if (!(check)) fprintf(fout,"NONE\n");
    else
    {
        qsort(0,check-1);
        for (i=0;i<check;i++) fprintf(fout,"%ld %ld\n",ta[i],tb[i]);
    }
    fclose(fin); fclose(fout);

    return 0;
}

/*
ID: os.idea1
LANG: C
TASK: milk
*/

#include <stdio.h>

long a[5001],p[5001];

void qsort(long l,long r)
{
    long i=l,j=r,mid=p[(l+r)/2],t;
    while (i<=j)
    {
        while (p[i]<mid) i++;
        while (p[j]>mid) j--;
        if (i<=j)
        {
            t=p[i]; p[i]=p[j]; p[j]=t;
            t=a[i]; a[i]=a[j]; a[j]=t;
            i++; j--;
        }
    }
    if (i<r) qsort(i,r);
    if (j>l) qsort(l,j);
}

int main()
{
    FILE *fin=fopen("milk.in","r");
    FILE *fout=fopen("milk.out","w");

    long n,m,i;
    fscanf(fin,"%d %d",&n,&m);
    for (i=0;i<m;i++) fscanf(fin,"%d %d",&p[i],&a[i]);
    qsort(0,m-1);
    long tot=0,k=0;
    while (n>0)
    {
        if (n-a[k]>=0)
        {
            n-=a[k];
            tot+=a[k]*p[k];
            k++;
        }
        else
        {
            tot+=n*p[k];
            n=0;
        }
    }
    fprintf(fout,"%d\n",tot);

    fclose(fin); fclose(fout);

    return 0;
}

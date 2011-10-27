/*
ID: os.idea1
LANG: C
TASK: barn1
*/
#include <stdio.h>

void qsort(long a[],long l,long r)
{
    long i=l,j=r,mid=a[(l+r)/2],t;
    while (i<=j)
    {
        while (a[i]<mid) i++;
        while (a[j]>mid) j--;
        if (i<=j)
        {
            t=a[i]; a[i]=a[j]; a[j]=t;
            i++; j--;
        }
    }
    if (i<r) qsort(a,i,r);
    if (l<j) qsort(a,l,j);
}

int main()
{
    FILE *fin=fopen("barn1.in","r");
    FILE *fout=fopen("barn1.out","w");

    long m,s,c,i,a[201],b[201];;
    fscanf(fin,"%d %d %d",&m,&s,&c);
    if (m>=c)
    {
        fprintf(fout,"%d\n",c);
        fclose(fin); fclose(fout);
        return 0;
    }
    for (i=0;i<c;i++) fscanf(fin,"%d",&a[i]);
    qsort(a,0,c-1);
    for (i=1;i<c;i++) b[i-1]=a[i]-a[i-1]-1;
    qsort(b,0,c-2);
    s=a[c-1]-a[0]+1;
    m--;
    while (m)
    {
        s-=b[c-2-m+1];
        m--;
    }
    fprintf(fout,"%d\n",s);

    fclose(fin); fclose(fout);

    return 0;
}

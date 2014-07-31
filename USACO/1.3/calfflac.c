/*
ID: os.idea1
LANG: C
TASK: calfflac
*/

#include <stdio.h>
#include <string.h>

char s[20001]={'\0'},ks[20001]={'\0'};
long max=0;

void get(long a,long b,long v,long *pa,long *pb)
{
    long i=a-1,j=b+1;
    while (s[i]==s[j] || !(('a'<=s[i]&&s[i]<='z' || 'A'<=s[i]&&s[i]<='Z')&&('a'<=s[j]&&s[j]<='z' || 'A'<=s[j]&&s[j]<='Z')))
    {
        if (!('a'<=s[i]&&s[i]<='z' || 'A'<=s[i]&&s[i]<='Z')) i--;
        else if (!('a'<=s[j]&&s[j]<='z' || 'A'<=s[j]&&s[j]<='Z')) j++;
        else
        {
            v+=2;
            i--; j++;
        }
    }
    i++; j--;
    if (v>max)
    {
        max=v;
        while (!('a'<=s[i]&&s[i]<='z' || 'A'<=s[i]&&s[i]<='Z')) i++;
        while (!('a'<=s[j]&&s[j]<='z' || 'A'<=s[j]&&s[j]<='Z')) j--;
        *pa=i; *pb=j;
    }
}

int main()
{
    FILE *fin=fopen("calfflac.in","r");
    FILE *fout=fopen("calfflac.out","w");

    char ts[100];
    long pa,pb,i=0;
    while (!feof(fin))  fscanf(fin,"%c",&ks[i++]);
    for (i=0;i<strlen(ks);i++)
    {
        s[i]=ks[i];
        if ('A'<=s[i]&&s[i]<='Z') s[i]+=32;
    }
    for (i=0;i<strlen(s);i++)
        if ('a'<=s[i]&&s[i]<='z' || 'A'<=s[i]&&s[i]<='Z')
        {
            int a=i,b=i+1,t;
            get(a,a,1,&pa,&pb);
            while (!('a'<=s[b]&&s[b]<='z' || 'A'<=s[b]&&s[b]<='Z')) b++;
            if (s[a]==s[b]) get(a,b,2,&pa,&pb);
        }
    fprintf(fout,"%ld\n",max);
    for (i=pa;i<=pb;i++) fprintf(fout,"%c",ks[i]);
    fprintf(fout,"\n");

    fclose(fin); fclose(fout);

    return 0;
}

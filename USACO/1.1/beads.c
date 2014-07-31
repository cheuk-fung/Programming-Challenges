/*
ID: os.idea1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <string.h>

int max(int a,int b)
{
    return (a>b)?a:b;
}

int main()
{
    FILE *fin=fopen("beads.in","r");
    FILE *fout=fopen("beads.out","w");

    int n,i;
    char s[1000];
    fscanf(fin,"%d %s",&n,s);

    int slen=n<<1;
    for (i=0;i<n;i++) s[i+n]=s[i];

    int r1[1000],b1[1000];
    r1[0]=(s[0]=='r' || s[0]=='w')?1:0;
    b1[0]=(s[0]=='b' || s[0]=='w')?1:0;
    for (i=1;i<slen;i++)
        switch (s[i])
        {
            case 'r':
                r1[i]=r1[i-1]+1;
                b1[i]=0;
                break;
            case 'b':
                b1[i]=b1[i-1]+1;
                r1[i]=0;
                break;
            case 'w':
                r1[i]=r1[i-1]+1;
                b1[i]=b1[i-1]+1;
                break;
        }
    int r2[1000],b2[1000];
    r1[slen]=(s[slen]=='r' || s[slen]=='w')?1:0;
    b1[slen]=(s[slen]=='b' || s[slen]=='w')?1:0;
    for (i=slen-1;i>=0;i--)
        switch (s[i])
        {
            case 'r':
                r2[i]=r2[i+1]+1;
                b2[i]=0;
                break;
            case 'b':
                b2[i]=b2[i+1]+1;
                r2[i]=0;
                break;
            case 'w':
                r2[i]=r2[i+1]+1;
                b2[i]=b2[i+1]+1;
                break;
        }

    int maxsum=0;
    for (i=0;i<slen;i++)
        maxsum=max(maxsum,max(r1[i],b1[i])+max(r2[i+1],b2[i+1]));
    if (maxsum>n) maxsum=n;
    fprintf(fout,"%d\n",maxsum);

    fclose(fin); fclose(fout);
    return 0;
}

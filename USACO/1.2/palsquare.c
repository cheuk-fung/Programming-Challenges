/*
ID: os.idea1
LANG: C
TASK: palsquare
*/
#include <stdio.h>
#include <string.h>

const char num[21]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K'};

int main()
{
    FILE *fin=fopen("palsquare.in","r");
    FILE *fout=fopen("palsquare.out","w");

    int n;
    fscanf(fin,"%d",&n);

    int i;
    for (i=1;i<=300;i++)
    {
        int k=i*i,j=-1;
        char s[100];
        while (k>0)
        {
            j++;
            s[j]=num[k%n];
            k/=n;
        }
        s[j+1]='\0';
        int check=1;
        for (k=0;k<j/2+1;k++)
            if (s[k]!=s[j-k])
            {
                check=0;
                break;
            }
        if (check) {
            char tis[100],is[100];
            int k=i,j=-1;
            while (k>0)
            {
                j++;
                tis[j]=num[k%n];
                k/=n;
            }
            for (k=0;k<=j;k++) is[k]=tis[j-k];
            is[j+1]='\0';
            fprintf(fout,"%s %s\n",is,s);
        }
    }

    fclose(fin); fclose(fout);

    return 0;
}

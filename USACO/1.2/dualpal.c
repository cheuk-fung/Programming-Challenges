/*
ID: os.idea1
LANG: C
TASK: dualpal
*/
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin=fopen("dualpal.in","r");
    FILE *fout=fopen("dualpal.out","w");

    int n,s;
    fscanf(fin,"%d %d",&n,&s);

    int tot=0,num=s;
    while (tot<n)
    {
        num++;
        int i,c=0;
        for (i=2;i<=10&&c<2;i++)
        {
            int k=num,j=-1;
            char s[100];
            while (k>0)
            {
                j++;
                s[j]=k%i+'0';
                k/=i;
            }
            s[j+1]='\0';
            int check=1;
            for (k=0;k<j/2+1;k++)
                if (s[k]!=s[j-k])
                {
                    check=0;
                    break;
                }
            if (check) c++;
        }
        if (c==2)
        {
            fprintf(fout,"%d\n",num);
            tot++;
        }
    }

    fclose(fin); fclose(fout);

    return 0;
}

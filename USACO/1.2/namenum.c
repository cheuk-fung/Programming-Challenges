/*
ID: os.idea1
LANG: C
TASK: namenum
*/
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin=fopen("namenum.in","r");
    FILE *fout=fopen("namenum.out","w");
    FILE *dicttxt=fopen("dict.txt","r");

    long long name;
    long tot=0;

    fscanf(fin,"%lld",&name);

    while (!feof(dicttxt))
    {
        char dict[12];
        fscanf(dicttxt,"%s",dict);
        long i;
        long long num=0;
        for (i=0;i<strlen(dict);i++)
        {
            num*=10;
            switch (dict[i])
            {
                case 'A': case 'B': case 'C':num+=2; break;
                case 'D': case 'E': case 'F':num+=3; break;
                case 'G': case 'H': case 'I':num+=4; break;
                case 'J': case 'K': case 'L':num+=5; break;
                case 'M': case 'N': case 'O':num+=6; break;
                case 'P': case 'R': case 'S':num+=7; break;
                case 'T': case 'U': case 'V':num+=8; break;
                case 'W': case 'X': case 'Y':num+=9; break;
            }
        }
        if (num==name)
        {
            tot++;
            fprintf(fout,"%s\n",dict);
        }
    }
    if (!tot) fprintf(fout,"NONE\n");

    fclose(fin); fclose(fout); fclose(dicttxt);

    return 0;
}

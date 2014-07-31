/*
ID: os.idea1
LANG: C
TASK: clocks
*/

#include <stdio.h>

int hash[300000]={0},clock[300000][9]={{0}},ans[30];
long data[300000][2]={{0}}/* 0:last no., 1:father*/;
const long four[10]={1,4,16,64,256,1024,4096,16384,65536,262144};

long gethash(long k)
{
    long tmp=0,i;
    for (i=0;i<9;i++) tmp+=clock[k][i]%4*four[i];
    return tmp;
}

int main()
{
    FILE *fin=fopen("clocks.in","r");
    FILE *fout=fopen("clocks.out","w");

    const int turn[9][9]={ {3,3,0,3,3,0},
                           {3,3,3,0},
                           {0,3,3,0,3,3,0},
                           {3,0,0,3,0,0,3,0},
                           {0,3,0,3,3,3,0,3,0},
                           {0,0,3,0,0,3,0,0,3},
                           {0,0,0,3,3,0,3,3,0},
                           {0,0,0,0,0,0,3,3,3},
                           {0,0,0,0,3,3,0,3,3} };
    long i,open=0,closed=-1;

    for (i=0;i<9;i++)
    {
        fscanf(fin,"%d",&clock[0][i]);
        clock[0][i]%=12;
    }
    data[0][0]=0; data[0][1]=-1;
    hash[gethash(0)]=1;

    while (open>closed)
    {
        closed++;
        for (i=data[closed][0];i<9/* && tu[closed][i]<4*/;i++)
        {
            open++;
            long j;
            for (j=0;j<9;j++)
            {
                clock[open][j]=(clock[closed][j]+turn[i][j])%12;
               // tu[open][j]=tu[closed][j];
            }
            //tu[open][i]++;
            data[open][0]=i; data[open][1]=closed;

            long tmp=gethash(open);
            if (hash[tmp])
            {
                open--;
                continue;
            }
            hash[tmp]=1;
           // if ((i==5-1 && data[open][1]==3) || (i==8-1 && data[data[open][1]][0]==4) || (i==9-1 && data[data[open][1]][0]==7))

            /*prlongf("%d %d %d\n",i,data[open][0],data[open][1]);
            for (j=0;j<9;j++) prlongf("%d ",clock[closed][j]);
            prlongf("\n");
            for (j=0;j<9;j++) prlongf("%d ",clock[open][j]);
            prlongf("\n");
            getchar();*/

            if (tmp==0)
            {
                long k=open,p=0;
                while (data[k][1]>=0)
                {

            /*printf("%ld\n",data[k][0]+1);
            for (j=0;j<9;j++) printf("%d ",clock[k][j]);
            printf("\n");*/

                    ans[p++]=data[k][0]+1;
                    k=data[k][1];

            /*for (j=0;j<9;j++) printf("%d ",clock[k][j]);
            printf("\n");
            getchar();*/
                }
                p--;
                for (k=p;k>0;k--) fprintf(fout,"%d ",ans[k]);
                fprintf(fout,"%d\n",ans[0]);
                fclose(fin);fclose(fout);

                return 0;
            }
        }
    }

    return 0;
}


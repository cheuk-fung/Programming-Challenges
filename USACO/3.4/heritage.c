/*
ID: os.idea1
LANG: C
TASK: heritage
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;
char pre[26], mid[26];

void getpost(char *pre, char *mid)
{
    if (!strlen(pre) || !strlen(mid)) return;
    char *p = strchr(mid, pre[0]), tmp1[26] = "\0", tmp2[26] = "\0";
    getpost(strncpy(tmp1, pre, strlen(mid) - strlen(p) + 1) + 1, strncpy(tmp2, mid, strlen(mid) - strlen(p)));
    getpost(pre + strlen(mid) - strlen(p), ++p);
    fprintf(fout, "%c", pre[0]);
}

int main()
{
    fin = fopen("heritage.in", "r");
    fout = fopen("heritage.out", "w");

    fscanf(fin, "%s %s", mid, pre);

    getpost(pre, mid);
    fprintf(fout, "\n");

    fclose(fin); fclose(fout);
    return 0;
}

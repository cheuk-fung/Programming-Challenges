/*
ID: os.idea1
LANG: C
TASK: cryptcow
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define hash_max 97011

static char suc[75] = "Begin the Escape execution at the Break of Dawn";

char s[75], goal[75];
long slen, times, char_time_suc[256], char_time_s[256], p[75];
int hash_table[hash_max + 1];

FILE *fin, *fout;

void decode(int p)
{
    if (p) fprintf(fout, "1 %ld\n", times);
    else fprintf(fout, "0 0\n");
    fclose(fin); fclose(fout);
    exit(0);
}

int input_error()
{
    long i;
    for (i = 0; i < strlen(suc); i++) char_time_suc[(int)suc[i]]++;
    for (i = 0; i < strlen(s); i++) char_time_s[(int)s[i]]++;
    if (char_time_s[(int)'C'] != char_time_s[(int)'O'] || char_time_s[(int)'C'] != char_time_s[(int)'W'])
	return 1;
    for (i = 0; i < 256; i++)
	if (i != (int)'C' && i != (int)'O' && i != (int)'W' && char_time_s[i] != char_time_suc[i])
	    return 1;
    return 0;
}

int hash(char ss[])
{
    long long hash_sum = 0, hash_base = 1;
    long i;
    for (i = 0; i < strlen(ss); i++)
    {
	hash_sum = (hash_sum + (int)ss[i] * hash_base) % LONG_MAX;
	hash_base = hash_base * 11 % LONG_MAX;
    }
    hash_sum %= hash_max;
    if (hash_table[hash_sum]) return 1;
    hash_table[hash_sum] = 1;
    return 0;
}

int ELFhash(char ss[])
{
    long i, h = 0, g;
    for (i = 0; i < strlen(ss); i++)
    {
	h = (h << 4) + (int)ss[i];
	g = h & 0xf0000000;
	if (g)
	    h ^= g >> 24;
	h &= ~g;
    }
    h %= hash_max;
    if (hash_table[h]) return 1;
    hash_table[h] = 1;
    return 0;
}

void kmp_pre()
{
    long i, j = -1;
    p[0] = -1;
    for (i = 1; i < strlen(goal); i++)
    {
	while (j > -1 && goal[j + 1] != goal[i]) j = p[j];
	if (goal[j + 1] == goal[i]) j++;
	p[i] = j;
    }
}

int kmp()
{
    long i, j = -1, k = strlen(goal) - 1;
    for (i = 0; i < strlen(suc); i++)
    {
	while (j > -1 && goal[j + 1] != suc[i]) j = p[j];
	if (goal[j + 1] == suc[i]) j++;
	if (j == k) return 1;
    }
    return 0;
}

int Impossible(char ss[])
{
    long i, j, len = strlen(ss);
    for (i = j = 0; i <= len; i++)
    {
	if (ss[i] == 'C' || ss[i] == 'O' || ss[i] == 'W' || i == len)
	{
	    goal[j] = '\0';
	    if (j)
	    {
		kmp_pre();
		if (!kmp()) return 1;
	    }
	    j = 0;
	}
	else
	    goal[j++] = ss[i];
    }
    return 0;
}

void swap(char ss[], char str[], long C, long O, long W)
{
    long i, j;
    for (i = 0; i < C; i++) ss[i] = str[i];
    for (j = O + 1; j < W; i++, j++) ss[i] = str[j];  
    for (j = C + 1; j < O; i++, j++) ss[i] = str[j];
    for (j = W + 1; j < strlen(str); i++, j++) ss[i] = str[j];
    ss[i] = '\0';
}

void find_COW(char str[])
{
    if (hash(str)) return;
    if (Impossible(str)) return;
    long i, j, k;
    for (i = 0; i < strlen(str); i++)
	if (str[i] == 'O')
	    for (j = 0; j < i; j++)
		if (str[j] == 'C')
		    for (k = strlen(str) - 1; k > i; k--)
			if (str[k] == 'W')
			{
			    char ss[75];
			    swap(ss, str, j, i, k);
			    if (!strcmp(ss, suc)) decode(1);	
			    find_COW(ss);
			}
}

int main()
{
    fin = fopen("cryptcow.in", "r");
    fout = fopen("cryptcow.out", "w");

    char c;
    while (1 + 1 == 2)
    {
	fscanf(fin, "%c", &c);
	if (c == '\n') break;
	if (c == 'C') times++;
	s[slen++] = c;
    }
    s[slen] = '\0';
    if (!strcmp(s, suc)) decode(1);
    else if (input_error()) decode(0);
    else
    {
	find_COW(s);
	decode(0);
    }

    return 0;
}

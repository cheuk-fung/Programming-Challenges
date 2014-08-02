/*
 *  SRC: POJ 1035
 * PROB: Spell checker
 * AlGO: string
 * DATE: Nov 5, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

using namespace std;

int input(char** words)
{
    int sum = 0;
    while (1 + 1 == 2) {
	words[sum] = new char[16];
	scanf("%s", words[sum]);
	if (words[sum][0] == '#') break;
	sum++;
    }
    return sum;
}

bool find(char* word, char** dict, int DictSum)
{
    for (int i = 0; i < DictSum; i++)
	if (!strcmp(word, dict[i])) return true;
    return false;
}

bool DeleteChar(char* word, char* dict)
{
    int i, len = strlen(dict);
    for (i = 0; i < len; i++)
	if (word[i] != dict[i]) break;
    for (; i < len; i++)
	if (word[i + 1] != dict[i]) return false;
    return true;
}

bool ReplaceChar(char* word, char* dict)
{
    int i, len = strlen(dict);
    for (i = 0; i < len; i++)
	if (word[i] != dict[i]) break;
    for (i++; i < len; i++)
	if (word[i] != dict[i]) return false;
    return true;
}

bool InsertChar(char* word, char* dict)
{
    int i, len = strlen(word);
    for (i = 0; i < len; i++)
	if (word[i] != dict[i]) break;
    for (; i < len; i++)
	if (word[i] != dict[i + 1]) return false;
    return true;
}

int main()
{
    char* dict[10001];
    char* words[51];
    int DictSum = input(dict), WordSum = input(words);

    for (int i = 0; i < WordSum; i++) {
	if (find(words[i], dict, DictSum)) {
	    printf("%s is correct\n", words[i]);
	    continue;
	}

	printf("%s:", words[i]);
	for (int j = 0; j < DictSum; j++) {
	    if (strlen(words[i]) - 1 == strlen(dict[j]))
	    {
		if (DeleteChar(words[i], dict[j])) printf(" %s", dict[j]);
		continue;
	    }
	    if (strlen(words[i]) == strlen(dict[j]))
	    {
		if (ReplaceChar(words[i], dict[j])) printf(" %s", dict[j]);
		continue;
	    }
	    if (strlen(words[i]) + 1 == strlen(dict[j]))
	    {
		if (InsertChar(words[i], dict[j])) printf(" %s", dict[j]);
		continue;
	    }
	}
	printf("\n");
    }

    return 0;
}


/*
 *  SRC: POJ
 * TASK: Repeater
 * ALGO: D&C
 * DATE: Nov. 4, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

using namespace std;

int n;
char tmp[10][10], pic[5000][5000];

bool draw(int level)
{
    if (level == 2) {
	for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++) {
		if (tmp[i][j] == ' ') {
		    for (int a = i * n; a < (i + 1) * n; a++)
			for (int b = j * n; b < (j + 1) * n; b++)
			    pic[a][b] = ' ';
		}
		else {
		    for (int a = i * n, c = 0; a < (i + 1) * n; a++, c++)
			for (int b = j * n, d = 0; b < (j + 1) * n; b++, d++)
			    pic[a][b] = tmp[c][d];
		}
	    }
	return true;
    }

    bool flag = false;
    int size = pow(n, level - 1);
    for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) {
	    if (tmp[i][j] == ' ') {
		for (int a = i * size; a < (i + 1) * size; a++)
		    for (int b = j * size; b < (j + 1) * size; b++)
			pic[a][b] = ' ';
	    }
	    else {
		if (flag == false) flag = draw(level - 1);
		else {
		    for (int a = i * size, c = 0; a < (i + 1) * size; a++, c++)
			for (int b = j * size, d = 0; b < (j + 1) * size; b++, d++)
			    pic[a][b] = pic[c][d];
		}
	    }
	}
    
    return true;
}

bool repeating()
{
    scanf("%d", &n);
    if (!n) return false;
    
    for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) {
	    tmp[i][j] = getchar();
	    if (tmp[i][j] == '\n') tmp[i][j] = getchar();
	}

    int q;
    scanf("%d", &q);

    if (q == 0) return true;
    if (q == 1) {
	for (int i = 0; i < n; i++) {
	    tmp[i][n] = '\0';
	    printf("%s\n", tmp[i]);
	}

	return true;
    }

    draw(q);

    int size = pow(n, q);
    for (int i = 0; i < size; i++) {
	pic[i][size] = '\0';
	printf("%s\n", pic[i]);
    }

    return true;
}
    
int main()
{
    while (repeating()) ;

    return 0;
}


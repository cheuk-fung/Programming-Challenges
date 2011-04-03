/*
 *  SRC: NKOJ
 * TASK: All Star Game
 * ALGO: DFS
 * DATE: 03/27/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<map>
#include	<string>

long N, Max;
std::string Team[30][5];
std::map<std::string, bool> Gamer;

void DFS(long tm, long sum)
{
    if (sum + N - tm < Max) return ;
    if (tm == N) {
        if (sum > Max) Max = sum;
        return ;
    }

    DFS(tm + 1, sum);

    if (!(Gamer[Team[tm][0]] || Gamer[Team[tm][1]] || Gamer[Team[tm][2]])) {
        Gamer[Team[tm][0]] = true;
        Gamer[Team[tm][1]] = true;
        Gamer[Team[tm][2]] = true;
        DFS(tm + 1, sum + 1);
        Gamer[Team[tm][2]] = false;
        Gamer[Team[tm][1]] = false;
        Gamer[Team[tm][0]] = false;
    }

    return ;
}		/* -----  end of function DFS  ----- */

int main()
{
    scanf("%ld", &N);
    for (long i = 0; i < N; i++) {
        for (long j = 0; j < 3; j++) {
            char ts[50];
            scanf("%s", ts);
            Team[i][j] = std::string(ts);
            Gamer[Team[i][j]] = false;
        }
    }

    DFS(0, 0);

    printf("%ld\n", Max);

    return 0;
}				/* ----------  end of function main  ---------- */


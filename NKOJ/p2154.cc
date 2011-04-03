/*
 *  SRC: NKOJ
 * TASK: Birds Attack
 * ALGO: Physics
 * DATE: 03/27/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<cmath>

int main()
{
    double H, V, g;
    scanf("%lf%lf%lf", &H, &V, &g);
    printf("%.4lf\n", V / g * sqrt(V * V + 2 * g * H));

    return 0;
}				/* ----------  end of function main  ---------- */


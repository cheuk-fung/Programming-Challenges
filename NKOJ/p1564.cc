/*
 *  SRC: NKOJ p1564
 * PROB: Hangover
 * ALGO: NULL
 * DATE: Feb 11, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include	<cstdio>
#include	<cmath>

using namespace std;

double calc ( int mid )
{
    double cc = 0;
    for ( int i = 2; i <= mid + 1; i++ ) cc += double(1) / double(i);

    return cc;
}

void solve ( double c )
{
    for ( int i = 1; ; i++ ) {
	if ( calc( i ) - c > 1e-6 ) {
	    printf ( "%d card(s)\n", i );
	    return ;
	}
    }
}

int main ()
{
    while ( 1 + 1 == 2 ) {
	double c;
	scanf ( "%lf", &c );

	if ( fabs( c ) < 1e-6 ) break;

	solve( c );
    }

    return 0;
}

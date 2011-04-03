/*
 * =====================================================================================
 * 
 *       Filename:  prime.cc
 * 
 *    Description:  
 * 
 *        Created:  04/02/2011 00:01:10
 *       Compiler:  g++
 * 
 *         Author:  Leewings Ac (Zhuofeng Wu), osideal {at} gmail.com
 * 
 * =====================================================================================
 */

long prime(long n, long* p)
{
    bool b[n];
    long sum = 0;
    for (long i = 0; i < n; i++) b[i] = 1;
    for (long i = 2; i < n; i++)
        if (b[i]) {
            p[sum++] = i;
            for (int j = i; j < n; j += i) b[j] = 0;
        }

    return sum;
}


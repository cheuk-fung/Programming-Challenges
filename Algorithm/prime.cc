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

int prime(int n, int* p)
{
    bool b[n];
    int sum = 0;
    for (int i = 0; i < n; i++) b[i] = true;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[sum++] = i;
        for (int j = 0; j < sum && i * p[j] <= n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return sum;
}


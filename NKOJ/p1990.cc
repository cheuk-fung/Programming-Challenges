/*
 *  SRC: NKOJ p1990
 * PROB: Humidex
 * ALGO: Math
 * DATE: May 6, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
void TD(float temp, float dew)
{
    float e, h, humi;
    e = 6.11 * exp(5417.7530 * (1.0 / 273.16 - 1.0 / (dew + 273.16)));
    h = 0.5555 * (e - 10.0);
    humi = temp + h;
    printf("T %.1f D %.1f H %.1f\n", temp, dew, humi);
}
void TH(float temp, float humi)
{
    float h, e, dew;
    h = humi - temp;
    e = h / 0.5555 + 10.0;
    dew = 1.0 / (1.0 / 273.16 - log(e / 6.11) / 5417.7530) - 273.16;
    printf("T %.1f D %.1f H %.1f\n", temp, dew, humi);
}
void DH(float dew, float humi)
{
    float e, h, temp;
    e = 6.11 * exp(5417.7530 * (1.0 / 273.16 - 1.0 / (dew + 273.16)));
    h = 0.5555 * (e - 10.0);
    temp = humi - h;
    printf("T %.1f D %.1f H %.1f\n", temp, dew, humi);
}
int main()
{
    while (1) {
        char p, q;
        scanf("%c", &p);
        if (p == 'E') break;
        if (p == '\n') continue;
        float a, b;
        scanf(" %f %c%f", &a, &q, &b);
        if (p == 'T' && q == 'D') TD(a, b);
        else if (p == 'D' && q == 'T') TD(b, a);
        else if (p == 'T' && q == 'H') TH(a, b);
        else if (p == 'H' && q == 'T') TH(b, a);
        else if (p == 'D' && q == 'H') DH(a, b);
        else DH(b, a);
    }
}

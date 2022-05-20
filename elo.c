#include "elo.h"

double eloRating(double ra, double rb, bool sa)
{
    double ea = (1 / (1 + pow(10, ((rb - ra) / 400))));
    
    double ra_new;

    if (sa == 1) 
    {
        ra_new = ra + 30 * (1 - ea);
    }
    else
    {
        ra_new = ra + 30 * (0 - ea);
    }

    return ra_new;
}

char *division(double rx_new)
{
    if (rx_new >= 0 && rx_new <= 1149)
    {
        return "Bronze";
    }
    else if (rx_new >= 1150 && rx_new <= 1499)
    {
        return "Silver";
    }
    else if (rx_new >= 1500 && rx_new <= 1849)
    {
        return "Gold";
    }
    else if (rx_new >= 1850 && rx_new <= 2199)
    {
        return "Platinum";
    }
    else if (rx_new >= 2200)
    {
        return "Diamond";
    }

    return 0;
}

double KDratio(int K, int D)
{
    double KD;
    
    if (D == 0)
    {
        KD = (double)K / 1;
    }
    else
    {
        KD = (double)K / D;
    }

    return KD;
}

double KADratio(int K, int A, int D)
{
    double KAD;
    
    if (D == 0)
    {
        KAD = (K + A) / 1;
    }
    else
    {
        KAD = (double)(K + A) / D;
    }

    return KAD;
}
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define SIZE 1000

typedef struct Player_ Player;

struct Player_
{
    int ID; //ID hráče
    char *nickname; //přezdívka hráče
    int K; //počet zabití
    int A; //počet asistencí
    int D; //počet smrtí
    double KDratio; //poměr zabití a smrtí
    double KADratio; //poměr zabití, asistencí a smrtí
    int winCount; //počet výher
    int loseCount; //počet proher
    int matchCount; //počet odehraných zápasů
    double eloRating; //ELO rating hráče
    char *division; //divize hráče
};

double eloRating(double ra, double rb, bool sa); //výpočet ELO ratingu
char *division(double rx_new); //zařazení do divize podle výsledného ratingu
double KDratio(int K, int D); //výpočet poměru zabití a smrtí
double KDAratio(int K, int D, int A); //výpočet poměru zabití, asistencí a smrtí
void match(FILE *matches, Player *allPlayers); //matches.txt
void player(FILE *players, Player *allPlayers); //players.txt
void createHTMLtable(FILE *html, Player *allPlayers); //vytvoření HTML tabulky
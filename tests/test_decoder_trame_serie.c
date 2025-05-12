#include <stdio.h>
#include <stdlib.h>
#include "../src/common.h"


int main()
{

    //char buffer[50];
    int retour;
    Donnees mesure;


    retour = decoder_trame("DATA:21.3,50.9", &mesure);
    printf("retour=%d : temperature:%f humidité:%f\n", retour, mesure.temperature, mesure.humidite);


    return EXIT_SUCCESS;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"


void exit_error(int code_erreur, char *message) 
{
    if (0 == code_erreur) {
        fprintf(stderr, "Mauvaise configuration: code_erreur ne peut pas être nul.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "%s", message);
    exit(code_erreur);   
}


int decoder_trame(char *buffer, Donnees *data)
{
    // Vérifier si la ligne commence par "DATA:"
    if (strncmp(buffer, "DATA:", 5) == 0) {
        if (sscanf(buffer + 5, "%f,%f", &data->temperature, &data->humidite) == 2) {
            return 0;
        }
    }

    return 1;
}
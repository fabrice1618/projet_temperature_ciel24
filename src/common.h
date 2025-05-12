#ifndef COMMON_H
#define COMMON_H

// Structure pour stocker les données de température et d'humidité
typedef struct {
    int timestamp;
    float temperature;
    float humidite;
} Mesure;

// Structure pour stocker les données de température et d'humidité
typedef struct {
    float temperature;
    float humidite;
} Donnees;


void exit_error(int code_erreur, char *message);
int decoder_trame(char *buffer, Donnees *data);

#endif

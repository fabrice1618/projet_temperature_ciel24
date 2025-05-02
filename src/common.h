#ifndef COMMON_H
#define COMMON_H

// Structure pour stocker les données de température et d'humidité
typedef struct {
    int timestamp;
    float temperature;
    float humidite;
} Mesure;


void exit_error(int code_erreur, char *prefixe);

#endif

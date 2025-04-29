#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include "fonctions.h"

#define BUFFER_SIZE 1024

// Fonction pour créer le socket serveur
int creer_socket_serveur() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket");
        exit(EXIT_FAILURE);
    }
    return sock;
}

// Fonction pour lier le socket à l'adresse IP et au port
void lier_socket(int socket, struct sockaddr_in *serverAddr) {
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(1618);  // Port 1618
    serverAddr->sin_addr.s_addr = INADDR_ANY;

    if (bind(socket, (struct sockaddr*)serverAddr, sizeof(*serverAddr)) < 0) {
        perror("Bind");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

// Fonction pour mettre le serveur en écoute
void ecouter_connexions(int socket) {
    if (listen(socket, 1) < 0) {
        perror("Listen");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

// Fonction pour accepter un client
int accepter_client(int socket, struct sockaddr_in *clientAddr) {
    socklen_t addrLen = sizeof(*clientAddr);
    int clientSock = accept(socket, (struct sockaddr*)clientAddr, &addrLen);
    if (clientSock < 0) {
        perror("Accept");
        close(socket);
        exit(EXIT_FAILURE);
    }
    return clientSock;
}

// Fonction pour afficher l'IP du client
void afficher_ip_client(struct sockaddr_in *clientAddr) {
    char ipClient[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr->sin_addr), ipClient, INET_ADDRSTRLEN);
    printf("Client connecté depuis %s:%d\n", ipClient, ntohs(clientAddr->sin_port));
}

// Fonction pour initialiser le fichier CSV (ouvrir et ajouter l'en-tête)
FILE* initialiser_fichier() {
    FILE *fichier = fopen("donnees.tsv", "a");

    if (!fichier) {
        perror("Erreur ouverture fichier CSV");
        exit(EXIT_FAILURE);
    }

    // Ajouter l'en-tête si le fichier est vide
    fseek(fichier, 0, SEEK_END);
    if (ftell(fichier) == 0) {
        fprintf(fichier, "date\t heure\t température\t humidité\n");
    }

    return fichier;
}

// Fonction pour écrire les données reçues dans le fichier
void ecrire_dans_fichier(FILE *fichier, const char *date_str, const char *heure_str, float temperature, float humidite) {
    fprintf(fichier, "%s\t %s\t %.2f\t %.2f\n", date_str, heure_str, temperature, humidite);
    fflush(fichier);
}

// Fonction pour fermer le fichier après utilisation
void fermer_fichier(FILE *fichier) {
    fclose(fichier);
}

// Fonction pour chiffrer le message (décalage de 3)
void chiffrer(char *buffer) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        buffer[i] += 3;  // Décalage de +3
    }
}

// Fonction pour déchiffrer le message (décalage de 3)
void dechiffrer(char *buffer) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        buffer[i] -= 3;  // Décalage de -3
    }
}

// Fonction pour obtenir l'heure et la date actuelles
void date(char *date_str, char *heure_str) {
    int h, min, s, day, mois, an;
    time_t now;
    
    // Renvoie l'heure actuelle
    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;

    // Augmenter la taille du buffer de date_str pour éviter toute troncation
    snprintf(heure_str, 10, "%02d:%02d:%02d", h, min, s);

    // Assurer que la date ne dépasse pas les 30 caractères (ou augmenter la taille si nécessaire)
    snprintf(date_str, 30, "%02d/%02d/%d", day, mois, an);  // Agrandir le buffer à 30 caractères
}

// Fonction pour séparer les données reçues en température et humidité
void separer_donnees(const char *donnees, float *temperature, float *humidite) {
    // Variables pour stocker les valeurs extraites
    float temp, humid;
    
    // Utilisation de sscanf pour extraire les valeurs
    if (sscanf(donnees, "%f %f%%", &temp, &humid) == 2) {
        *temperature = temp;
        *humidite = humid;
        printf("Température: %.2f°C\n", *temperature);
        printf("Humidité: %.2f%%\n", *humidite);
    } else {
        printf("Erreur de format dans les données reçues\n");
    }
}

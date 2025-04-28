#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>

int creer_socket_serveur();
void lier_socket(int socket, struct sockaddr_in *serverAddr);
void ecouter_connexions(int socket);
int accepter_client(int socket, struct sockaddr_in *clientAddr);
void afficher_ip_client(struct sockaddr_in *clientAddr);
FILE* initialiser_fichier();
void ecrire_dans_fichier(FILE *fichier, const char *date_str, const char *heure_str, float temperature, float humidite);
void fermer_fichier(FILE *fichier);
void date(char *date_str, char *heure_str);

// Déclaration des fonctions de chiffrement et déchiffrement
void chiffrer(char *buffer);
void dechiffrer(char *buffer);

// Fonction pour séparer les données reçues en température et humidité
void separer_donnees(const char *donnees, float *temperature, float *humidite);

#endif
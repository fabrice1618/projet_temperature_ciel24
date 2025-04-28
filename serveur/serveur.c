#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h> // Pour la gestion du temps
#include "fonctions.h"

#define BUFFER_SIZE 1024

// Fonction main
int main() {
    int serveurSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;

    // Créer et configurer le socket serveur
    serveurSocket = creer_socket_serveur();
    lier_socket(serveurSocket, &serverAddr);
    ecouter_connexions(serveurSocket);
    printf("Serveur en attente sur le port 1618...\n");

    // Accepter la connexion du client
    clientSocket = accepter_client(serveurSocket, &clientAddr);
    afficher_ip_client(&clientAddr);

    // Gérer la communication avec le client
    FILE *fichier = initialiser_fichier();
    char buffer[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        int recu = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if (recu <= 0) {
            printf("Fin de réception ou erreur.\n");
            break;
        }

        buffer[recu] = '\0';

        // Décryptage du message reçu
        dechiffrer(buffer);
        printf("Message décrypté : %s\n", buffer);

        // Séparer la température et l'humidité
        float temperature = 0.0, humidite = 0.0;
        // Utiliser sscanf pour extraire la température et l'humidité
        if (sscanf(buffer, "%f %f%%", &temperature, &humidite) == 2) {
            printf("Température: %.2f\tHumidité: %.2f%%\n", temperature, humidite);

            // Appel de la fonction pour obtenir la date et l'heure
            char date_str[30]; // Augmenter la taille du buffer de date_str
            char heure_str[10];
            date(date_str, heure_str);  // Mettre la date et l'heure dans les variables

            // Écrire dans le fichier CSV avec tabulation entre les valeurs
            ecrire_dans_fichier(fichier, date_str, heure_str, temperature, humidite);

            // **Envoyer une réponse sans chiffrement au client** (pour tester)
            char reponse[] = "Données reçues";  // La réponse peut être modifiée

            // Commenter le chiffrement pour tester sans chiffrement
            // chiffrer(reponse);  // Commenter cette ligne pour tester sans chiffrement

            // Envoyer la réponse sans chiffrement
            int taille_reponse = strlen(reponse);
            ssize_t bytes_sent = send(clientSocket, reponse, taille_reponse, 0);
            if (bytes_sent == -1) {
                perror("Erreur d'envoi de la réponse");
                break;
            } else {
                printf("Réponse envoyée au client : %s\n", reponse);
                printf("Nombre de bytes envoyés : %ld\n", bytes_sent);
            }

        } else {
            printf("Erreur de format des données reçues\n");
        }
    }

    // Fermer le fichier après avoir écrit les données
    fermer_fichier(fichier);

    printf("Données enregistrées dans donnees.csv ✅\n");

    // Fermer les sockets
    close(clientSocket);
    close(serveurSocket);

    return 0;
}

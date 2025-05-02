// client.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <termios.h>
#include <fcntl.h>

#include "client.h"
#include "config.h"



// Crée un socket et retourne le descripteur du socket
int create_socket() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        exit_error("Erreur lors de la création du socket");
    }
    return clientSocket;
}

// Configure la connexion au serveur et se connecte
int connect_to_server(int clientSocket, struct sockaddr_in *serverAddr) {
    if (connect(clientSocket, (struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0) {
        close(clientSocket);
        exit_error("Erreur lors de la connexion");
    }
    return 0;
}

// Envoie un message au serveur
void send_message(int clientSocket, const char *message) {
    ssize_t sent = send(clientSocket, message, strlen(message), 0);
    if (sent < 0) {
        close(clientSocket);
        exit_error("Erreur lors de l'envoi du message");
    }
}

// Chiffrage du message (César avec un décalage de 3)
void chiffrer(char *buffer) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        buffer[i] += 3;
    }
}

// Déchiffrage du message
void dechiffrer(char *buffer) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        buffer[i] -= 3;
    }
}

// Reçoit un message du serveur
void receive_message(int clientSocket, char *buffer1) {
    ssize_t received = recv(clientSocket, buffer1, BUFFER_SIZE, 0);
    if (received < 0) {
        close(clientSocket);
        exit_error("Erreur lors de la réception du message");
    }
    buffer1[received] = '\0';  // Assurez-vous que la chaîne est bien terminée
}

// Ferme le socket
void close_socket(int clientSocket) {
    close(clientSocket);
}



// Fonction pour lire la température et l'humidité depuis le port série
int lire_temperature(int fd, Donnees *data) {
    char buffer[128];
    char c;
    size_t index = 0;

    // Lire les données ligne par ligne
    while (index < sizeof(buffer) - 1) {
        int n = read(fd, &c, 1);
        if (n <= 0) break;       // Erreur ou fin de lecture
        if (c == '\n') break;    // Fin de ligne
        buffer[index++] = c;
    }
    buffer[index] = '\0';  // Ajouter le caractère null à la fin de la chaîne

    // Vérifier si la ligne commence par "DATA:"
    if (strncmp(buffer, "DATA:", 5) == 0) {
        if (sscanf(buffer + 5, "%f,%f", &data->temperature, &data->humidite) == 2) {
            printf("Température : %.2f°C | Humidité : %.2f%%\n", data->temperature, data->humidite);
        } else {
            printf("Format invalide après DATA:\n");
            data->temperature = -999;  // Données invalides
        }
    }

    return 0;
}


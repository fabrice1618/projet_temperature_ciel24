#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "config.h"


int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE], buffer1[BUFFER_SIZE];
    Donnees data = { -999, 0 };  // Initialisation avec valeurs par défaut

    // Création du socket client
    clientSocket = create_socket();

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connexion au serveur
    connect_to_server(clientSocket, &serverAddr);

    // Initialisation de la liaison série avec l'Arduino
    int serial_fd = init_serial();

    printf("Envoi automatique des données toutes les 0.1s. Ctrl+C pour quitter.\n");

    while (1) {
        // Lire la température et l'humidité
        lire_temperature(serial_fd, &data);

        // Si des données valides ont été lues
        if (data.temperature != -999) {
            // Préparer le message à envoyer au serveur
            snprintf(buffer, BUFFER_SIZE, "%.2f %.2f%%\n", data.temperature, data.humidite);

            // Chiffrement et envoi des données
            chiffrer(buffer);
            send_message(clientSocket, buffer);

            // Réception de la réponse du serveur
            receive_message(clientSocket, buffer1);
            dechiffrer(buffer1);
            printf("Réponse du serveur : %s\n", buffer1);

            // Attente avant la prochaine itération (ajuster selon les besoins)
            sleep(1.5);  // Attente de 2 secondes
        }
    }

    close(serial_fd);
    close_socket(clientSocket);
    return 0;
}

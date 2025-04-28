// client.c

#include "client.h"

// Crée un socket et retourne le descripteur du socket
int create_socket() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
    return clientSocket;
}

// Configure la connexion au serveur et se connecte
int connect_to_server(int clientSocket, struct sockaddr_in *serverAddr) {
    if (connect(clientSocket, (struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0) {
        perror("Erreur lors de la connexion");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
    return 0;
}

// Envoie un message au serveur
void send_message(int clientSocket, const char *message) {
    ssize_t sent = send(clientSocket, message, strlen(message), 0);
    if (sent < 0) {
        perror("Erreur lors de l'envoi du message");
        close(clientSocket);
        exit(EXIT_FAILURE);
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
        perror("Erreur lors de la réception du message");
        close(clientSocket);
        exit(EXIT_FAILURE);
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
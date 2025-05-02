// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>


// Structure pour stocker les données de température et d'humidité
typedef struct {
    float temperature;
    float humidite;
} Donnees;


int create_socket();
int connect_to_server(int clientSocket, struct sockaddr_in *serverAddr);
void send_message(int clientSocket, const char *message);
void chiffrer(char *buffer);
void dechiffrer(char *buffer1);
void receive_message(int clientSocket, char *buffer);
void close_socket(int clientSocket);
int lire_temperature(int fd, Donnees *data);
int init_serial();

#endif // CLIENT_FUNCTIONS_H

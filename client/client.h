// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 1618
#define BUFFER_SIZE 1024
#define SERIAL_PORT "/dev/ttyACM0"  // À ajuster selon ton système
//#define SERIAL_PORT "../serveur/log.txt"  // Utiliser le bon port série

// Structure pour stocker les données de température et d'humidité
typedef struct {
    float temperature;
    float humidite;
} Donnees;


int create_socket();
int connect_to_server(int clientSocket, struct sockaddr_in *serverAddr);
void send_message(int clientSocket, const char *message);
void receive_message(int clientSocket, char *buffer);
void close_socket(int clientSocket);
void chiffrer(char *buffer);
void dechiffrer(char *buffer1);
int lire_temperature(int fd, Donnees *data);
int init_serial();

#endif // CLIENT_FUNCTIONS_H

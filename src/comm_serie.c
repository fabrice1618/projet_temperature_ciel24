#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../config.h"
#include "common.h"
#include "comm_serie.h"


// configuration port série
//#define BUFFER_SIZE_SERIE 20
//#define PORT_SERIE_DEFAUT "/dev/ttyACM0"


// Fonction pour initialiser la liaison série
CommSerie open_commSerie(char *port_serie, int buffer_size) 
{
    CommSerie comm;

    comm.fd = open(port_serie, O_RDONLY | O_NOCTTY);
    if (comm.fd < 0) {
        exit_error(2, "Erreur ouverture port série");
    }

    if (buffer_size <= 0) {
        exit_error(2, "Erreur buffer_size port série");
    }
    comm.buffer = (char *) calloc(buffer_size, sizeof(char));
    if (comm.buffer == NULL) {
        exit_error(2, "Erreur allocation buffer port série");
    }
    comm.buffer_size = buffer_size;

    struct termios options;
    tcgetattr(comm.fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);  // Activer le récepteur et désactiver le contrôle de modem
    tcsetattr(comm.fd, TCSANOW, &options);

    return comm;
}


void close_commSerie(CommSerie comm)
{
    free(comm.buffer);
    close(comm.fd);
}


int readline_commSerie(CommSerie comm) 
{
    char c;
    int index = 0;

    memset(comm.buffer, 0, comm.buffer_size);

    while (index < comm.buffer_size - 1) {
        int n = read(comm.fd, &c, 1);
        if (n <= 0) break;       // Erreur ou fin de lecture
        if (c == '\n') break;    // Fin de ligne
        comm.buffer[index++] = c;
    }

    return 0;
}

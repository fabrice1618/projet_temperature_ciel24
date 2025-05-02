#ifndef COMM_SERIE_H
#define COMM_SERIE_H

typedef struct {
    int fd;
    char *buffer;
    int buffer_size;
} CommSerie;

CommSerie open_commSerie(char *port_serie, int buffer_size);
void close_commSerie(CommSerie comm);
int readline_commSerie(CommSerie comm);

#endif
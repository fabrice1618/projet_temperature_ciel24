#include <stdlib.h>

#include "../config.h"
#include "../src/common.h"
#include "../src/comm_serie.h"

int main(int argc, char *argv[])
{
    CommSerie comm_serie;

    if (argc == 2) {
        comm_serie = open_commSerie(argv[1], BUFFER_SIZE_SERIE);
    } else {
        comm_serie = open_commSerie(PORT_SERIE_DEFAUT, BUFFER_SIZE_SERIE);
    }


    close_commSerie(comm_serie);
    
    return EXIT_SUCCESS;
}

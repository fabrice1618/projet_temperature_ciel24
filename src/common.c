#include <stdlib.h>
#include <stdio.h>


void exit_error(int code_erreur, char *message) 
{
    if (0 == code_erreur) {
        fprintf(stderr, "Mauvaise configuration: code_erreur ne peut pas être nul.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "%s", message);
    exit(code_erreur);   
}

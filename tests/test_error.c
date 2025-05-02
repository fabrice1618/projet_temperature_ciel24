#include <stdlib.h>

#include "../config.h"
#include "../src/common.h"

int main()
{
    exit_error(42, "Test erreur");
    
    return EXIT_SUCCESS;
}

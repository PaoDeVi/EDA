#include <stdio.h>
#include <stdlib.h>
#include "kmeans.h"

int 
main(int argc, char *argv[]) 
{
    if (argc == 2) {
        char* name = argv[1];
        img image = mainBMP(name);
        kmeans mk(&image, 2);
        mk.initialize();
        mk.clusterize(10);
        write_modified(image);
    }
    return 0;
}

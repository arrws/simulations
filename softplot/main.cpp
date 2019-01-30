#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "global.h"
#include "drawing.h"

// COMPILE WITH:
// g++ *cpp -lGL -lGLU -lglut

int main(int argc, char **argv)
{
    global.sleep = 80000;

    if (argc > 1)
        strcpy(global.moviefilename, argv[1]);

    initialize_global_data();
    if (argc > 2) // for smaller visualization
        global.radius_particle = 0.01;

    read_moviefile_data();
    
    init_glut();
    init_OpenGl();

    start_main_loop_glut()
    return 0;
}


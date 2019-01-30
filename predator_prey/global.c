#include "global.h"

struct global_struct global;

void init_cellular_automata()
{
    int moves[8][2] = {{1,0}, {0,1}, {1,1}, {-1,0}, {0,-1}, {-1,-1}, {-1, 1}, {1,-1}};
    memcpy(&global.moves, &moves, sizeof moves);

    global.predator = 'x';
    global.prey = '.';
    global.nothing = ' ';


    int i, j;
    global.a = (char **)malloc(global.N_grid * sizeof(char *));
    for (i=0; i<global.N_grid; i++) {
        global.a[i] = (char *)malloc(global.N_grid * sizeof(char));
        for (j=0; j<global.N_grid; j++)
            global.a[i][j] = global.nothing;
    }

    global._a = (char **)malloc(global.N_grid * sizeof(char *));
    for (i=0; i<global.N_grid; i++) {
        global._a[i] = (char *)malloc(global.N_grid * sizeof(char));
        for (j=0; j<global.N_grid; j++)
            global._a[i][j] = global.nothing;
    }

    global.step = 0;

    srand(time(NULL));
    /* init_blob(); */

    init_randomly(global.N_predator, global.predator);
    init_randomly(global.N_prey , global.prey);

}

void init_blob(){
    int m = global.N_grid/2;
    global.N_predator = 3;
    global.N_prey = 9;

    global.a[m+2][m] = global.prey;
    global.a[m+1][m] = global.prey;
    global.a[m][m] = global.prey;
    global.a[m-1][m] = global.prey;

    global.a[m+2][m-1] = global.prey;
    global.a[m+1][m-1] = global.prey;
    global.a[m][m-1] = global.prey;
    global.a[m-1][m-1] = global.prey;

    global.a[m+2][m+1] = global.prey;
    global.a[m+2][m+1] = global.predator;
    global.a[m+1][m+1] = global.predator;
    global.a[m][m+1] = global.predator;
    global.a[m-1][m+1] = global.predator;
}

void init_randomly(int N, char e)
{
    int N_trials;
    int x_try, y_try;
    int i, j;

    for(i=0; i<N; i++)
    {
        x_try = global.N_grid/2;
        y_try = global.N_grid/2;

        N_trials = 0;
        while ((global.a[x_try][y_try] != global.nothing) && (N_trials < 1000))
        {
            //attempt to place
            x_try = (x_try + rand() % global.N_grid) % global.N_grid;
            y_try = (y_try + rand() % global.N_grid) % global.N_grid;
            N_trials++;
        }
        global.a[x_try][y_try] = e;
    }
}


void update_matrix()
{
    int i, j;
    global.N_prey = 0;
    global.N_predator = 0;

    for (i=0; i<global.N_grid; i++) {
        for (j=0; j<global.N_grid; j++) {
            global.a[i][j] = global._a[i][j];
            global._a[i][j] = global.nothing;

            if (global.a[i][j] == global.prey)
                global.N_prey ++;
            if (global.a[i][j] == global.predator)
                global.N_predator ++;
        }
    }
}


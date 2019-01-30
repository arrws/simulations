#include "global.h"
#include "automata.h"

void run_step()
{
    int i,j;
    for (i=0; i<global.N_grid; i++) {
        for (j=0; j<global.N_grid; j++) {
            if (global.a[i][j] == global.prey)
                act_prey(i, j);
            if (global.a[i][j] == global.predator)
                act_predator(i, j);
        }
    }
    update_matrix();
}


void act_predator(int x, int y)
{
    int i, _x, _y, ok = 0;

    // maybe kill predator
    if (!roll_dice(global.pred_death_rate) == 1)
    {
        // keep the original predator
        global._a[x][y] = global.predator;

        // check for prey
        for (i=0; i<8; i++){
            _x = (x + global.moves[i][0] + global.N_grid)% global.N_grid;
            _y = (y + global.moves[i][1] + global.N_grid)% global.N_grid;
            if (global.a[_x][_y] == global.prey) {
                ok = 1;

                // maybe spawn predator
                if (roll_dice(global.pred_spawn_rate) == 1) {
                    global._a[_x][_y] = global.predator;
                }
            }
        }
        // no food die
        if (ok == 0)
            global._a[x][y] = global.nothing;
    }
}

void act_prey(int x, int y)
{
    int i, _x, _y;

    // maybe kill prey
    if (!roll_dice(global.prey_death_rate) == 1)
    {
        // keep the original prey
        global._a[x][y] = global.prey;

        // check free
        for (i=0; i<8; i++){
            _x = (x + global.moves[i][0] + global.N_grid)% global.N_grid;
            _y = (y + global.moves[i][1] + global.N_grid)% global.N_grid;
            if (global.a[_x][_y] == global.nothing && global._a[_x][_y] == global.nothing) {

                // maybe spawn prey
                if (roll_dice(global.prey_spawn_rate) == 1) {
                    global._a[_x][_y] = global.prey;
                }
            }
        }
    }
}

int roll_dice(double chance)
{
    float c =(float)rand()/(float)(RAND_MAX);
    if (c < chance)
        return 1;
    return 0;
}


/* void shuffle(int *array, size_t n) */
/* { */
/*     if (n > 1) */
/*     { */
/*         size_t i; */
/*         for (i = 0; i < n - 1; i++) */
/*         { */
/*             size_t j = i + rand() / (RAND_MAX / (n - i) + 1); */
/*             int t = array[j]; */
/*             array[j] = array[i]; */
/*             array[i] = t; */
/*         } */
/*     } */
/* } */

/* void random_walk(int x, int y, char e) */
/* { */
/*     int arr[8] = {0,1,2,3,4,5,6,7}; */
/*     shuffle(arr, 8); */
/*     int i, _x, _y; */
/*     for (i=0; i<8; i++){ */
/*         _x = (x + global.moves[arr[i]][0] + global.N_grid)% global.N_grid; */
/*         _y = (y + global.moves[arr[i]][1] + global.N_grid)% global.N_grid; */
/*         if (global.a[_x][_y] == global.nothing) { */
/*             global._a[x][y] = global.nothing; */
/*             global._a[_x][_y] = e; */
/*             break; */
/*         } */
/*     } */
/* } */

/* Point get_nearby_pos(int x, int y, char target) */
/* { */
/*     int i, arr[8] = {0,1,2,3,4,5,6,7}; */
/*     Point p; */
/*     for (i=0; i<8; i++){ */
/*         p.x = (x + global.moves[arr[i]][0] + global.N_grid)% global.N_grid; */
/*         p.y = (y + global.moves[arr[i]][1] + global.N_grid)% global.N_grid; */
/*         if (global.a[p.x][p.y] == target) { */
/*             p.ok = 1; */
/*             return p; */
/*         } */
/*     } */
/*     p.ok = 0; */
/*     return p; */
/* } */


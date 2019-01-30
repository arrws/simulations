#ifndef global_h
#define global_h

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>

struct Point
{
    int x;
    int y;
    int ok;
};

struct global_struct
{
    char nothing;
    char predator;
    char prey;

    int N_grid;
    int N_predator;
    int N_prey;
    char **a;
    char **_a;

    double pred_spawn_rate;
    double pred_death_rate;

    double prey_spawn_rate;
    double prey_death_rate;

    int step;
    int moves[8][2];
};

extern struct global_struct global;

void init_blob();
void init_cellular_automata(void);
void init_randomly(int N, char e);
void update_matrix(void);

#endif

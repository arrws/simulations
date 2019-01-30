#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "automata.h"
#include "global.h"


FILE *outfile;
FILE *moviefile;

void write_cmovie()
{
    int i,j;
    float floatholder;
    int intholder;

    intholder = global.N_grid*global.N_grid;
    fwrite(&intholder,sizeof(int),1,moviefile);

    intholder = 0;
    fwrite(&intholder,sizeof(int),1,moviefile);

    for(i=0;i<global.N_grid;i++)
        for(j=0;j<global.N_grid;j++)
        {
            if (global.a[i][j] == global.predator) intholder = 2;
            else if (global.a[i][j] == global.prey) intholder = 3;
            else intholder = 1;

            fwrite(&intholder,sizeof(int),1,moviefile);
            intholder = i*global.N_grid+j;
            fwrite(&intholder,sizeof(int),1,moviefile);
            floatholder = (float)i;
            fwrite(&floatholder,sizeof(float),1, moviefile);
            floatholder = (float)j;
            fwrite(&floatholder,sizeof(float),1,moviefile);
            floatholder = 1.0;
            fwrite(&floatholder,sizeof(float),1,moviefile);
        }
}

void print_cellular_automata()
{
    system("@cls||clear");
    int i,j;
    for (i=0; i<global.N_grid; i++) {
        for (j=0; j<global.N_grid; j++)
            printf("%c ",global.a[i][j]);
        printf("\n");
    }
    printf("\n");
}

void run_simulation()
{
    while (global.step < 500 && global.N_predator > 0 && global.N_prey > 0)
    {
        /* print_cellular_automata(); */
        global.step ++;
        run_step();
        write_cmovie();
        printf("%d\t%d\t%d\n", global.step, global.N_prey, global.N_predator);
        /* sleep(1); */
    }
}

int main(int argc, const char * argv[])
{
    printf("#######################################\n");
    printf("##  Predator Prey Cellular Automata  ##\n");
    printf("#######################################\n");

    moviefile = fopen("test.mvi","wb");
    if (argc > 1) moviefile = fopen(argv[1],"wb");


    global.N_grid = 50;
    if (argc > 2) global.N_grid = atoi(argv[2]);
    global.N_prey = 500;
    if (argc > 3) global.N_prey = atoi(argv[3]);
    global.N_predator = 50;
    if (argc > 4) global.N_predator = atoi(argv[4]);

    global.pred_spawn_rate = 0.8;
    if (argc > 5) global.pred_spawn_rate = atof(argv[5])/100;
    global.pred_death_rate = 0.1;
    if (argc > 6) global.pred_death_rate = atof(argv[6])/100;
    global.prey_spawn_rate = 1.0;
    if (argc > 7) global.prey_spawn_rate = atof(argv[7])/100;
    global.prey_death_rate = 0.2;
    if (argc > 8) global.prey_death_rate = atof(argv[8])/100;

    printf("N_prey %d\n", global.N_prey);
    printf("N_predator %d\n", global.N_predator);
    printf("pred_spawn_rate %f\n", global.pred_spawn_rate);
    printf("pred_death_rate %f\n", global.pred_death_rate);
    printf("prey_spawn_rate %f\n", global.prey_spawn_rate);
    printf("prey_death_rate %f\n\n", global.prey_death_rate);


    init_cellular_automata();
    /* print_cellular_automata(); */

    printf("step\tprey\tpredators\n");
    printf("%d\t%d\t%d\n", global.step, global.N_prey, global.N_predator);
    run_simulation();

    fclose(moviefile);
    return 0;
}



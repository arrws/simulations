#include <stdio.h>
#include <stdlib.h>

#include "timing.h"
#include "global.h"
#include "init.h"

#include "core.h"
#include "verlet.h"
#include "pinning.h"

void write_cmovie_frame();

//runs the simulation for the required steps
void run_simulation()
{
    global.total_time = 100000;
    global.echo_time = 1000;
    global.echo_time = 1000000;
    global.movie_time = 100;

    rebuild_Verlet_list(); //build for the first time
    /* rebuild_pinning_grid(); //build for the first time */

    get_starting_time();
    for(global.time=0;global.time<global.total_time;global.time++)
    {

        /* calculate_external_forces_on_particles(); */
        /* calculate_pairwise_forces(); */
        /* move_particles(); */

        /* // pinning sites */
        /* adjust_pinningsite_directions(); */
        /* rotate_pinningsite_directions(); */
        /* calculate_external_forces_on_pinningsites(); */
        /* move_pinningsites(); */
        /* rebuild_pinning_grid(); */
        /* move_particles(); */

        // verlet lists
        calculate_external_forces_on_particles();
        calculate_verlet_pairwise_forces();
        move_particles();
        check_Verlet_rebuild_condition_and_set_flag();
        if (global.flag_to_rebuild_Verlet==1)
            //one particle moved enough to rebuild the Verlet list
            rebuild_Verlet_list();


        //echo time
        if (global.time % global.echo_time == 0)
        {
            printf("Timestep: %d / %d\n",global.time,global.total_time);
            fflush(stdout);
        }

        //movie write time
        if (global.time % global.movie_time == 0)
            write_cmovie_frame();

    }

    get_finishing_time();
    echo_running_time();
}


void write_cmovie_frame()
{
    int i;
    float floatholder;
    int intholder;

    intholder = global.N_particles;
    fwrite(&intholder,sizeof(int),1,global.moviefile);

    intholder = global.time;
    fwrite(&intholder,sizeof(int),1,global.moviefile);

    for (i=0;i<global.N_particles;i++)
    {
        intholder = global.particle_color[i];
        fwrite(&intholder,sizeof(int),1,global.moviefile);
        intholder = i;//ID
        fwrite(&intholder,sizeof(int),1,global.moviefile);
        floatholder = (float)global.particle_x[i];
        fwrite(&floatholder,sizeof(float),1, global.moviefile);
        floatholder = (float)global.particle_y[i];
        fwrite(&floatholder,sizeof(float),1, global.moviefile);
        floatholder = 1.0;//cum_disp, cmovie format
        fwrite(&floatholder,sizeof(float),1,global.moviefile);
    }

}

int main(int argc, const char * argv[])
{
    printf("######################################\n");
    printf("##   Molecular Dynamics Simulation  ##\n");
    printf("##  Lane Formation + Pinning Sites  ##\n");
    printf("######################################\n\n");

    global.moviefile = fopen("test.mvi","wb");

    if (argc > 1) global.N_particles = atoi(argv[1]);
    if (argc > 2) global.moviefile = fopen(argv[2],"wb");

    init_simulation();
    init_simulation_box();

    /* init_pinningsites(); */

    init_particles();

    run_simulation();

    return 0;
}



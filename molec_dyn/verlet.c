#include "verlet.h"
#include "global.h"
#include <stdlib.h>
#include <math.h>

#include "core.h"

#define PI 3.1415926535


void check_Verlet_rebuild_condition_and_set_flag()
{
int i;
double dr2;

//check if any particle moved (potentially) enough to enter the inner Verlet shell
//coming from the outside, if one did, rebuild the Verlet lists
global.flag_to_rebuild_Verlet = 0;

for(i=0;i<global.N_particles;i++)
        {
        dr2 = global.particle_dx_so_far[i] * global.particle_dx_so_far[i] +
                global.particle_dy_so_far[i] * global.particle_dy_so_far[i];

        //if (i==0) printf("%d %lf\n",global.time,dr2);fflush(stdout);

        if (dr2>=global.Verlet_intershell_squared)
            {
            global.flag_to_rebuild_Verlet = 1;
            break; //exit the for cycle
            }
        }

}



void calculate_verlet_pairwise_forces()
{
int ii,i,j;
double r,r2,f;
double dx,dy;

for(ii=0;ii<global.N_Verlet;ii++)
    {
    //obtain the i,j from the Verlet list
    i = global.Verletlisti[ii];
    j = global.Verletlistj[ii];

    //perform the pairwise force calculation
    distance_squared_folded_PBC(global.particle_x[i],global.particle_y[i],
            global.particle_x[j],global.particle_y[j],&r2,&dx,&dy);

    //non-tabulated version
    //try to not divide just multiply division is costly
    r = sqrt(r2);
    if (r<0.2)
        {
        printf("WARNING:PARTICLES TOO CLOSE. LOWER FORCE USED\n");
        f = 100.0;
        }
    else
        {
        f = 1/r2 * exp(-r * global.partile_particle_screening_wavevector);
        //if (r<1.0) printf("r=%lf f=%lf\n",r,f);
        }

    //division and multiplication for projection to the x,y axes

    f = f/r;
    //if (r<1.0) printf("%f/r=lf fx=%lf fy=%lf\n\n",f,f*dx,f*dy);

    global.particle_fx[i] -= f*dx;
    global.particle_fy[i] -= f*dy;

    global.particle_fx[j] += f*dx;
    global.particle_fy[j] += f*dy;
    }

}



//rebuilds the Verlet list
void rebuild_Verlet_list()
{
int i,j;
double dr2,dx,dy;
double estimation;

//initialize the Verlet list for the first time
if (global.N_Verlet_max==0)
    {
    //we are building the Verlet list for the first time in the simulation
    printf("Verlet list will be built for the first time\n");

    estimation = global.N_particles/(double)global.SX/(double)global.SY;
    printf("System density is %.3lf\n",estimation);

    estimation *= PI * global.Verlet_cutoff_distance * global.Verlet_cutoff_distance;
    printf("Particles in a R = %.2lf shell = %lf\n",
        global.Verlet_cutoff_distance,estimation);

    global.N_Verlet_max = (int)estimation * global.N_particles / 2;
    printf("Estimated N_Verlet_max = %d\n",global.N_Verlet_max);

    global.Verletlisti = (int *) malloc(global.N_Verlet_max * sizeof(int));
    global.Verletlistj = (int *) malloc(global.N_Verlet_max * sizeof(int));
    }

//build the Verlet list
global.N_Verlet = 0;

for(i=0;i<global.N_particles;i++)
    {
    for(j=i+1;j<global.N_particles;j++)
        {
        distance_squared_folded_PBC(global.particle_x[i],global.particle_y[i],
            global.particle_x[j],global.particle_y[j],&dr2,&dx,&dy);

        //if (global.time==0)
        //    if ((i==150)||(j==150)) printf("(%d %d %lf)\n",i,j,dr2);

        if (dr2<36.0)
            {
            global.Verletlisti[global.N_Verlet] = i;
            global.Verletlistj[global.N_Verlet] = j;

            //if (global.time==0)
            //if ((i==150)||(j==150)) printf("(%d %d)\n",i,j);

            global.N_Verlet++;
            if (global.N_Verlet>=global.N_Verlet_max)
                {
                printf("Verlet list reallocated from %d\n",global.N_Verlet_max);
                global.N_Verlet_max = (int)(1.1*global.N_Verlet);
                global.Verletlisti = (int *) realloc(global.Verletlisti ,global.N_Verlet_max * sizeof(int));
                global.Verletlistj = (int *) realloc(global.Verletlistj ,global.N_Verlet_max * sizeof(int));
                printf("New Verlet list max size = %d\n",global.N_Verlet_max);
                }
            }
        }
    }

/* printf("Counted Verlet list lenght = %d\n",global.N_Verlet); */
fflush(stdout);

global.flag_to_rebuild_Verlet = 0;
for(i=0;i<global.N_particles;i++)
    {
    global.particle_dx_so_far[i] = 0.0;
    global.particle_dy_so_far[i] = 0.0;
    }

}




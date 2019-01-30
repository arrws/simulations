#ifndef global_h
#define global_h

#include <stdio.h>

struct global_struct
{
    double SX, SY;
    double halfSX,halfSY;

    int N_pinningsites;
    double *pinningsite_x;
    double *pinningsite_y;
    double *pinningsite_fx;
    double *pinningsite_fy;
    int *pinningsite_color;
    double *pinningsite_direction_x;
    double *pinningsite_direction_y;
    double *pinningsite_dx_so_far;
    double *pinningsite_dy_so_far;
    double *pinningsite_R;
    double pinningsite_setradius;
    double pinningsite_grid_dx;
    double pinningsite_grid_dy;
    int Nx_pinningsite_grid;
    int Ny_pinningsite_grid;
    int **pinningsite_grid;

    double pinning_lattice_constant;
    double pinning_driving_force;
    int pinning_direction_change;

    int     N_particles;
    double  *particle_x;                        //particle x position
    double  *particle_y;                        //particle y position
    double  *particle_fx;                       //particle total force x direction
    double  *particle_fy;                       //particle total force y direction
    int     *particle_color;                    //particle color
    double  *particle_direction;                //direction of external force

    double  particle_driving_force;             //external driving force
    double  particle_particle_screening_length;  //inter-partcile force screening length
    double *particle_direction_x;
    double *particle_direction_y;

    double *particle_dx_so_far;
    double *particle_dy_so_far;

    double partile_particle_screening_length;
    double partile_particle_screening_wavevector;

    int N_Verlet;
    int N_Verlet_max; //initial allocation + later, longest allocation
    int *Verletlisti;
    int *Verletlistj;
    int flag_to_rebuild_Verlet;

    double Verlet_cutoff_distance;
    double Verlet_cutoff_distance_squared;
    double Verlet_intershell_squared;


    double dt;          //simulation step length

    int total_time;     //total running time
    int echo_time;      //echo to screen
    int movie_time;     //write to file
    int time;           //current time step

    FILE *moviefile;
};

struct flag_struct
{
    short int system_size_SX_set;
    short int system_size_SY_set;
};

extern struct global_struct global;
extern struct flag_struct flag;

#endif


#include "pinning.h"
#include "core.h"
#include "global.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535

//change the direction of the pinning sites
//they will move on a circle
void rotate_pinningsite_directions()
{
double theta,sint,cost;
double newx,newy;
int i;

//theta  = 3.1415/180.0*0.005;
theta = global.pinning_driving_force * global.dt * 0.2857;
sint = sin(theta);
cost = cos(theta);

//printf("%lf %lf\n",sint,cost);

//rotation matrix
//cos(theta)*x -sin(theta)*y
//sin(theta)*x +cos(theta)*y

for(i=0;i<global.N_particles;i++)
    {
     newx = global.particle_direction_x[i] * cost - global.particle_direction_y[i] * sint;
     newy = global.particle_direction_x[i] * sint + global.particle_direction_y[i] * cost;

    global.particle_direction_x[i] = newx;
    global.particle_direction_y[i] = newy;
    }

//printf("%lf %lf\n",global.particle_direction_x[i],global.particle_direction_y[i]);

}


//change the direction of the pinning sites
//they will move on a triangle
void adjust_pinningsite_directions()
{
int i,k;

float val = global.pinningsite_dx_so_far[0]*global.pinningsite_dx_so_far[0] + global.pinningsite_dy_so_far[0]*global.pinningsite_dy_so_far[0];


if ( val>= global.pinning_lattice_constant * global.pinning_lattice_constant * 1.0)
      {

      //change directions now
      for(k=0;k<global.N_pinningsites;k++)
        switch ( (global.pinningsite_color[k]-2 + global.pinning_direction_change)%3 )
            {
            case 0: {
                    global.pinningsite_direction_x[k] = - 0.5;
                    global.pinningsite_direction_y[k] = - sqrt(3)/2.0;
                    break;
                    }
            case 1: {
                    global.pinningsite_direction_x[k] = 1.0;
                    global.pinningsite_direction_y[k] = 0.0;
                    break;
                    }
            case 2: {
                    global.pinningsite_direction_x[k] = - 0.5;
                    global.pinningsite_direction_y[k] = + sqrt(3)/2.0;
                    break;
                    }
            }

      global.pinning_direction_change++;

      for(i=0;i<global.N_pinningsites;i++)
        {
        global.pinningsite_dx_so_far[i] = 0.0;
        global.pinningsite_dy_so_far[i] = 0.0;
        }

      }


}


void calculate_external_forces_on_pinningsites()
{
int i;

for(i=0;i<global.N_pinningsites;i++)
    {
    global.pinningsite_fx[i] += global.pinningsite_direction_x[i] * global. pinning_driving_force;
    global.pinningsite_fy[i] += global.pinningsite_direction_y[i] * global. pinning_driving_force;
    }
}



//moves the pinning sites one time step
void move_pinningsites()
{

int i;
double dx,dy;

for(i=0;i<global.N_pinningsites;i++)
    {
    dx = global.pinningsite_fx[i] * global.dt;
    dy = global.pinningsite_fy[i] * global.dt;

    global.pinningsite_x[i] += dx;
    global.pinningsite_y[i] += dy;

    global.pinningsite_dx_so_far[i] += dx;
    global.pinningsite_dy_so_far[i] += dy;

    fold_pinningsite_back_PBC(i);

    global.pinningsite_fx[i] = 0.0;
    global.pinningsite_fy[i] = 0.0;
    }
}

void fold_pinningsite_back_PBC(int i)
{

//fold back the pinningsite into the pBC simulation box
//assumes it did not jump more thana  box length
//if it did the simulation is already broken anyhow

if (global.pinningsite_x[i]<0) global.pinningsite_x[i] += global.SX;
if (global.pinningsite_y[i]<0) global.pinningsite_y[i] += global.SY;
if (global.pinningsite_x[i]>=global.SX) global.pinningsite_x[i] -= global.SX;
if (global.pinningsite_y[i]>=global.SY) global.pinningsite_y[i] -= global.SY;
}


void rebuild_pinning_grid()
{
int i,j;
int gi,gj;

if (global.pinningsite_grid==NULL)
    {
    //build the pinningsite grid for the first time;
    global.Nx_pinningsite_grid = (int) (global.SX/global.pinningsite_setradius) + 1;
    global.Ny_pinningsite_grid = (int) (global.SY/global.pinningsite_setradius) + 1;
    printf("Pinning sites grid is %d x %d\n",global.Nx_pinningsite_grid,global.Ny_pinningsite_grid);
    global.pinningsite_grid_dx = global.SX/global.Nx_pinningsite_grid;
    global.pinningsite_grid_dy = global.SX/global.Ny_pinningsite_grid;
    printf("Pinning sites cell is %.2lf x %.2lf\n", global.pinningsite_grid_dx, global.pinningsite_grid_dy);
    printf("Pinning sites radius is = %.2lf\n",global.pinningsite_setradius);

    //initialize the grid
    global.pinningsite_grid = (int **) malloc(global.Nx_pinningsite_grid * sizeof(int *));
    for(i=0;i<global.Nx_pinningsite_grid;i++)
        global.pinningsite_grid[i] = (int *) malloc(global.Ny_pinningsite_grid * sizeof(int));
    }

//always do this - zero the values
for(i=0;i<global.Nx_pinningsite_grid;i++)
    for(j=0;j<global.Ny_pinningsite_grid;j++)
        global.pinningsite_grid[i][j] = -1;

//always do this - fill up the values
for(i=0;i<global.N_pinningsites;i++)
    {
    gi = (int) global.pinningsite_x[i]/global.pinningsite_grid_dx;
    gj = (int) global.pinningsite_y[i]/global.pinningsite_grid_dy;

    /*if ((gi>=global.Nx_pinningsite_grid)||(gj>=global.Ny_pinningsite_grid))
        {
        printf("Out of bounds pinningsite\n");
        exit(1);
        }*/
    //this cannot fail (hopefully)
    global.pinningsite_grid[gi][gj] = i;
    }

}


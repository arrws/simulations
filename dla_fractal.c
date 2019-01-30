#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_max 1000
#define PI 3.141592653579892

int grid[N_max][N_max];
int N_grid;

double R_max = 5.0; // maximum radius of the crystal
int randomwalker_x, randomwalker_y; // the random walker's position
double randomwalker_R;  // random walker's distance from the center
double stick_prob = 0.5;
double gyration;

int N_particles;

int t;

FILE *moviefile;

void write_cmovie();

void init_grid()
{
    int i,j;

    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
            grid[i][j] = 0;

    grid[N_grid/2][N_grid/2] = 1;
    N_particles = 1;
}


void init_randomwalker()
{
    double theta;
    if (( (double)N_grid/2 + 3.0*R_max ) > (double) N_grid )
    {
        printf("Cannot create any more random walkers");
        exit(1);
    }
    randomwalker_R = (R_max + 5.0);
    theta = 2*PI*rand()/(RAND_MAX+1.0);
    randomwalker_x = N_grid/2 + (int)floor(randomwalker_R * cos(theta));
    randomwalker_y = N_grid/2 + (int)floor(randomwalker_R * sin(theta));

    /* randomwalker_x = N_grid/2; */
    /* randomwalker_y = N_grid/2; */
}

void move_randomwalker()
{
    double r;
    int tempx, tempy;
    tempx = randomwalker_x;
    tempy = randomwalker_y;

    r = rand()/(RAND_MAX+1.0);

    if (r<0.25)         tempx++;   //right
    else if (r<0.5)     tempy++;   //up
    else if (r<0.75)    tempx--;   //left
    else                tempy--;   //down

    if (grid[tempx][tempy]==0)
    {
        randomwalker_x = tempx;
        randomwalker_y = tempy;
    }
}

void does_it_stick()
{
    double R_max_candidate;
    double dx,dy;

    double r;

    r = rand()/(RAND_MAX+1.0);

    if (r < stick_prob) {
        //if it has a neighbor grid site that is occupied
        //nearest neighbor (right, left,up,down)
        // grid[randomwalker_x+1][randomwalker_y+1]
        //would be next nearest neighbor
        if ((grid[randomwalker_x+1][randomwalker_y]==1)||
            (grid[randomwalker_x-1][randomwalker_y]==1)||
            (grid[randomwalker_x][randomwalker_y+1]==1)||
            (grid[randomwalker_x][randomwalker_y-1]==1))
        {
            //particle got stuck on the growing crystal
            grid[randomwalker_x][randomwalker_y] = 1;
            N_particles++;
            write_cmovie();

            dx = (randomwalker_x-(N_grid/2));
            dy = (randomwalker_y-(N_grid/2));

            R_max_candidate = dx*dx + dy*dy;

            if (R_max_candidate > R_max*R_max)
                R_max = sqrt(R_max_candidate);

            init_randomwalker();
        }
    }

}


int the_random_walker_is_lost()
{
    double dx,dy, dr2;
    dx  = randomwalker_x - (N_grid/2.0);
    dy  = randomwalker_y - (N_grid/2.0);
    dr2 = dx*dx + dy*dy;
    if (dr2>9.0*R_max*R_max)
        return 1;
    return 0;
}

void compute_gyration()
{
    int i,j;
    int gyr_sum=0;

    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
            if (grid[i][j] == 1)
                gyr_sum += sqrt( (i-N_grid/2)*(i-N_grid/2) + (j-N_grid/2)*(j-N_grid/2) );
    gyration = gyr_sum/N_particles;
}

void write_cmovie(void)
{
    int i,j,k;
    float floatholder;
    int intholder;

    intholder = N_particles;
    fwrite(&intholder,sizeof(int),1,moviefile);

    intholder = t;
    fwrite(&intholder,sizeof(int),1,moviefile);

    float xsmall = 2.0;

    k=1;
    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
            if (grid[i][j])
            {
                intholder = 3; //color of spin
                fwrite(&intholder,sizeof(int),1,moviefile);
                intholder = k++; //spin ID
                fwrite(&intholder,sizeof(int),1,moviefile);
                floatholder = (float)i / xsmall;
                fwrite(&floatholder,sizeof(float),1, moviefile);
                floatholder = (float)j / xsmall;
                fwrite(&floatholder,sizeof(float),1,moviefile);
                floatholder = 1.0;//cum_disp, cmovie format
                fwrite(&floatholder,sizeof(float),1,moviefile);
        }
}

int main(int argc, const char * argv[]) {

    printf("#####################################################\n");
    printf("##  Diffusion Limited Aggregation Crystal Fractal  ##\n");
    printf("#####################################################\n\n");

    moviefile = fopen("test.mvi","wb");

    N_grid = 150;
    stick_prob = 0.5;
    if (argc > 1) stick_prob = atof(argv[1])/100;
    if (argc > 2) N_grid = atof(argv[2]);
    if (argc > 3) moviefile = fopen(argv[3],"wb");
    printf("N_grid = %d\nstick_prob = %f\n", N_grid, stick_prob);

    init_grid();
    init_randomwalker();

    printf("\nRun started\n");
    printf("Step\tN_particles\tGyration\n");

    for(t=0;t<5000000;t++)
        {
            if (t%10000==0) {
                compute_gyration();
                printf("%d\t%d\t%f\n", t, N_particles, gyration);
            }

            move_randomwalker();
            if (the_random_walker_is_lost())
                init_randomwalker();
            does_it_stick();
        }

    fclose(moviefile);
    return 0;
}

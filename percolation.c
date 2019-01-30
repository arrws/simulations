#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_max 1000

int N_grid;
double  p; ///probability of picking the site

int grid[N_max][N_max];
int cluster_number[N_max][N_max];
int actual_cluster;
int N_particles;

FILE *moviefile;
int t;

void initialize_system()
{
    int i,j;
    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
        {
            grid[i][j] = 0; //have not picked any sites
            cluster_number[i][j] = -1;//nobody is in a cluster
        }
}

void fill_system_with_probability(double p)
{
    int i,j;
    double r;
    N_particles = 0;
    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
        {
            cluster_number[i][j] = -1;
            r = rand()/(RAND_MAX+1.0);
            //if r<p, this site will be filled
            if (r<p)
            {
                grid[i][j] = 1;
                N_particles++;
            }
        }
    /* printf("filled grid with %d particles \n",N_particles); */
}

int recursive_clusternumber(int i,int j)
{
    int n = 1; // united n more cells
    cluster_number[i][j] = actual_cluster;

    if ((i+1<N_grid))
        //find a position to the right of the actual position
        if ((cluster_number[i+1][j]==-1)&&(grid[i+1][j]==1))
            n += recursive_clusternumber(i+1,j);
        //find a position to the left
    if ((i-1>=0))
        if ((cluster_number[i-1][j]==-1)&&(grid[i-1][j]==1))
            n += recursive_clusternumber(i-1,j);
        //up
    if ((j+1<N_grid))
        if ((cluster_number[i][j+1]==-1)&&(grid[i][j+1]==1))
            n += recursive_clusternumber(i,j+1);
        //down
    if ((j-1>=0))
        if ((cluster_number[i][j-1]==-1)&&(grid[i][j-1]==1))
            n += recursive_clusternumber(i,j-1);

    return n;
}

int max(int x, int y) { if (x>y) return x; return y; }

void clusterize_system()
{
    int i,j;
    int max_cluster = 0, cluster_size;
    actual_cluster = 1;
    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
        {
            //filled position, it's not in any cluser
            if ((grid[i][j]==1) && (cluster_number[i][j]==-1))
            {
                //start the recursive algorithm
                //to find everybody connected to this point
                cluster_size = recursive_clusternumber(i,j);
                max_cluster = max(cluster_size, max_cluster);
                //the next cluster is going to
                //be a bigger number
                actual_cluster++;
            }
        }
    actual_cluster--;
    printf("%d\t%d\t%d\n",N_particles, actual_cluster, max_cluster);
}

void write_cmovie()
{
    int i,j;
    float floatholder;
    int intholder;

    intholder = N_grid*N_grid;
    fwrite(&intholder,sizeof(int),1,moviefile);

    intholder = t;
    fwrite(&intholder,sizeof(int),1,moviefile);

    for(i=0;i<N_grid;i++)
        for(j=0;j<N_grid;j++)
        {
            //color the particles based on which
            //cluster they belong to
            if (grid[i][j]==0) intholder = 2;
            else intholder = 3 + (cluster_number[i][j]%10);
            fwrite(&intholder,sizeof(int),1,moviefile);
            intholder = i*N_grid+j;            //spin ID
            fwrite(&intholder,sizeof(int),1,moviefile);
            floatholder = (float)i;
            fwrite(&floatholder,sizeof(float),1, moviefile);
            floatholder = (float)j;
            fwrite(&floatholder,sizeof(float),1,moviefile);
            floatholder = 1.0;//cum_disp, cmovie format
            fwrite(&floatholder,sizeof(float),1,moviefile);
        }
}


int main(int argc, const char * argv[]) {
    printf("#####################################\n");
    printf("##  Percolation Cluser Simulation  ##\n");
    printf("#####################################\n\n");

    moviefile = fopen("test.mvi","wb");

    N_grid = 100;
    p = 0.3;
    if (argc > 1) p = atof(argv[1])/100;
    if (argc > 2) N_grid = atof(argv[2]);
    if (argc > 3) moviefile = fopen(argv[3],"wb");
    printf("N_grid = %d\nprob = %f\n", N_grid, p);

    printf("\nRun started\n");
    printf("\nN_particles\tN_clusters\tmax_size\n");

    /* for(t=0;t<100;t++) */
    for(t=0;t<10;t++)
    {
        //srand(1446742268);
        int seed = (int)time(NULL)+t*10;
        /* printf("%d seed=%d\n",t,seed); */
        srand(seed);

        initialize_system();
        fill_system_with_probability(p);
        //right here I can calculate statistics
        // - size of the largest cluster (averaged)
        // - probability of a spanning cluster in the system
        clusterize_system();
        write_cmovie();
    }

    fclose(moviefile);
    return 0;
}



#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int **adjacency;
int *degree;
int N_nodes;
int N_links;

void initialize_adj();
void create_random_links();

void initialize_adj()
{
    int i,j;

    adjacency = (int **)malloc(N_nodes*sizeof(int *));
    for(i=0;i<N_nodes;i++)
        adjacency[i] = (int *)malloc(N_nodes*sizeof(int));

    for(i=0;i<N_nodes;i++)
        for(j=0;j<N_nodes;j++)
            adjacency[i][j] = 0;
}

//create an Erdos-Renyi (random) network
void create_random_links()
{
    int i,j;
    int N_links_placed = 0;
    //assume all nodes are present right from the start
    while (N_links_placed<N_links)
    {
        i = (int)floor((double)N_nodes * rand()/(RAND_MAX+1.0));
        j = (int)floor((double)N_nodes * rand()/(RAND_MAX+1.0));
        if ((i!=j) && (adjacency[i][j]!=1))
        {
            adjacency[i][j] = 1;
            adjacency[j][i] = 1;
            N_links_placed++;
        }
    }

}

//Albert-Barabasi scale free network
void create_scale_free_links()
{
    int i,j;
    int average_brought_in;
    int N_nodes_added;
    int total_sum_of_degrees;

    int pick_number;
    int sum_so_far;

    average_brought_in = (int)floor(2.0*(double)N_links/(double)N_nodes);
    printf("links per node = %d\n",average_brought_in);

    //make a small completely connected core
    for(i=0;i<average_brought_in;i++)
        for(j=0;j<average_brought_in;j++) {
        adjacency[i][j] = 1;
        adjacency[j][i] = 1;
        }

    //now we do preferential attachment
    degree = (int *)malloc(N_nodes * sizeof(int));
    total_sum_of_degrees = 0;
    for(i=0; i<average_brought_in; i++) {
        degree[i] = average_brought_in;
        total_sum_of_degrees += degree[i];
    }
    /* printf("total sum of degrees = %d\n",total_sum_of_degrees); */

    N_nodes_added = average_brought_in + 1;

    while (N_nodes_added < (N_nodes-1))
    {
        for(i=0;i<average_brought_in;i++)
        {
            //has to pick a node to connect to
            pick_number = (int)floor((double)total_sum_of_degrees*rand()/(RAND_MAX+1.0));

            //printf("picked number = %d of %d\n",pick_number,total_sum_of_degrees);fflush(stdout);
            //to figure out whom to link to I sum up the
            //ki until I find the node
            sum_so_far = 0;
            for(j=0;j<N_nodes_added-1;j++) {
                //printf("%d ",j);fflush(stdout);
                sum_so_far +=degree[j];
                if ((sum_so_far<pick_number)&&(sum_so_far+degree[j+1]>=pick_number)) break;
            }
            //j is the node to link to
            /* printf("the node to link to is = %d\n",j); */
            /* printf("N_nodes_added = %d\n",N_nodes_added); */
            /* fflush(stdout); */

            //N_nodes_added is linking
            adjacency[j][N_nodes_added] = 1;
            adjacency[N_nodes_added][j] = 1;
            degree[j] +=1;
            degree[N_nodes_added] +=1;
            total_sum_of_degrees +=2;

            N_nodes_added++;
            if (N_nodes_added > N_nodes-1) break;
        }
    }
}

int max(int x, int y) { if (x>y) return x; return y; }

void calculate_degree_distribution()
{
    printf("\nDegree\tNum\n");
    int i,j;
    int d, max_degree=0;
    degree = (int *)malloc(N_nodes * sizeof(int));
    for(i=0;i<N_nodes;i++)
    {
        d = 0;
        for(j=0;j<N_nodes;j++)
            if (adjacency[i][j] == 1)
                d ++;
        max_degree = max(d, max_degree);
        degree[d] ++;
    }
    for(i=1;i<=max_degree;i++)
        printf("%d\t%d\n",i, degree[i]);
}


int main(int argc, const char * argv[])
{
    printf("##################################\n");
    printf("##  Complex Network Generation  ##\n");
    printf("##################################\n\n");

    N_nodes = 1000;
    if (argc > 1) N_nodes = atoi(argv[1]);
    N_links = 5000;
    if (argc > 2) N_links = atoi(argv[2]);
    printf("N_nodes = %d\nN_links = %d\n", N_nodes, N_links);

    printf("\nRun started\n");
    initialize_adj();
    if (argc > 3)
        create_random_links();
    else
        create_scale_free_links();
    calculate_degree_distribution();

    printf("\nGRAPH\n");
    int i,j;
    for(i=0;i<N_nodes;i++)
        for(j=0;j<N_nodes;j++)
            if (adjacency[i][j] == 1)
                printf("%d -> %d;\n", i, j);

    return 0;
}


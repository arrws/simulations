#ifndef init_h
#define init_h

#include <stdio.h>
#include <stdlib.h>

void init_simulation(void);
void init_simulation_box(void);

void init_particles(void);
void init_particles_randomly(void);

void init_particles_square_lattice(void);
void init_particles_triangular_lattice(void);

void init_pinningsites(void);
void init_pinningsites_square_lattice(void);
void init_pinningsites_triangular_lattice(void);

void set_direction_by_color(int k, int color);
double distance_folded_PBC(double x0,double y0,double x1,double y1);

#endif /* init_h */

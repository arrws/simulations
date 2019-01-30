#ifndef pinning_h
#define pinning_h

#include <stdio.h>

void calculate_external_forces_on_pinningsites(void);
void move_pinningsites(void);
void fold_pinningsite_back_PBC(int i);
void rebuild_pinning_grid(void);
void adjust_pinningsite_directions(void);
void rotate_pinningsite_directions(void);

#endif /* pinning_h */

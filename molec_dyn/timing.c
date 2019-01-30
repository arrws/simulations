#include <stdio.h>
#include "timing.h"
#include "global.h"

struct timespec program_start_time;
struct timespec program_finish_time;

void get_starting_time() { clock_gettime(CLOCK_MONOTONIC, &program_start_time); }

void get_finishing_time() { clock_gettime(CLOCK_MONOTONIC, &program_finish_time); }

void echo_running_time()
{
    double time_expired;
    time_t time_endtime;
    struct tm *timeinfo;

    time_expired  = program_finish_time.tv_sec - program_start_time.tv_sec + (program_finish_time.tv_nsec - program_start_time.tv_nsec)*1e-9;
    time(&time_endtime);
    timeinfo = localtime(&time_endtime);

    printf("Run finished on: %s",asctime(timeinfo));
    printf("Running Time: %.2lf seconds\n",time_expired);
}


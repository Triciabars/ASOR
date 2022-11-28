#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char *argv[]){

    pid_t pid = atoi(argv[1]);
    struct sched_param p;
    sched_getparam(pid, &p);
     int polplanification = sched_getscheduler(pid);
    if(polplanification == 1) {
            printf("Planificación: %s\n", "SCHED_FIFO");
    }else if(polplanification == 3) {
                printf("Planificación: %s\n", "SCHED_BATCH");
    } else if(polplanification == 5) {
            printf("Planificación: %s\n", "SCHED_IDLE");
    } else if(polplanification == 0) {
            printf("Planificación: %s\n", "SCHED_OTHER");
    } else if(polplanification == 2) {
            printf("Planificación: %s\n", "SCHED_RR");
    }
    printf("Prioridad: %i\n", p.sched_priority);
    int maxprio = sched_get_priority_max(polplanification);
    int minprio = sched_get_priority_min(polplanification);
    printf("Mínimo y máximo de politica de prioridad: %i-%i\n", minprio,maxprio);
    return 0;
}

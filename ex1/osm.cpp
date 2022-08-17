#include <iostream>
#include "osm.h"
#include <sys/time.h>

#define NUM_OPS_IN_ITER 5
#define NUM_TO_ADD 5
#define SEC_TO_NSEC 1000000000
#define USEC_TO_NSEC 1000


double osm_operation_time(unsigned int iterations){
    if (iterations == 0){
        return -1;
    }
    struct timeval before, after;
    gettimeofday(&before, NULL);
    for (int i = 0; i< iterations; i+=NUM_OPS_IN_ITER){
        int a = NUM_TO_ADD+NUM_TO_ADD;
        int a1 = NUM_TO_ADD+NUM_TO_ADD;
        int a2 = NUM_TO_ADD+NUM_TO_ADD;
        int a3 = NUM_TO_ADD+NUM_TO_ADD;
        int a4 = NUM_TO_ADD+NUM_TO_ADD;
    }
    gettimeofday(&after, NULL);
    double diff1 = ((double)after.tv_usec-(double)before.tv_usec)*USEC_TO_NSEC;
    double diff2 = ((double)after.tv_sec-(double)before.tv_sec)*SEC_TO_NSEC;
    double result = (diff1+diff2)/iterations;
    return result;
}

void nothing_func(){}

double osm_function_time(unsigned int iterations){
    if (iterations == 0){
        return -1;
    }
    struct timeval before, after;
    gettimeofday(&before, NULL);
    for (int i = 0; i< iterations; i+=NUM_OPS_IN_ITER){
        nothing_func();
        nothing_func();
        nothing_func();
        nothing_func();
        nothing_func();
    }
    gettimeofday(&after, NULL);
    double diff1 = ((double)after.tv_usec-(double)before.tv_usec)*USEC_TO_NSEC;
    double diff2 = ((double)after.tv_sec-(double)before.tv_sec)*SEC_TO_NSEC;
    double result = (diff1+diff2)/iterations;
    return result;
}

double osm_syscall_time(unsigned int iterations){
    if (iterations == 0){
        return -1;
    }
    struct timeval before, after;
    gettimeofday(&before, NULL);
    for (int i = 0; i< iterations; i+=NUM_OPS_IN_ITER){
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }
    gettimeofday(&after, NULL);
    double diff1 = ((double)after.tv_usec-(double)before.tv_usec)*USEC_TO_NSEC;
    double diff2 = ((double)after.tv_sec-(double)before.tv_sec)*SEC_TO_NSEC;
    double result = (diff1+diff2)/iterations;
    return result;
}


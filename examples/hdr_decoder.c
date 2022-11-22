/**
 * hdr_decoder.c
 * Written by Michael Barker and released to the public domain,
 * as explained at http://creativecommons.org/publicdomain/zero/1.0/
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

#include <hdr/hdr_histogram.h>
#include <hdr/hdr_histogram_log.h>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

long get_mem_usage() {
    struct rusage myusage;
    getrusage(RUSAGE_SELF, &myusage);
    return myusage.ru_maxrss;
}
//static struct hdr_histogram* histogram = NULL;


int main()
{
    //srand(time(NULL));
    /* own test */
    long initial_usage = get_mem_usage();
    int i, value;
    // char* result;
    struct hdr_histogram* histogram;

    // lower bound: 0ms, upper bound: 900,000ms
    hdr_init(1, 9000000, 1, &histogram);


    for (i = 0; i < 100000; i++)
    {
        value = rand() % 9000000 + 1;
        hdr_record_value(histogram, value);
    }
    printf("rusage: %ld + %ld\n", initial_usage, get_mem_usage()-initial_usage);

    // SEE NUMBER OF buckets

    int mem = hdr_get_memory_size(histogram);
    printf("Footprint: %d \n", mem);

    printf("\nPercentiles Printing\n\n");
    hdr_percentiles_print(histogram,stdout,5,1.0,CLASSIC);

    printf("\n\nLogarithmic Printing\n");
    hdr_logarithmic_print(histogram,1);

    return 0;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

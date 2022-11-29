/**
 * yb_test.c
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

// long get_mem_usage() {
//     struct rusage myusage;
//     getrusage(RUSAGE_SELF, &myusage);
//     return myusage.ru_maxrss;
// }
//static struct hdr_histogram* histogram = NULL;


int main()
{
    //srand(time(NULL));
    //long initial_usage = get_mem_usage();
    int i, value;
    // char* result;
    struct hdr_histogram* histogram;

    // lower bound: 0ms, upper bound: 900,000ms
    hdr_init(1, 9000000, 2, &histogram);


    for (i = 0; i < 100; i++)
    {
        value = rand() % 9000000 + 1;
        hdr_record_value_atomic(histogram, value);
    }

    //printf("rusage: %lld + %lld\n", initial_usage, get_mem_usage()-initial_usage);

    int p95 = hdr_value_at_percentile(histogram, 90.0);
    printf("p95: %d\n", p95);

    int mem = hdr_get_memory_size(histogram);
    printf("Footprint: %d \n", mem);

    printf("\nPercentiles Printing\n\n");
    hdr_percentiles_print(histogram,stdout,5,1.0);

    printf("\n\nLogarithmic Printing\n");

    const char* result = get_hdr_histogram(histogram,1);
    printf("%s", result);

    return 0;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

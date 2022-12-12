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


int main()
{
    //srand(time(NULL));
    int i, value;
    struct hdr_histogram* histogram = (struct hdr_histogram*) calloc(1, sizeof(struct hdr_histogram));;

    // lower bound: 1ms, upper bound: 900,000ms
    yb_hdr_init(1, 9000000, 2, histogram);
    hdr_set_auto_resize(histogram, true);

    for (i = 0; i < 100; i++)
    {
        value = rand() % 9000000 + 1;
        hdr_record_value(histogram, value);
    }

    printf("Counts: %d \n", histogram->counts_len);

    int mem = hdr_get_memory_size(histogram);
    printf("Footprint: %d \n", mem);

    printf("\nPercentiles Printing\n\n");
    hdr_percentiles_print(histogram,stdout,5,1.0);

    return 0;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

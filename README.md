HdrHistogram_c: 'C' port of High Dynamic Range (HDR) Histogram

HdrHistogram
----------------------------------------------
[![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/HdrHistogram/HdrHistogram?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Windows Build: ![AppVeyor](https://ci.appveyor.com/api/projects/status/github/HdrHistogram/HdrHistogram_c)
Linux Build: [![Build Status](https://semaphoreci.com/api/v1/mikeb01/hdrhistogram_c/branches/master/badge.svg)](https://semaphoreci.com/mikeb01/hdrhistogram_c)

This port contains a subset of the functionality supported by the Java
implementation.  The current supported features are:

* Standard histogram with 64 bit counts (32/16 bit counts not supported)
* All iterator types (all values, recorded, percentiles, linear, logarithmic)
* Histogram serialisation (encoding version 1.2, decoding 1.0-1.2)
* Reader/writer phaser and interval recorder

Features not supported, but planned

* Auto-resizing of histograms

Features unlikely to be implemented

* Double histograms
* Atomic/Concurrent histograms
* 16/32 bit histograms

# Simple Tutorial

## Recording values

```C
#include <hdr_histogram.h>

struct hdr_histogram* histogram;

// Initialise the histogram
hdr_init(
    1,  // Minimum value
    INT64_C(3600000000),  // Maximum value
    3,  // Number of significant figures
    &histogram)  // Pointer to initialise

// Record value
hdr_record_value(
    histogram,  // Histogram to record to
    value)  // Value to record

// Record value n times
hdr_record_values(
    histogram,  // Histogram to record to
    value,  // Value to record
    10)  // Record value 10 times

// Record value with correction for co-ordinated omission.
hdr_record_corrected_value(
    histogram,  // Histogram to record to
    value,  // Value to record
    1000)  // Record with expected interval of 1000.

// Print out the values of the histogram
hdr_percentiles_print(
    histogram,
    stdout,  // File to write to
    5,  // Granularity of printed values
    1.0,  // Multiplier for results
    CLASSIC);  // Format CLASSIC/CSV supported.
```

## More examples

For more detailed examples of recording and logging results look at the
[hdr_decoder](examples/hdr_decoder.c)
and [hiccup](examples/hiccup.c)
examples.  You can run hiccup and decoder
and pipe the results of one into the other.

```
$ ./examples/hiccup | ./examples/hdr_decoder
```

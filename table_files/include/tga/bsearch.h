#ifndef _TGA_BSEARCH
#define _TGA_BSEARCH

#include <stdint.h>

/// Performs binary search in an array of unique values and returns the index of the
/// first element larger or equal to the value. returns size if not found.
inline int bsearch_geq(int64_t value, const int64_t* array, int size)
{
    int low = 0;
    int high = size;

    while (low+1 < high) {
        int mid = (low + high) >> 1;
        if (array[mid] < value) low = mid;
        else if (array[mid] > value) high = mid;
        else return mid;
    }
    return high;
}

#endif
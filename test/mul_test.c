#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "minirsa.h"
#include "minirsa_test.h"

static int mult128_test_one(const uint64_t a, const uint64_t b, const uint64_t lo,const uint64_t hi)
{
    int ret = 0;
    uint64_t xa = a;
    uint64_t xb = b;
    uint64_t r1, r2;
    mnrs_mult128(xa, xb, &r1, &r2);

    if (r1 != lo || r2 != hi) {
        ret = -1;
    }
    return ret;
}

int mult128_test()
{
    int ret = 0;

    if (mult128_test_one(1, 1, 1, 0) != 0) {
        ret = -1;
    }
    else if (mult128_test_one(1ull<<32, 1ull<<32, 0, 1) != 0) {
        ret = -1;
    }
    else if (mult128_test_one(1ull<<32, 1ull<<32, 0, 1) != 0) {
        ret = -1;
    }
    else if (mult128_test_one(UINT32_MAX, UINT32_MAX, 0xfffffffe00000001ull, 0) != 0) {
        ret = -1;
    } 
    else if (mult128_test_one(UINT64_MAX, 2, UINT64_MAX -1, 1) != 0) {
        ret = -1;
    } 
    else if (mult128_test_one(UINT64_MAX, UINT64_MAX, 1, UINT64_MAX - 1) != 0) {
        ret = -1;
    }
    return ret;
}
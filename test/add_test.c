#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "minirsa.h"
#include "minirsa_test.h"

const uint64_t a1[] = { 1 };
const uint64_t b1[] = { 1 };
const uint64_t c1[] = { 2 };
const uint64_t a2[] = { 1 };
const uint64_t b2[] = { 1, 1 };
const uint64_t c2[] = { 2, 1 };
const uint64_t a3[] = { UINT64_MAX };
const uint64_t b3[] = { 1, 1 };
const uint64_t c3[] = { 0, 2 };
const uint64_t a4[] = { UINT64_MAX, UINT64_MAX };
const uint64_t b4[] = { 1 };
const uint64_t c4[] = { 0, 0, 1 };

static int add_test_one(int l_a, const uint64_t* a, int l_b, const uint64_t* b, int l_c, const uint64_t* c)
{
    int ret = 0;
    uint64_t r[64];

    if (l_c > 64) {
        ret = -1;
    }
    else {
        ret = mnrs_add(l_a, a, l_b, b, l_c, r);
        if (ret == 0) {
            ret = memcmp(r, c, sizeof(uint64_t) * l_c);
        }
    }
    return ret;
}

#define ADD_TEST(a,b,c) add_test_one((int)(sizeof(a)/sizeof(uint64_t)), a, \
                                     (int)(sizeof(b)/sizeof(uint64_t)), b, \
                                     (int)(sizeof(c)/sizeof(uint64_t)), c)

int add_test()
{
    int ret = 0;

    if (ADD_TEST(a1, b1, c1) != 0) {
        ret = -1;
    }
    else if (ADD_TEST(a2, b2, c2) != 0) {
        ret = -1;
    } 
    else if (ADD_TEST(a3, b3, c3) != 0) {
        ret = -1;
    } 
    else if (ADD_TEST(a4, b4, c4) != 0) {
        ret = -1;
    } 
    return ret;
}

static int subtract_test_one(int l_a, const uint64_t* a, int l_b, const uint64_t* b, int l_c, const uint64_t* c)
{
    int ret = 0;
    uint64_t r[64];

    if (l_c > 64) {
        ret = -1;
    }
    else {
        ret = mnrs_subtract(l_a, a, l_b, b, l_c, r);
        if (ret == 0) {
            ret = memcmp(r, c, sizeof(uint64_t) * l_c);
        }
    }
    return ret;
}

#define SUBTRACT_TEST(a,b,c) subtract_test_one((int)(sizeof(a)/sizeof(uint64_t)), a, \
                                               (int)(sizeof(b)/sizeof(uint64_t)), b, \
                                               (int)(sizeof(c)/sizeof(uint64_t)), c)

int subtract_test()
{
    int ret = 0;

    if (SUBTRACT_TEST(c1, a1, b1) != 0) {
        ret = -1;
    }
    else if (SUBTRACT_TEST(c2, a2, b2) != 0) {
        ret = -1;
    } 
    else if (SUBTRACT_TEST(c3, a3, b3) != 0) {
        ret = -1;
    } 
    else if (SUBTRACT_TEST(c4, a4, b4) != 0) {
        ret = -1;
    } 
    else if (SUBTRACT_TEST(c1, b1, a1) != 0) {
        ret = -1;
    }
    else if (SUBTRACT_TEST(c2, b2, a2) != 0) {
        ret = -1;
    } 
    else if (SUBTRACT_TEST(c3, b3, a3) != 0) {
        ret = -1;
    } 
    else if (SUBTRACT_TEST(c4, b4, a4) != 0) {
        ret = -1;
    } 
    return ret;
}

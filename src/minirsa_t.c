/* Copyright, etc. */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <minirsa.h>
#include <minirsa_test.h>

int main(argc, argv)
{
    int ret = 0;

    if (add_test() != 0) {
        printf("Add test fails.");
        ret = -1;
    }
    if (subtract_test() != 0) {
        printf("Subtract test fails.");
        ret = -1;
    }
    if (mult128_test() != 0) {
        printf("Mult128 test fails");
        ret = -1;
    }

    if (ret == 0){
        printf("All tests pass.");
    }
    exit(ret);
}
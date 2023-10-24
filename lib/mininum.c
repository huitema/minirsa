/* Basic "big num" library, containing the strict minimum necessary to 
 * implement RSA. The library models numbers as { uint64_t *, length }
 * using little endian notation.
 */
#include <stdint.h>
#include <minirsa.h>

int mnrs_add(int l_a, const uint64_t* a, int l_b, const uint64_t* b, int l_c, uint64_t* c)
{
    int ret = 0;

    if (l_b > l_a) {
        return mnrs_add(l_b, b, l_a, a, l_c, c);
    }
    else if (l_c < l_a) {
        return -1;
    }
    else {
        uint64_t overflow = 0;
        int i = 0;

        for (; i < l_b; i++) {
            uint64_t x = a[i];
            x += overflow;
            overflow = x < a[i];
            x += b[i];
            overflow |= x < b[i];
            c[i] = x;
        }
        for (; i < l_a; i++) {
            uint64_t x = a[i];
            x += overflow;
            overflow = x < a[i];
            c[i] = x;
        }
        if (overflow > 0) {
            if (l_c > i) {
                c[i++] = overflow;
            }
            else {
                ret = -1;
            }
        }
        for (; i < l_c; i++) {
            c[i] = 0;
        }
    }
    return ret;
}

int mnrs_subtract(int l_a, const uint64_t* a, int l_b, const uint64_t* b, int l_c, uint64_t* c)
{
    int ret = 0;

    uint64_t overflow = 0;
    int i = 0;

    for (; i < l_b; i++) {
        uint64_t x = a[i];
        x -= overflow;
        overflow = x > a[i];
        x -= b[i];
        overflow |= x > a[i];
        if (i < l_c) {
            c[i] = x;
        }
        else if (x != 0) {
            return -1;
        }
    }
    for (; i < l_a; i++) {
        uint64_t x = a[i];
        x -= overflow;
        overflow = x > a[i];
        if (i < l_c) {
            c[i] = x;
        }
        else if (x != 0) {
            return -1;
        }
    }
    if (overflow > 0) {
        return -1;
    }
    for (; i < l_c; i++) {
        c[i] = 0;
    }

    return 0;
}

#if defined(__GNUC__) && GCC_VERSION > 4
#define MNRS_U128 unsigned __int128
#elif defined MS_VER
#if defined UINT128_MAX

#endif
#endif


#if defined(__GNUC__) && GCC_VERSION > 4
void mnrs_mult128(uint64_t op1, uint64_t op2, uint64_t* lo, uint64_t *hi)
{
    unsigned __int128 x = op1;
    x *= op2;
    *lo = (uint64_t)(x & UINT64_MAX);
    *hi = (uint64_t)(x >> 64);
}
#elif defined(_WIN64)
#include <intrin.h>

void mnrs_mult128(uint64_t a, uint64_t b, uint64_t *lc, uint64_t *hc)
{

    *lc = _umul128(a, b, hc);
}
#else
void mnrs_mult128(uint64_t a, uint64_t b, uint64_t* lc, uint64_t* hc)
{
    uint64_t la = a & UINT32_MAX;
    uint64_t ha = a >> 32;
    uint64_t lb = b & UINT32_MAX;
    uint64_t hb = b >> 32;
    uint64_t lr = la * lb;
    uint64_t hr = ha * hb;
    uint64_t mab = ha * lb;
    uint64_t mba = hb * la;
    uint64_t mabl = mab << 32;
    uint64_t mbal = mba << 32;
    lr += mabl;
    if (lr < mabl) {
        hr += 1;
    }
    lr += mbal;
    if (lr < mbal) {
        hr += 1;
    }
    hr += (mab >> 32);
    hr += (mba >> 32);
    *lc = lr;
    *hc = hr;
}
#endif
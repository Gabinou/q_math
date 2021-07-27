#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "q_math.h"
/********************** 0.1 MICROSECOND RESOLUTION CLOCK **********************/
//  Modified from: https://gist.github.com/ForeverZer0/0a4f80fc02b96e19380ebb7a3debbee5
#if defined(__linux)
#  define MICROSECOND_CLOCK
#  define HAVE_POSIX_TIMER
#  include <time.h>
#  ifdef CLOCK_MONOTONIC
#     define CLOCKID CLOCK_MONOTONIC
#  else
#     define CLOCKID CLOCK_REALTIME
#  endif
#elif defined(__APPLE__)
#  define MICROSECOND_CLOCK
#  define HAVE_MACH_TIMER
#  include <mach/mach_time.h>
#elif defined(_WIN32)
#  define MICROSECOND_CLOCK
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

uint64_t get_ns() {
    static uint64_t is_init = 0;
#if defined(__APPLE__)
    static mach_timebase_info_data_t info;
    if (0 == is_init) {
        mach_timebase_info(&info);
        is_init = 1;
    }
    uint64_t now;
    now = mach_absolute_time();
    now *= info.numer;
    now /= info.denom;
    return now;
#elif defined(__linux)
    static struct timespec linux_rate;
    if (0 == is_init) {
        clock_getres(CLOCKID, &linux_rate);
        is_init = 1;
    }
    uint64_t now;
    struct timespec spec;
    clock_gettime(CLOCKID, &spec);
    now = spec.tv_sec * 1.0e9 + spec.tv_nsec;
    return now;
#elif defined(_WIN32)
    static LARGE_INTEGER win_frequency;
    if (0 == is_init) {
        QueryPerformanceFrequency(&win_frequency);
        is_init = 1;
    }
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (uint64_t)((1e9 * now.QuadPart) / win_frequency.QuadPart);
#endif
}
#ifdef MICROSECOND_CLOCK
double get_us() {
    return (get_ns() / 1e3);
}
#else
#  define FAILSAFE_CLOCK
#  define get_us() (((double)clock())/CLOCKS_PER_SEC*1e6) // [us]
#  define get_ns() (((double)clock())/CLOCKS_PER_SEC*1e9) // [ns]
#endif



/* MINCTEST - Minimal C Test Library - 0.2.0
*  ---------> MODIFIED FOR q_math <----------
* Copyright (c) 2014-2017 Lewis Van Winkle
*
* http://CodePlea.com
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgement in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __MINCTEST_H__
#define __MINCTEST_H__
/*****************************TEST GLOBALS*****************************/
FILE * globalf;
/* NB all tests should be in one file. */
static int ltests = 0;
static int lfails = 0;

/* Display the test results. */
#define lresults() do {\
    if (lfails == 0) {\
        dupprintf(globalf,"ALL TESTS PASSED (%d/%d)\n", ltests, ltests);\
    } else {\
        dupprintf(globalf,"SOME TESTS FAILED (%d/%d)\n", ltests-lfails, ltests);\
    }\
} while (0)

/* Run a test. Name can be any string to print out, test is the function name to call. */
#define lrun(name, test) do {\
    const int ts = ltests;\
    const int fs = lfails;\
    const clock_t start = clock();\
    dupprintf(globalf,"\t%-14s", name);\
    test();\
    dupprintf(globalf,"pass:%2d   fail:%2d   %4dms\n",\
            (ltests-ts)-(lfails-fs), lfails-fs,\
            (int)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)

/* Assert a true statement. */
#define lok(test) do {\
    ++ltests;\
    if (!(test)) {\
        ++lfails;\
        dupprintf(globalf,"%s:%d error \n", __FILE__, __LINE__);\
    }\
} while (0)

void dupprintf(FILE * f, char const * fmt, ...) { // duplicate printf
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
}

#endif /*__MINCTEST_H__*/


/*******************************CONSTANTS***************************/
#define ITERATIONS 100000

/*******************************ACTUAL TESTS***************************/
void test_log2() {
    lok(log2(0.0) == -INFINITY);
    lok(log2(0.0) == -INFINITY);
    lok(log2(0) == -INFINITY);
    lok(log2(0) == -INFINITY);
    lok(log2(1.0) == 0.0);
    lok(log2(1.0) == 0);
    lok(log2(2.0) == 1.0);
    lok(log2(2.0) == 1);
}

void test_q_math() {
    dupprintf(globalf, "test_q_math");
    dupprintf(globalf, "test_q_cycles");
    lok(q_cycle2_zp(0) == 0);
    lok(q_cycle2_zp(1) == 1);
    lok(q_cycle2_zp(2) == 0);
    lok(q_cycle2_zp(3) == 1);
    lok(q_cycle2_pz(0) == 1);
    lok(q_cycle2_pz(1) == 0);
    lok(q_cycle2_pz(2) == 1);
    lok(q_cycle2_pz(3) == 0);
    lok(q_cycle2_mz(0) == -1);
    lok(q_cycle2_mz(1) == 0);
    lok(q_cycle2_mz(2) == -1);
    lok(q_cycle2_mz(3) == 0);
    lok(q_cycle2_zm(0) == 0);
    lok(q_cycle2_zm(1) == -1);
    lok(q_cycle2_zm(2) == 0);
    lok(q_cycle2_zm(3) == -1);
    lok(q_cycle2_pm(0) == 1);
    lok(q_cycle2_pm(1) == -1);
    lok(q_cycle2_pm(2) == 1);
    lok(q_cycle2_pm(3) == -1);
    lok(q_cycle2_mp(0) == -1);
    lok(q_cycle2_mp(1) == 1);
    lok(q_cycle2_mp(2) == -1);
    lok(q_cycle2_mp(3) == 1);


    lok(q_cycle3_mzp(0) == -1);
    lok(q_cycle3_mzp(1) == 0);
    lok(q_cycle3_mzp(2) == 1);
    lok(q_cycle3_mzp(3) == -1);
    lok(q_cycle3_mzp(4) == 0);
    lok(q_cycle3_mzp(5) == 1);
    lok(q_cycle3_pmz(0) == 1);
    lok(q_cycle3_pmz(1) == -1);
    lok(q_cycle3_pmz(2) == 0);
    lok(q_cycle3_pmz(3) == 1);
    lok(q_cycle3_pmz(4) == -1);
    lok(q_cycle3_pmz(5) == 0);
    lok(q_cycle3_zpm(0) == 0);
    lok(q_cycle3_zpm(1) == 1);
    lok(q_cycle3_zpm(2) == -1);
    lok(q_cycle3_zpm(3) == 0);
    lok(q_cycle3_zpm(4) == 1);
    lok(q_cycle3_zpm(5) == -1);
    lok(q_cycle3_mpz(0) == -1);
    lok(q_cycle3_mpz(1) == 1);
    lok(q_cycle3_mpz(2) == 0);
    lok(q_cycle3_mpz(3) == -1);
    lok(q_cycle3_mpz(4) == 1);
    lok(q_cycle3_mpz(5) == 0);
    lok(q_cycle3_pzm(0) == 1);
    lok(q_cycle3_pzm(1) == 0);
    lok(q_cycle3_pzm(2) == -1);
    lok(q_cycle3_pzm(3) == 1);
    lok(q_cycle3_pzm(4) == 0);
    lok(q_cycle3_pzm(5) == -1);
    lok(q_cycle3_zmp(0) == 0);
    lok(q_cycle3_zmp(1) == -1);
    lok(q_cycle3_zmp(2) == 1);
    lok(q_cycle3_zmp(3) == 0);
    lok(q_cycle3_zmp(4) == -1);
    lok(q_cycle3_zmp(5) == 1);

    lok(q_cycle4_mzpz(0) == -1);
    lok(q_cycle4_mzpz(1) == 0);
    lok(q_cycle4_mzpz(2) == 1);
    lok(q_cycle4_mzpz(3) == 0);
    lok(q_cycle4_mzpz(4) == -1);
    lok(q_cycle4_mzpz(5) == 0);
    lok(q_cycle4_mzpz(6) == 1);
    lok(q_cycle4_mzpz(7) == 0);
    lok(q_cycle4_pzmz(0) == 1);
    lok(q_cycle4_pzmz(1) == 0);
    lok(q_cycle4_pzmz(2) == -1);
    lok(q_cycle4_pzmz(3) == 0);
    lok(q_cycle4_pzmz(4) == 1);
    lok(q_cycle4_pzmz(5) == 0);
    lok(q_cycle4_pzmz(6) == -1);
    lok(q_cycle4_pzmz(7) == 0);
    lok(q_cycle4_zmzp(0) == 0);
    lok(q_cycle4_zmzp(1) == -1);
    lok(q_cycle4_zmzp(2) == 0);
    lok(q_cycle4_zmzp(3) == 1);
    lok(q_cycle4_zmzp(4) == 0);
    lok(q_cycle4_zmzp(5) == -1);
    lok(q_cycle4_zmzp(6) == 0);
    lok(q_cycle4_zmzp(7) == 1);
    lok(q_cycle4_zmzp(0) == 0);
    lok(q_cycle4_zmzp(1) == -1);
    lok(q_cycle4_zmzp(2) == 0);
    lok(q_cycle4_zmzp(3) == 1);
    lok(q_cycle4_zmzp(4) == 0);
    lok(q_cycle4_zmzp(5) == -1);
    lok(q_cycle4_zmzp(6) == 0);
    lok(q_cycle4_zmzp(7) == 1);

    lok(q_cycle6_mzpzzz(0) == -1);
    lok(q_cycle6_mzpzzz(1) == 0);
    lok(q_cycle6_mzpzzz(2) == 1);
    lok(q_cycle6_mzpzzz(3) == 0);
    lok(q_cycle6_mzpzzz(4) == 0);
    lok(q_cycle6_mzpzzz(5) == 0);
    lok(q_cycle6_mzpzzz(6) == -1);
    lok(q_cycle6_mzpzzz(7) == 0);
    lok(q_cycle6_mzpzzz(8) == 1);
    lok(q_cycle6_mzpzzz(9) == 0);
    lok(q_cycle6_mzpzzz(10) == 0);
    lok(q_cycle6_mzpzzz(11) == 0);
    lok(q_cycle6_zzzmzp(0) == 0);
    lok(q_cycle6_zzzmzp(1) == 0);
    lok(q_cycle6_zzzmzp(2) == 0);
    lok(q_cycle6_zzzmzp(3) == -1);
    lok(q_cycle6_zzzmzp(4) == 0);
    lok(q_cycle6_zzzmzp(5) == 1);
    lok(q_cycle6_zzzmzp(6) == 0);
    lok(q_cycle6_zzzmzp(7) == 0);
    lok(q_cycle6_zzzmzp(8) == 0);
    lok(q_cycle6_zzzmzp(9) == -1);
    lok(q_cycle6_zzzmzp(10) == 0);
    lok(q_cycle6_zzzmzp(11) == 1);
    lok(q_cycle6_zzmzpz(0) == 0);
    lok(q_cycle6_zzmzpz(1) == 0);
    lok(q_cycle6_zzmzpz(2) == -1);
    lok(q_cycle6_zzmzpz(3) == 0);
    lok(q_cycle6_zzmzpz(4) == 1);
    lok(q_cycle6_zzmzpz(5) == 0);
    lok(q_cycle6_zzmzpz(6) == 0);
    lok(q_cycle6_zzmzpz(7) == 0);
    lok(q_cycle6_zzmzpz(8) == -1);
    lok(q_cycle6_zzmzpz(9) == 0);
    lok(q_cycle6_zzmzpz(10) == 1);
    lok(q_cycle6_zzmzpz(11) == 0);
    lok(q_cycle6_zpzzzm(0) == 0);
    lok(q_cycle6_zpzzzm(1) == 1);
    lok(q_cycle6_zpzzzm(2) == 0);
    lok(q_cycle6_zpzzzm(3) == 0);
    lok(q_cycle6_zpzzzm(4) == 0);
    lok(q_cycle6_zpzzzm(5) == -1);
    lok(q_cycle6_zpzzzm(6) == 0);
    lok(q_cycle6_zpzzzm(7) == 1);
    lok(q_cycle6_zpzzzm(8) == 0);
    lok(q_cycle6_zpzzzm(9) == 0);
    lok(q_cycle6_zpzzzm(10) == 0);
    lok(q_cycle6_zpzzzm(11) == -1);
    lok(q_cycle6_zmzpzz(0) == 0);
    lok(q_cycle6_zmzpzz(1) == -1);
    lok(q_cycle6_zmzpzz(2) == 0);
    lok(q_cycle6_zmzpzz(3) == 1);
    lok(q_cycle6_zmzpzz(4) == 0);
    lok(q_cycle6_zmzpzz(5) == 0);
    lok(q_cycle6_zmzpzz(6) == 0);
    lok(q_cycle6_zmzpzz(7) == -1);
    lok(q_cycle6_zmzpzz(8) == 0);
    lok(q_cycle6_zmzpzz(9) == 1);
    lok(q_cycle6_zmzpzz(10) == 0);
    lok(q_cycle6_zmzpzz(11) == 0);
    lok(q_cycle6_pzzzmz(0) == 1);
    lok(q_cycle6_pzzzmz(1) == 0);
    lok(q_cycle6_pzzzmz(2) == 0);
    lok(q_cycle6_pzzzmz(3) == 0);
    lok(q_cycle6_pzzzmz(4) == -1);
    lok(q_cycle6_pzzzmz(5) == 0);
    lok(q_cycle6_pzzzmz(6) == 1);
    lok(q_cycle6_pzzzmz(7) == 0);
    lok(q_cycle6_pzzzmz(8) == 0);
    lok(q_cycle6_pzzzmz(9) == 0);
    lok(q_cycle6_pzzzmz(10) == -1);
    lok(q_cycle6_pzzzmz(11) == 0);
    lok(q_cycle6_mzzzpz(0) == -1);
    lok(q_cycle6_mzzzpz(1) == 0);
    lok(q_cycle6_mzzzpz(2) == 0);
    lok(q_cycle6_mzzzpz(3) == 0);
    lok(q_cycle6_mzzzpz(4) == 1);
    lok(q_cycle6_mzzzpz(5) == 0);
    lok(q_cycle6_mzzzpz(6) == -1);
    lok(q_cycle6_mzzzpz(7) == 0);
    lok(q_cycle6_mzzzpz(8) == 0);
    lok(q_cycle6_mzzzpz(9) == 0);
    lok(q_cycle6_mzzzpz(10) == 1);
    lok(q_cycle6_mzzzpz(11) == 0);
    lok(q_cycle6_zpzmzz(0) == 0);
    lok(q_cycle6_zpzmzz(1) == 1);
    lok(q_cycle6_zpzmzz(2) == 0);
    lok(q_cycle6_zpzmzz(3) == -1);
    lok(q_cycle6_zpzmzz(4) == 0);
    lok(q_cycle6_zpzmzz(5) == 0);
    lok(q_cycle6_zpzmzz(6) == 0);
    lok(q_cycle6_zpzmzz(7) == 1);
    lok(q_cycle6_zpzmzz(8) == 0);
    lok(q_cycle6_zpzmzz(9) == -1);
    lok(q_cycle6_zpzmzz(10) == 0);
    lok(q_cycle6_zpzmzz(11) == 0);
    lok(q_cycle6_pzmzzz(0) == 1);
    lok(q_cycle6_pzmzzz(1) == 0);
    lok(q_cycle6_pzmzzz(2) == -1);
    lok(q_cycle6_pzmzzz(3) == 0);
    lok(q_cycle6_pzmzzz(4) == 0);
    lok(q_cycle6_pzmzzz(5) == 0);
    lok(q_cycle6_pzmzzz(6) == 1);
    lok(q_cycle6_pzmzzz(7) == 0);
    lok(q_cycle6_pzmzzz(8) == -1);
    lok(q_cycle6_pzmzzz(9) == 0);
    lok(q_cycle6_pzmzzz(10) == 0);
    lok(q_cycle6_pzmzzz(11) == 0);
    lok(q_cycle6_zzzpzm(0) == 0);
    lok(q_cycle6_zzzpzm(1) == 0);
    lok(q_cycle6_zzzpzm(2) == 0);
    lok(q_cycle6_zzzpzm(3) == 1);
    lok(q_cycle6_zzzpzm(4) == 0);
    lok(q_cycle6_zzzpzm(5) == -1);
    lok(q_cycle6_zzzpzm(6) == 0);
    lok(q_cycle6_zzzpzm(7) == 0);
    lok(q_cycle6_zzzpzm(8) == 0);
    lok(q_cycle6_zzzpzm(9) == 1);
    lok(q_cycle6_zzzpzm(10) == 0);
    lok(q_cycle6_zzzpzm(11) == -1);
    lok(q_cycle6_zzpzmz(0) == 0);
    lok(q_cycle6_zzpzmz(1) == 0);
    lok(q_cycle6_zzpzmz(2) == 1);
    lok(q_cycle6_zzpzmz(3) == 0);
    lok(q_cycle6_zzpzmz(4) == -1);
    lok(q_cycle6_zzpzmz(5) == 0);
    lok(q_cycle6_zzpzmz(6) == 0);
    lok(q_cycle6_zzpzmz(7) == 0);
    lok(q_cycle6_zzpzmz(8) == 1);
    lok(q_cycle6_zzpzmz(9) == 0);
    lok(q_cycle6_zzpzmz(10) == -1);
    lok(q_cycle6_zzpzmz(11) == 0);
    lok(q_cycle6_zmzzzp(0) == 0);
    lok(q_cycle6_zmzzzp(1) == -1);
    lok(q_cycle6_zmzzzp(2) == 0);
    lok(q_cycle6_zmzzzp(3) == 0);
    lok(q_cycle6_zmzzzp(4) == 0);
    lok(q_cycle6_zmzzzp(5) == 1);
    lok(q_cycle6_zmzzzp(6) == 0);
    lok(q_cycle6_zmzzzp(7) == -1);
    lok(q_cycle6_zmzzzp(8) == 0);
    lok(q_cycle6_zmzzzp(9) == 0);
    lok(q_cycle6_zmzzzp(10) == 0);
    lok(q_cycle6_zmzzzp(11) == 1);
    lok(q_cycle6_mppmzz(0) == -1);
    lok(q_cycle6_mppmzz(1) == 1);
    lok(q_cycle6_mppmzz(2) == 1);
    lok(q_cycle6_mppmzz(3) == -1);
    lok(q_cycle6_mppmzz(4) == 0);
    lok(q_cycle6_mppmzz(5) == 0);
    lok(q_cycle6_mppmzz(6) == -1);
    lok(q_cycle6_mppmzz(7) == 1);
    lok(q_cycle6_mppmzz(8) == 1);
    lok(q_cycle6_mppmzz(9) == -1);
    lok(q_cycle6_mppmzz(10) == 0);
    lok(q_cycle6_mppmzz(11) == 0);
    lok(q_cycle6_zzmppm(0) == 0);
    lok(q_cycle6_zzmppm(1) == 0);
    lok(q_cycle6_zzmppm(2) == -1);
    lok(q_cycle6_zzmppm(3) == 1);
    lok(q_cycle6_zzmppm(4) == 1);
    lok(q_cycle6_zzmppm(5) == -1);
    lok(q_cycle6_zzmppm(6) == 0);
    lok(q_cycle6_zzmppm(7) == 0);
    lok(q_cycle6_zzmppm(8) == -1);
    lok(q_cycle6_zzmppm(9) == 1);
    lok(q_cycle6_zzmppm(10) == 1);
    lok(q_cycle6_zzmppm(11) == -1);
    lok(q_cycle6_pmzzmp(0) == 1);
    lok(q_cycle6_pmzzmp(1) == -1);
    lok(q_cycle6_pmzzmp(2) == 0);
    lok(q_cycle6_pmzzmp(3) == 0);
    lok(q_cycle6_pmzzmp(4) == -1);
    lok(q_cycle6_pmzzmp(5) == 1);
    lok(q_cycle6_pmzzmp(6) == 1);
    lok(q_cycle6_pmzzmp(7) == -1);
    lok(q_cycle6_pmzzmp(8) == 0);
    lok(q_cycle6_pmzzmp(9) == 0);
    lok(q_cycle6_pmzzmp(10) == -1);
    lok(q_cycle6_pmzzmp(11) == 1);

    dupprintf(globalf, "Geometrics sequences");
    int32_t current;
    int32_t upper1;
    int32_t upper2;
    int32_t lower;
    int32_t out;
    int32_t geo_factor;
    int32_t distance;
    current = 0;
    upper1 = 3;
    upper2 = 6;
    lower = 0;
    distance = 32;
    geo_factor = 2;
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 16);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 8);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 4);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 2);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    geo_factor = 3;
    distance = 243;
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 81);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 27);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 9);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 3);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    distance = q_sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    lower = 0;
    dupprintf(globalf, "pingpong");
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 0);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 0);
    current++;
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 1);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 1);
    current++;
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 2);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 2);
    current++;
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 1);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 3);
    current++;
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 0);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 4);
    current++;
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 1);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 5);
    current++;
    out = q_sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 2);
    out = q_sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 4);
}
void cache_benchmarks() {
    dupprintf(globalf, "\n q_math cache benchmarks\n");
    size_t row = 100;
    size_t col = 10;
    size_t depth = 20;
    double t_0, t_1;

    uint8_t * temp_cache = calloc(row * col, sizeof(*temp_cache));
    uint64_t * temp_cache3d = calloc(row * col * depth, sizeof(*temp_cache3d));

    // row col is cache friendly!
    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t r = 0; r < row; r++) {
            for (size_t c = 0; c < col; c++) {
                temp_cache[(r * col + c)] = r + c;
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache row col %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t c = 0; c < col; c++) {
            for (size_t r = 0; r < row; r++) {
                temp_cache[(r * col + c)] = r + c;
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache col row %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    // row col depth is cache friendly!
    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        // dupprintf(globalf, "i %d \n", i);
        for (size_t r = 0; r < row; r++) {
            // dupprintf(globalf, "r %d \n", r);
            for (size_t c = 0; c < col; c++) {
                // dupprintf(globalf, "c %d \n", c);
                for (size_t d = 0; d < depth; d++) {
                    // dupprintf(globalf, "d %d \n", d);
                    // dupprintf(globalf, "len len %d %d \n", (r * col  + c * row + d), (col * row * depth));

                    temp_cache3d[(r * col  + c * row + d)] = r + c + d;
                }
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache row col depth %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t c = 0; c < col; c++) {
            for (size_t r = 0; r < row; r++) {
                for (size_t d = 0; d < depth; d++) {
                    temp_cache3d[(r * col  + c * row + d)] = r + c + d;
                }
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache col row depth %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t c = 0; c < col; c++) {
            for (size_t d = 0; d < depth; d++) {
                for (size_t r = 0; r < row; r++) {
                    temp_cache3d[(r * col  + c * row + d)] = r + c + d;
                }
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache col depth row %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t r = 0; r < row; r++) {
            for (size_t d = 0; d < depth; d++) {
                for (size_t c = 0; c < col; c++) {
                    temp_cache3d[(r * col  + c * row + d)] = r + c + d;
                }
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache row depth col %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t d = 0; d < depth; d++) {
            for (size_t r = 0; r < row; r++) {
                for (size_t c = 0; c < col; c++) {
                    temp_cache3d[(r * col  + c * row + d)] = r + c + d;
                }
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache depth row col %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);

    t_0 = get_us();
    for (size_t i = 0; i < ITERATIONS; i++) {
        for (size_t d = 0; d < depth; d++) {
            for (size_t c = 0; c < col; c++) {
                for (size_t r = 0; r < row; r++) {
                    temp_cache3d[(r * col  + c * row + d)] = r + c + d;
                }
            }
        }
    }
    t_1 = get_us();
    dupprintf(globalf, "cache depth col row %d \n", ITERATIONS);
    dupprintf(globalf, "%.1f [us] \n", t_1 - t_0);


}


int main() {
    globalf = fopen("q_math_test_results.txt", "w+");
    dupprintf(globalf, "\nHello, World! I am testing q_math.\n");
    lrun("log2", test_log2);
    cache_benchmarks();
    lresults();

    dupprintf(globalf, "q_math Test End \n \n");
    fclose(globalf);
    return (0);
}
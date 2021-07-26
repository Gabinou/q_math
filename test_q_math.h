#include "minctest.h"
#include "q_math.h"

void test_q_math() {
    SDL_Log("test_q_math");


    SDL_Log("test_cycles");
    lok(cycle2_zp(0) == 0);
    lok(cycle2_zp(1) == 1);
    lok(cycle2_zp(2) == 0);
    lok(cycle2_zp(3) == 1);
    lok(cycle2_pz(0) == 1);
    lok(cycle2_pz(1) == 0);
    lok(cycle2_pz(2) == 1);
    lok(cycle2_pz(3) == 0);
    lok(cycle2_mz(0) == -1);
    lok(cycle2_mz(1) == 0);
    lok(cycle2_mz(2) == -1);
    lok(cycle2_mz(3) == 0);
    lok(cycle2_zm(0) == 0);
    lok(cycle2_zm(1) == -1);
    lok(cycle2_zm(2) == 0);
    lok(cycle2_zm(3) == -1);
    lok(cycle2_pm(0) == 1);
    lok(cycle2_pm(1) == -1);
    lok(cycle2_pm(2) == 1);
    lok(cycle2_pm(3) == -1);
    lok(cycle2_mp(0) == -1);
    lok(cycle2_mp(1) == 1);
    lok(cycle2_mp(2) == -1);
    lok(cycle2_mp(3) == 1);


    lok(cycle3_mzp(0) == -1);
    lok(cycle3_mzp(1) == 0);
    lok(cycle3_mzp(2) == 1);
    lok(cycle3_mzp(3) == -1);
    lok(cycle3_mzp(4) == 0);
    lok(cycle3_mzp(5) == 1);
    lok(cycle3_pmz(0) == 1);
    lok(cycle3_pmz(1) == -1);
    lok(cycle3_pmz(2) == 0);
    lok(cycle3_pmz(3) == 1);
    lok(cycle3_pmz(4) == -1);
    lok(cycle3_pmz(5) == 0);
    lok(cycle3_zpm(0) == 0);
    lok(cycle3_zpm(1) == 1);
    lok(cycle3_zpm(2) == -1);
    lok(cycle3_zpm(3) == 0);
    lok(cycle3_zpm(4) == 1);
    lok(cycle3_zpm(5) == -1);
    lok(cycle3_mpz(0) == -1);
    lok(cycle3_mpz(1) == 1);
    lok(cycle3_mpz(2) == 0);
    lok(cycle3_mpz(3) == -1);
    lok(cycle3_mpz(4) == 1);
    lok(cycle3_mpz(5) == 0);
    lok(cycle3_pzm(0) == 1);
    lok(cycle3_pzm(1) == 0);
    lok(cycle3_pzm(2) == -1);
    lok(cycle3_pzm(3) == 1);
    lok(cycle3_pzm(4) == 0);
    lok(cycle3_pzm(5) == -1);
    lok(cycle3_zmp(0) == 0);
    lok(cycle3_zmp(1) == -1);
    lok(cycle3_zmp(2) == 1);
    lok(cycle3_zmp(3) == 0);
    lok(cycle3_zmp(4) == -1);
    lok(cycle3_zmp(5) == 1);

    lok(cycle4_mzpz(0) == -1);
    lok(cycle4_mzpz(1) == 0);
    lok(cycle4_mzpz(2) == 1);
    lok(cycle4_mzpz(3) == 0);
    lok(cycle4_mzpz(4) == -1);
    lok(cycle4_mzpz(5) == 0);
    lok(cycle4_mzpz(6) == 1);
    lok(cycle4_mzpz(7) == 0);
    lok(cycle4_pzmz(0) == 1);
    lok(cycle4_pzmz(1) == 0);
    lok(cycle4_pzmz(2) == -1);
    lok(cycle4_pzmz(3) == 0);
    lok(cycle4_pzmz(4) == 1);
    lok(cycle4_pzmz(5) == 0);
    lok(cycle4_pzmz(6) == -1);
    lok(cycle4_pzmz(7) == 0);
    lok(cycle4_zmzp(0) == 0);
    lok(cycle4_zmzp(1) == -1);
    lok(cycle4_zmzp(2) == 0);
    lok(cycle4_zmzp(3) == 1);
    lok(cycle4_zmzp(4) == 0);
    lok(cycle4_zmzp(5) == -1);
    lok(cycle4_zmzp(6) == 0);
    lok(cycle4_zmzp(7) == 1);
    lok(cycle4_zmzp(0) == 0);
    lok(cycle4_zmzp(1) == -1);
    lok(cycle4_zmzp(2) == 0);
    lok(cycle4_zmzp(3) == 1);
    lok(cycle4_zmzp(4) == 0);
    lok(cycle4_zmzp(5) == -1);
    lok(cycle4_zmzp(6) == 0);
    lok(cycle4_zmzp(7) == 1);

    lok(cycle6_mzpzzz(0) == -1);
    lok(cycle6_mzpzzz(1) == 0);
    lok(cycle6_mzpzzz(2) == 1);
    lok(cycle6_mzpzzz(3) == 0);
    lok(cycle6_mzpzzz(4) == 0);
    lok(cycle6_mzpzzz(5) == 0);
    lok(cycle6_mzpzzz(6) == -1);
    lok(cycle6_mzpzzz(7) == 0);
    lok(cycle6_mzpzzz(8) == 1);
    lok(cycle6_mzpzzz(9) == 0);
    lok(cycle6_mzpzzz(10) == 0);
    lok(cycle6_mzpzzz(11) == 0);
    lok(cycle6_zzzmzp(0) == 0);
    lok(cycle6_zzzmzp(1) == 0);
    lok(cycle6_zzzmzp(2) == 0);
    lok(cycle6_zzzmzp(3) == -1);
    lok(cycle6_zzzmzp(4) == 0);
    lok(cycle6_zzzmzp(5) == 1);
    lok(cycle6_zzzmzp(6) == 0);
    lok(cycle6_zzzmzp(7) == 0);
    lok(cycle6_zzzmzp(8) == 0);
    lok(cycle6_zzzmzp(9) == -1);
    lok(cycle6_zzzmzp(10) == 0);
    lok(cycle6_zzzmzp(11) == 1);
    lok(cycle6_zzmzpz(0) == 0);
    lok(cycle6_zzmzpz(1) == 0);
    lok(cycle6_zzmzpz(2) == -1);
    lok(cycle6_zzmzpz(3) == 0);
    lok(cycle6_zzmzpz(4) == 1);
    lok(cycle6_zzmzpz(5) == 0);
    lok(cycle6_zzmzpz(6) == 0);
    lok(cycle6_zzmzpz(7) == 0);
    lok(cycle6_zzmzpz(8) == -1);
    lok(cycle6_zzmzpz(9) == 0);
    lok(cycle6_zzmzpz(10) == 1);
    lok(cycle6_zzmzpz(11) == 0);
    lok(cycle6_zpzzzm(0) == 0);
    lok(cycle6_zpzzzm(1) == 1);
    lok(cycle6_zpzzzm(2) == 0);
    lok(cycle6_zpzzzm(3) == 0);
    lok(cycle6_zpzzzm(4) == 0);
    lok(cycle6_zpzzzm(5) == -1);
    lok(cycle6_zpzzzm(6) == 0);
    lok(cycle6_zpzzzm(7) == 1);
    lok(cycle6_zpzzzm(8) == 0);
    lok(cycle6_zpzzzm(9) == 0);
    lok(cycle6_zpzzzm(10) == 0);
    lok(cycle6_zpzzzm(11) == -1);
    lok(cycle6_zmzpzz(0) == 0);
    lok(cycle6_zmzpzz(1) == -1);
    lok(cycle6_zmzpzz(2) == 0);
    lok(cycle6_zmzpzz(3) == 1);
    lok(cycle6_zmzpzz(4) == 0);
    lok(cycle6_zmzpzz(5) == 0);
    lok(cycle6_zmzpzz(6) == 0);
    lok(cycle6_zmzpzz(7) == -1);
    lok(cycle6_zmzpzz(8) == 0);
    lok(cycle6_zmzpzz(9) == 1);
    lok(cycle6_zmzpzz(10) == 0);
    lok(cycle6_zmzpzz(11) == 0);
    lok(cycle6_pzzzmz(0) == 1);
    lok(cycle6_pzzzmz(1) == 0);
    lok(cycle6_pzzzmz(2) == 0);
    lok(cycle6_pzzzmz(3) == 0);
    lok(cycle6_pzzzmz(4) == -1);
    lok(cycle6_pzzzmz(5) == 0);
    lok(cycle6_pzzzmz(6) == 1);
    lok(cycle6_pzzzmz(7) == 0);
    lok(cycle6_pzzzmz(8) == 0);
    lok(cycle6_pzzzmz(9) == 0);
    lok(cycle6_pzzzmz(10) == -1);
    lok(cycle6_pzzzmz(11) == 0);
    lok(cycle6_mzzzpz(0) == -1);
    lok(cycle6_mzzzpz(1) == 0);
    lok(cycle6_mzzzpz(2) == 0);
    lok(cycle6_mzzzpz(3) == 0);
    lok(cycle6_mzzzpz(4) == 1);
    lok(cycle6_mzzzpz(5) == 0);
    lok(cycle6_mzzzpz(6) == -1);
    lok(cycle6_mzzzpz(7) == 0);
    lok(cycle6_mzzzpz(8) == 0);
    lok(cycle6_mzzzpz(9) == 0);
    lok(cycle6_mzzzpz(10) == 1);
    lok(cycle6_mzzzpz(11) == 0);
    lok(cycle6_zpzmzz(0) == 0);
    lok(cycle6_zpzmzz(1) == 1);
    lok(cycle6_zpzmzz(2) == 0);
    lok(cycle6_zpzmzz(3) == -1);
    lok(cycle6_zpzmzz(4) == 0);
    lok(cycle6_zpzmzz(5) == 0);
    lok(cycle6_zpzmzz(6) == 0);
    lok(cycle6_zpzmzz(7) == 1);
    lok(cycle6_zpzmzz(8) == 0);
    lok(cycle6_zpzmzz(9) == -1);
    lok(cycle6_zpzmzz(10) == 0);
    lok(cycle6_zpzmzz(11) == 0);
    lok(cycle6_pzmzzz(0) == 1);
    lok(cycle6_pzmzzz(1) == 0);
    lok(cycle6_pzmzzz(2) == -1);
    lok(cycle6_pzmzzz(3) == 0);
    lok(cycle6_pzmzzz(4) == 0);
    lok(cycle6_pzmzzz(5) == 0);
    lok(cycle6_pzmzzz(6) == 1);
    lok(cycle6_pzmzzz(7) == 0);
    lok(cycle6_pzmzzz(8) == -1);
    lok(cycle6_pzmzzz(9) == 0);
    lok(cycle6_pzmzzz(10) == 0);
    lok(cycle6_pzmzzz(11) == 0);
    lok(cycle6_zzzpzm(0) == 0);
    lok(cycle6_zzzpzm(1) == 0);
    lok(cycle6_zzzpzm(2) == 0);
    lok(cycle6_zzzpzm(3) == 1);
    lok(cycle6_zzzpzm(4) == 0);
    lok(cycle6_zzzpzm(5) == -1);
    lok(cycle6_zzzpzm(6) == 0);
    lok(cycle6_zzzpzm(7) == 0);
    lok(cycle6_zzzpzm(8) == 0);
    lok(cycle6_zzzpzm(9) == 1);
    lok(cycle6_zzzpzm(10) == 0);
    lok(cycle6_zzzpzm(11) == -1);
    lok(cycle6_zzpzmz(0) == 0);
    lok(cycle6_zzpzmz(1) == 0);
    lok(cycle6_zzpzmz(2) == 1);
    lok(cycle6_zzpzmz(3) == 0);
    lok(cycle6_zzpzmz(4) == -1);
    lok(cycle6_zzpzmz(5) == 0);
    lok(cycle6_zzpzmz(6) == 0);
    lok(cycle6_zzpzmz(7) == 0);
    lok(cycle6_zzpzmz(8) == 1);
    lok(cycle6_zzpzmz(9) == 0);
    lok(cycle6_zzpzmz(10) == -1);
    lok(cycle6_zzpzmz(11) == 0);
    lok(cycle6_zmzzzp(0) == 0);
    lok(cycle6_zmzzzp(1) == -1);
    lok(cycle6_zmzzzp(2) == 0);
    lok(cycle6_zmzzzp(3) == 0);
    lok(cycle6_zmzzzp(4) == 0);
    lok(cycle6_zmzzzp(5) == 1);
    lok(cycle6_zmzzzp(6) == 0);
    lok(cycle6_zmzzzp(7) == -1);
    lok(cycle6_zmzzzp(8) == 0);
    lok(cycle6_zmzzzp(9) == 0);
    lok(cycle6_zmzzzp(10) == 0);
    lok(cycle6_zmzzzp(11) == 1);
    lok(cycle6_mppmzz(0) == -1);
    lok(cycle6_mppmzz(1) == 1);
    lok(cycle6_mppmzz(2) == 1);
    lok(cycle6_mppmzz(3) == -1);
    lok(cycle6_mppmzz(4) == 0);
    lok(cycle6_mppmzz(5) == 0);
    lok(cycle6_mppmzz(6) == -1);
    lok(cycle6_mppmzz(7) == 1);
    lok(cycle6_mppmzz(8) == 1);
    lok(cycle6_mppmzz(9) == -1);
    lok(cycle6_mppmzz(10) == 0);
    lok(cycle6_mppmzz(11) == 0);
    lok(cycle6_zzmppm(0) == 0);
    lok(cycle6_zzmppm(1) == 0);
    lok(cycle6_zzmppm(2) == -1);
    lok(cycle6_zzmppm(3) == 1);
    lok(cycle6_zzmppm(4) == 1);
    lok(cycle6_zzmppm(5) == -1);
    lok(cycle6_zzmppm(6) == 0);
    lok(cycle6_zzmppm(7) == 0);
    lok(cycle6_zzmppm(8) == -1);
    lok(cycle6_zzmppm(9) == 1);
    lok(cycle6_zzmppm(10) == 1);
    lok(cycle6_zzmppm(11) == -1);
    lok(cycle6_pmzzmp(0) == 1);
    lok(cycle6_pmzzmp(1) == -1);
    lok(cycle6_pmzzmp(2) == 0);
    lok(cycle6_pmzzmp(3) == 0);
    lok(cycle6_pmzzmp(4) == -1);
    lok(cycle6_pmzzmp(5) == 1);
    lok(cycle6_pmzzmp(6) == 1);
    lok(cycle6_pmzzmp(7) == -1);
    lok(cycle6_pmzzmp(8) == 0);
    lok(cycle6_pmzzmp(9) == 0);
    lok(cycle6_pmzzmp(10) == -1);
    lok(cycle6_pmzzmp(11) == 1);

    SDL_Log("Geometrics sequences");
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
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 16);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 8);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 4);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 2);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    geo_factor = 3;
    distance = 243;
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 81);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 27);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 9);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 3);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    distance = sequence_geometric_int32_t(distance, 0, geo_factor);
    lok(distance == 1);
    lower = 0;
    SDL_Log("pingpong");
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 0);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 0);
    current++;
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 1);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 1);
    current++;
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 2);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 2);
    current++;
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 1);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 3);
    current++;
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 0);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 4);
    current++;
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 1);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 5);
    current++;
    out = sequence_pingpong_int32_t(current, upper1, lower);
    lok(out == 2);
    out = sequence_pingpong_int32_t(current, upper2, lower);
    lok(out == 4);
}

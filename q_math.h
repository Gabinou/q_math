#ifndef Q_MATH_H
#define Q_MATH_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#ifdef __TINYC__
#include "tcc/tcc_libm.h"
#endif

#ifndef log2// because tcc SUCKS, does NOT DEFINE log2
#define log2(x) (log(x)/log(2.0f))
#endif

/************************* CONSTANTS *****************************/
#define Q_MATH_TEMPLATE_TYPES_INT REGISTER_ENUM(int8_t) \
REGISTER_ENUM(uint8_t) \
REGISTER_ENUM(int16_t) \
REGISTER_ENUM(uint16_t) \
REGISTER_ENUM(int32_t) \
REGISTER_ENUM(uint32_t) \
REGISTER_ENUM(int64_t) \
REGISTER_ENUM(uint64_t)\
REGISTER_ENUM(bool)

#define Q_MATH_TEMPLATE_TYPES_FLOAT REGISTER_ENUM(float) \
REGISTER_ENUM(double)

#define Q_MATH_TEMPLATE_TYPES REGISTER_ENUM(int8_t) \
REGISTER_ENUM(uint8_t) \
REGISTER_ENUM(int16_t) \
REGISTER_ENUM(uint16_t) \
REGISTER_ENUM(int32_t) \
REGISTER_ENUM(uint32_t) \
REGISTER_ENUM(int64_t) \
REGISTER_ENUM(uint64_t) \
REGISTER_ENUM(bool) \
REGISTER_ENUM(float) \
REGISTER_ENUM(double)

/************************* PERIODIC q_cycleS *****************************/
// m:-1, p:1, z:0
#define q_cycle2_zp(i) (i % 2)
#define q_cycle2_pz(i) ((i + 1) % 2)
#define q_cycle2_mz(i) ((i % 2) - 1)
#define q_cycle2_zm(i) (((i + 1) % 2) - 1)
#define q_cycle2_mp(i) (q_cycle2_mz(i) + q_cycle2_zp(i))
#define q_cycle2_pm(i) (q_cycle2_pz(i) + q_cycle2_zm(i))

#define q_cycle3_mzp(i) ((i % 3) - 1)
#define q_cycle3_zpm(i) (((i + 1) % 3) - 1)
#define q_cycle3_pmz(i) (((i + 2) % 3) - 1)
#define q_cycle3_pzm(i) (1 - (i % 3))
#define q_cycle3_zmp(i) (1 - ((i + 1) % 3))
#define q_cycle3_mpz(i) (1 - ((i + 2) % 3))

#define q_cycle4_mzp2(i) ((i % 4) - 1)
#define q_cycle4_zp2m(i) (((i + 1) % 4) - 1)
#define q_cycle4_p2mz(i) (((i + 2) % 4) - 1)
#define q_cycle4_2mzp(i) (((i + 3) % 4) - 1)
#define q_cycle4_mzpz(i) (q_cycle2_pz(i) * q_cycle4_mzp2(i))
#define q_cycle4_pzmz(i) (q_cycle2_mz(i) * q_cycle4_mzp2(i))
#define q_cycle4_zmzp(i) (q_cycle2_zp(i) * q_cycle4_2mzp(i))
#define q_cycle4_zpzm(i) (q_cycle2_zp(i) * q_cycle4_zp2m(i))

#define q_cycle4_mmpp(i) (q_cycle4_mzpz(i) + q_cycle4_zmzp(i))
#define q_cycle4_pmmp(i) (q_cycle4_pzmz(i) + q_cycle4_zmzp(i))
#define q_cycle4_mppm(i) (q_cycle4_mzpz(i) + q_cycle4_zpzm(i))
#define q_cycle4_ppmm(i) (q_cycle4_pzmz(i) + q_cycle4_zpzm(i))

#define q_cycle6_mzpzzz(i) (q_cycle3_mzp(i) * q_cycle2_pz(i))
#define q_cycle6_zzzmzp(i) (q_cycle3_mzp(i) * q_cycle2_zp(i))
#define q_cycle6_zzmzpz(i) (q_cycle3_zpm(i) * q_cycle2_pz(i))
#define q_cycle6_zpzzzm(i) (q_cycle3_zpm(i) * q_cycle2_zp(i))
#define q_cycle6_pzzzmz(i) (q_cycle3_pmz(i) * q_cycle2_pz(i))
#define q_cycle6_zmzpzz(i) (q_cycle3_pmz(i) * q_cycle2_zp(i))

#define q_cycle6_mzzzpz(i) (q_cycle3_mpz(i) * q_cycle2_pz(i))
#define q_cycle6_zpzmzz(i) (q_cycle3_mpz(i) * q_cycle2_zp(i))
#define q_cycle6_pzmzzz(i) (q_cycle3_pzm(i) * q_cycle2_pz(i))
#define q_cycle6_zzzpzm(i) (q_cycle3_pzm(i) * q_cycle2_zp(i))
#define q_cycle6_zzpzmz(i) (q_cycle3_zmp(i) * q_cycle2_pz(i))
#define q_cycle6_zmzzzp(i) (q_cycle3_zmp(i) * q_cycle2_zp(i))

#define q_cycle6_mppmzz(i) (q_cycle6_mzpzzz(i) + q_cycle6_zpzmzz(i))
#define q_cycle6_zzmppm(i) (q_cycle6_zzzpzm(i) + q_cycle6_zzmzpz(i))
#define q_cycle6_pmzzmp(i) (q_cycle6_zmzzzp(i) + q_cycle6_pzzzmz(i))

#define REGISTER_ENUM(type) extern type q_sequence_geometric_##type(type start, type destination, type geo_factor);
Q_MATH_TEMPLATE_TYPES_INT
#undef REGISTER_ENUM

#define REGISTER_ENUM(type) extern type q_sequence_pingpong_##type(type current, type upper, type lower);
Q_MATH_TEMPLATE_TYPES_INT
#undef REGISTER_ENUM

#define REGISTER_ENUM(type) extern float q_sqrt_##type(type in_int);
Q_MATH_TEMPLATE_TYPES
#undef REGISTER_ENUM

#define  carmack_sqrt_int8_t q_sqrt_int8_t
#define  carmack_sqrt_uint8_t q_sqrt_uint8_t
#define  carmack_sqrt_int16_t q_sqrt_int16_t
#define  carmack_sqrt_uint16_t q_sqrt_uint16_t
#define  carmack_sqrt_int32_t q_sqrt_int32_t
#define  carmack_sqrt_uint32_t q_sqrt_uint32_t
#define  carmack_sqrt_int64_t q_sqrt_int64_t
#define  carmack_sqrt_uint64_t q_sqrt_uint64_t
#define  carmack_sqrt_float q_sqrt_float
#define  carmack_sqrt_double q_sqrt_double

#endif /* Q_MATH_H */

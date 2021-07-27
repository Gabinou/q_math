
#include "q_math.h"

// sequence_geometric: Geometrically decreasing integer/float
// distance/geo_factor -> distance/geo_factor**2 -> distance/geo_factor**3
// Ex: q_sequence_geometric(32,1,2) = 16->8->4 ...
// sign*distance more elegant than std_abs()
#define REGISTER_ENUM(type) type q_sequence_geometric_##type(type start, type destination, type geo_factor) {\
    type distance = start - destination;\
    type sign = (type)copysign(1, distance);\
    type out = (sign * (distance / geo_factor) < 1) ? sign : (distance / geo_factor);\
    return (out);\
}
TEMPLATE_TYPES_INT
#undef REGISTER_ENUM

// sequence_pingpong: oscillating integer sequence. upper is excluded.
// modulo: x % 2 = 0,1,2,0,1,2,0...for x++
// pingpong(x, 2, 0) = 0,1,2,1,0,1,2... for x++
#define REGISTER_ENUM(type) type q_sequence_pingpong_##type(type current, type upper, type lower) {\
    type mod_factor = (2 * (upper - lower) - 2);\
    type term1 = mod_factor - (current % mod_factor);\
    type term2 = current % mod_factor;\
    return (fmin(term1, term2) + lower);\
}
TEMPLATE_TYPES_INT
#undef REGISTER_ENUM

// Sometimes attributed to John Carmack...
#define REGISTER_ENUM(type) float q_sqrt_##type(type in_int) {\
    const float x2 = in_int * 0.5f;\
    const float threehalfs = 1.5f;\
    union {\
        float f;\
        unsigned long i;\
    } conv  = { .f = in_int };\
    conv.i  = 0x5f3759df - (conv.i >> 1);\
    conv.f  *= (threehalfs - (x2 * conv.f * conv.f));\
    return conv.f;\
}
TEMPLATE_TYPES
#undef REGISTER_ENUM

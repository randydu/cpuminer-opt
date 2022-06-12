#include <catch_macros.h>


#define EXP16 65536.
#define EXP32 4294967296.
const long double exp32 = EXP32;                                  // 2**32
const long double exp48 = EXP32 * EXP16;                          // 2**48
const long double exp64 = EXP32 * EXP32;                          // 2**64
const long double exp96 = EXP32 * EXP32 * EXP32;                  // 2**96
const long double exp128 = EXP32 * EXP32 * EXP32 * EXP32;         // 2**128
const long double exp160 = EXP32 * EXP32 * EXP32 * EXP32 * EXP16; // 2**160

void diff_to_hash( uint32_t *target, const double diff )
{
  uint64_t *targ = (uint64_t*)target;
  register long double m = ( 1. / diff ) * exp32;
//  targ[1] = targ[0] = 0;
  targ[1] = targ[0] = -1;
  targ[3] = (uint64_t)m;
  targ[2] = (uint64_t)( ( m - (long double)targ[3] ) * exp64 );
}

double hash_to_diff( const void *target )
{
   const uint64_t *targ = (const uint64_t*)target;
   register long double m = ( (long double)targ[3] / exp32 )
                          + ( (long double)targ[2] / exp96 );
   return (double)( 1. / m );
}

inline bool valid_hash( const void *hash, const void *target )
{
   const uint64_t *h = (const uint64_t*)hash;
   const uint64_t *t = (const uint64_t*)target;
   if ( h[3] > t[3] ) return false;
   if ( h[3] < t[3] ) return true;
   if ( h[2] > t[2] ) return false;
   if ( h[2] < t[2] ) return true;
   if ( h[1] > t[1] ) return false;
   if ( h[1] < t[1] ) return true;
   if ( h[0] > t[0] ) return false;
   return true;
}


TEST_CASE("diff", "[util]")
{
    const double diff = 0.000000001;
    uint32_t target[8]{};
    diff_to_hash(&target[0], diff);

    double diff_r = hash_to_diff(&target[0]);
    CHECK(diff_r == diff);
}

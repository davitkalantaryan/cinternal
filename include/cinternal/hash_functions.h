//
// repo:            cinternal
// file:            hash_functions.h
// path:			include/cinternal/hash_functions.h
// created on:		2024 Dec 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_FUNCTIONS_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_FUNCTIONS_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdint.h>
#include <cinternal/undisable_compiler_warnings.h>

#ifndef cinternal_mix
#define cinternal_mix(a,b,c) \
{ \
  a=a-b;  a=a-c;  a=a^(c>>13); \
  b=b-c;  b=b-a;  b=b^(a<<8);  \
  c=c-a;  c=c-b;  c=c^(b>>13); \
  a=a-b;  a=a-c;  a=a^(c>>12); \
  b=b-c;  b=b-a;  b=b^(a<<16); \
  c=c-a;  c=c-b;  c=c^(b>>5);  \
  a=a-b;  a=a-c;  a=a^(c>>3);  \
  b=b-c;  b=b-a;  b=b^(a<<10); \
  c=c-a;  c=c-b;  c=c^(b>>15); \
}
#endif


#ifdef cinternal_hash1_raw_mem_inline_needed

static inline size_t cinternal_hash1_raw_mem_inline(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT
{
    const uint32_t unKeySize = CPPUTILS_STATIC_CAST(uint32_t, a_unKeySize);
    CPPUTILS_REGISTER const uint8_t* k = CPPUTILS_STATIC_CAST(const uint8_t*, a_pKey);
    CPPUTILS_REGISTER uint32_t a, b, c;  /* the internal state */

    uint32_t          len;    /* how many key bytes still need mixing */

    /* Set up the internal state */
    len = unKeySize;
    a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
    c = 13;         /* variable initialization of internal state */

    /*---------------------------------------- handle most of the key */
    while (len >= 12) {
        a = a + (k[0] + (CPPUTILS_STATIC_CAST(uint32_t, k[1]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[2]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[3]) << 24));
        b = b + (k[4] + (CPPUTILS_STATIC_CAST(uint32_t, k[5]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[6]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[7]) << 24));
        c = c + (k[8] + (CPPUTILS_STATIC_CAST(uint32_t, k[9]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[10]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[11]) << 24));
        cinternal_mix(a, b, c);
        k = k + 12; len = len - 12;
    }

    /*------------------------------------- handle the last 11 bytes */
    c = c + unKeySize;

    /* all the case statements fall through */
    switch (len) {
    case 11: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[10]) << 24); CPPUTILS_FALLTHROUGH
    case 10: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[9]) << 16); CPPUTILS_FALLTHROUGH
    case 9: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[8]) << 8); CPPUTILS_FALLTHROUGH

        /* the first byte of c is reserved for the length */
    case 8: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[7]) << 24); CPPUTILS_FALLTHROUGH
    case 7: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[6]) << 16); CPPUTILS_FALLTHROUGH
    case 6: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[5]) << 8); CPPUTILS_FALLTHROUGH
    case 5: b = b + k[4]; CPPUTILS_FALLTHROUGH
    case 4: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[3]) << 24); CPPUTILS_FALLTHROUGH
    case 3: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[2]) << 16); CPPUTILS_FALLTHROUGH
    case 2: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[1]) << 8); CPPUTILS_FALLTHROUGH
    case 1: a = a + k[0];
        /* case 0: nothing left to add */
    }
    cinternal_mix(a, b, c);
    /*-------------------------------------------- report the result */

    return CPPUTILS_STATIC_CAST(size_t, c);
}

#endif  //  cinternal_hash1_raw_mem_inline_needed



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_FUNCTIONS_H

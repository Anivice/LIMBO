/**
 * @file stdint.h
 *
 * @copyright
 * Copyright (C) 1997-2025 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 *
 * The GNU C Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef _STDINT_H
#define _STDINT_H       1

/* Convenience types.  */
typedef unsigned char           __u_char;
typedef unsigned short int      __u_short;
typedef unsigned int            __u_int;
typedef unsigned long int       __u_long;

/* Fixed-size types, underlying types depend on word size and compiler.  */
typedef signed char             __int8_t;
typedef unsigned char           __uint8_t;
typedef signed short int        __int16_t;
typedef unsigned short int      __uint16_t;
typedef signed int              __int32_t;
typedef unsigned int            __uint32_t;
__extension__ typedef
signed long long int            __int64_t;
__extension__ typedef
unsigned long long int          __uint64_t;

/* Smallest types with at least a given width.  */
typedef __int8_t                __int_least8_t;
typedef __uint8_t               __uint_least8_t;
typedef __int16_t               __int_least16_t;
typedef __uint16_t              __uint_least16_t;
typedef __int32_t               __int_least32_t;
typedef __uint32_t              __uint_least32_t;
typedef __int64_t               __int_least64_t;
typedef __uint64_t              __uint_least64_t;

/* quad_t is also 64 bits.  */
__extension__ typedef
long long int                   __quad_t;
__extension__ typedef
unsigned long long int          __u_quad_t;

/* Largest integral types.  */
__extension__ typedef
long long int                   __intmax_t;
__extension__ typedef
unsigned long long int          __uintmax_t;

/* Exact integral types.  */
/* Signed.  */
typedef __int8_t                int8_t;
typedef __int16_t               int16_t;
typedef __int32_t               int32_t;
typedef __int64_t               int64_t;

/* Unsigned.  */
typedef __uint8_t               uint8_t;
typedef __uint16_t              uint16_t;
typedef __uint32_t              uint32_t;
typedef __uint64_t              uint64_t;

/* Small types.  */
/* Signed.  */
typedef __int_least8_t          int_least8_t;
typedef __int_least16_t         int_least16_t;
typedef __int_least32_t         int_least32_t;
typedef __int_least64_t         int_least64_t;

/* Unsigned.  */
typedef __uint_least8_t         uint_least8_t;
typedef __uint_least16_t        uint_least16_t;
typedef __uint_least32_t        uint_least32_t;
typedef __uint_least64_t        uint_least64_t;

/* Fast types.  */
/* Signed.  */
typedef signed char             int_fast8_t;
typedef int                     int_fast16_t;
typedef int                     int_fast32_t;
__extension__
typedef long long int           int_fast64_t;

/* Unsigned.  */
typedef unsigned char           uint_fast8_t;
typedef unsigned int            uint_fast16_t;
typedef unsigned int            uint_fast32_t;
__extension__
typedef unsigned long long int  uint_fast64_t;

/* Largest integral types.  */
typedef __intmax_t              intmax_t;
typedef __uintmax_t             uintmax_t;

#define __INT64_C(c)            c ## LL
#define __UINT64_C(c)           c ## ULL

/* Limits of integral types.  */
/* Minimum of signed integral types.  */
#define INT8_MIN                (-128)
#define INT16_MIN               (-32767-1)
#define INT32_MIN               (-2147483647-1)
#define INT64_MIN               (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types.  */
#define INT8_MAX                (127)
#define INT16_MAX               (32767)
#define INT32_MAX               (2147483647)
#define INT64_MAX               (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
#define UINT8_MAX               (255)
#define UINT16_MAX              (65535)
#define UINT32_MAX              (4294967295U)
#define UINT64_MAX              (__UINT64_C(18446744073709551615))


/* Minimum of signed integral types having a minimum size.  */
#define INT_LEAST8_MIN          (-128)
#define INT_LEAST16_MIN         (-32767-1)
#define INT_LEAST32_MIN         (-2147483647-1)
#define INT_LEAST64_MIN         (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types having a minimum size.  */
#define INT_LEAST8_MAX          (127)
#define INT_LEAST16_MAX         (32767)
#define INT_LEAST32_MAX         (2147483647)
#define INT_LEAST64_MAX         (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types having a minimum size.  */
#define UINT_LEAST8_MAX         (255)
#define UINT_LEAST16_MAX        (65535)
#define UINT_LEAST32_MAX        (4294967295U)
#define UINT_LEAST64_MAX        (__UINT64_C(18446744073709551615))


/* Minimum of fast signed integral types having a minimum size.  */
#define INT_FAST8_MIN           (-128)
#define INT_FAST16_MIN          (-2147483647-1)
#define INT_FAST32_MIN          (-2147483647-1)
#define INT_FAST64_MIN          (-__INT64_C(9223372036854775807)-1)
/* Maximum of fast signed integral types having a minimum size.  */
#define INT_FAST8_MAX           (127)
#define INT_FAST16_MAX          (2147483647)
#define INT_FAST32_MAX          (2147483647)
#define INT_FAST64_MAX          (__INT64_C(9223372036854775807))

/* Maximum of fast unsigned integral types having a minimum size.  */
#define UINT_FAST8_MAX          (255)
#define UINT_FAST16_MAX         (4294967295U)
#define UINT_FAST32_MAX         (4294967295U)
#define UINT_FAST64_MAX         (__UINT64_C(18446744073709551615))


/* Values to test for integral types holding `void *' pointer.  */
#define INTPTR_MIN              (-2147483647-1)
#define INTPTR_MAX              (2147483647)
#define UINTPTR_MAX             (4294967295U)


/* Minimum for largest signed integral type.  */
#define INTMAX_MIN              (-__INT64_C(9223372036854775807)-1)
/* Maximum for largest signed integral type.  */
#define INTMAX_MAX              (__INT64_C(9223372036854775807))

/* Maximum for largest unsigned integral type.  */
#define UINTMAX_MAX             (__UINT64_C(18446744073709551615))


/* Limits of other integer types.  */
/* Limits of `ptrdiff_t' type.  */
#define PTRDIFF_MIN             (-2147483647-1)
#define PTRDIFF_MAX             (2147483647)

/* Limits of `sig_atomic_t'.  */
#define SIG_ATOMIC_MIN          (-2147483647-1)
#define SIG_ATOMIC_MAX          (2147483647)

/* Limit of `size_t' type.  */
#define SIZE_MAX                (4294967295U)

/* Limits of `wint_t'.  */
#define WINT_MIN                (0u)
#define WINT_MAX                (4294967295u)

/* Signed.  */
#define INT8_C(c)               c
#define INT16_C(c)              c
#define INT32_C(c)              c
#define INT64_C(c)              c ## LL

/* Unsigned.  */
#define UINT8_C(c)              c
#define UINT16_C(c)             c
#define UINT32_C(c)             c ## U
#define UINT64_C(c)             c ## ULL

/* Maximal type.  */
#define INTMAX_C(c)             c ## LL
#define UINTMAX_C(c)            c ## ULL

#endif /* _STDINT_H */

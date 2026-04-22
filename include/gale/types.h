/** \file
 *  Basic type definitions.
 *  These are the data types widely used within Gale to represent basic
 *  concepts like strings, numbers, times, etc. */

#ifndef GALE_TYPES_H
#define GALE_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "gale/compat.h"
#include "gale/config.h"

/** 32-bit unsigned integer. */
typedef uint32_t u32;
/** 32-bit signed integer. */
typedef int32_t s32;

/** 16-bit unsigned integer. */
typedef uint16_t u16;

/** 8-bit unsigned integer (byte). */
typedef unsigned char u8;

/** Alias for ::u8. */
typedef u8 byte;

/** Unicode character (UTF-32). */
typedef wchar_t wch;	/* wide char */

/** A counted buffer of untyped data. */
struct gale_data {
	/** Pointer to buffer. */
	byte *p;
        /** Length of buffer in bytes. */
	size_t l;
};

/** A constant, counted buffer of Unicode (UTF-32) text. */
struct gale_text {
	/** Pointer to buffer. */
	const wch *p;
        /** Length of buffer in characters. */
	size_t l;
};

/** An absolute or relative time value, with sufficient range and precision. 
 *  The time is represented by the number of seconds since the Unix epoch
 *  (January 1, 1970, UTC). */
struct gale_time {
	/** High four bytes of the number of seconds since the epoch 
         *  (zero for all times Unix can actually represent with time_t). */
	s32 sec_high;
        /** Low four bytes of the number of seconds since the epoch. */
	u32 sec_low;
	/** High four bytes of the fractional part of the second
         *  (a value of '1' indicates 1/(2^32) of a second). */ 
	u32 frac_high;
	/** Low four bytes of the fractional part of the second
         *  (a value of '1' indicates 1/(2^64) of a second). */ 
	u32 frac_low;
};

struct gale_fragment;

/** A collection of ::gale_fragment values (LISP 'alist'). */
struct gale_group {
	/** Counted array of ::gale_fragment structures. */
	const struct gale_fragment *list;
	/** Size of array in fragments. */
	size_t len;
	/** "Chain" to next group (so arrays don't have to grow). */
	const struct gale_group *next;
};

/** Data types for ::gale_fragment. */
enum gale_fragment_type { 
	frag_text, frag_data, frag_time, frag_number, frag_group 
};

/** A named value with a variant type. */
struct gale_fragment {
	/** Name of the value. */
	struct gale_text name;
	/** Type of the value. */
	enum gale_fragment_type type;
	/** The value itself; which branch is occupied depends
	    on the value of type. */
	union {
		struct gale_text text;
		struct gale_data data;
		struct gale_time time;
		struct gale_group group;
		s32 number;
	} value;
};

#endif

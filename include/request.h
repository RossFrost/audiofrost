/* NIST Secure Hash Algorithm */
/* heavily modified by Uwe Hollerbach <uh@alumni.caltech edu> */
/* from Peter C. Gutmann's implementation as found in */
/* Applied Cryptography by Bruce Schneier */
/* This code is in the public domain */
/* $Id$ */

#include <stdlib.h>
#include <stdio.h>


/* Useful defines & typedefs */
typedef unsigned char SHA_BYTE;	/* 8-bit quantity */
typedef unsigned long SHA_LONG;	/* 32-or-more-bit quantity */

#define SHA_BLOCKSIZE		64
#define SHA_DIGESTSIZE		20

typedef struct {
    SHA_LONG digest[5];		/* message digest */
    SHA_LONG count_lo, count_hi;	/* 64-bit bit count */
    SHA_BYTE data[SHA_BLOCKSIZE];	/* SHA data buffer */
    size_t local;			/* unprocessed amount in data */
} SHA_INFO;



#define SHA_BYTE_ORDER 1234

void sha_update(
    SHA_INFO *sha_info, 
    SHA_BYTE *buffer, 
    size_t count
);


void sha_final(
    unsigned char digest[20], 
    SHA_INFO *sha_info
);


unsigned char *rfc822_binary(
    void *src,
    unsigned long srcl,
    unsigned long *len
);
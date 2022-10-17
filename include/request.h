#include <stdlib.h>
#include <stdio.h>

typedef unsigned char SHA_BYTE;	
typedef unsigned long SHA_LONG;	

#define SHA_BLOCKSIZE 64

#define SHA_DIGESTSIZE 20

#define MB_TOC_STRING_LENGTH (3 + 3 + 100*7)

#define MB_DISC_ID_LENGTH 32

#define MB_ERROR_MSG_LENGTH	255

#define MCN_STR_LENGTH	13

#define ISRC_STR_LENGTH	12

#define MAX_DISC_LENGTH	(90 * 60 * 75)

#if __BYTE_ORDER___ == __ORDER_BIG_ENDIAN__
#  if __SIZEOF_LONG__ == 4
#    define SHA_BYTE_ORDER  4321
#  elif __SIZEOF_LONG__  == 8
#    define SHA_BYTE_ORDER  87654321
#  endif
#else
#  if __SIZEOF_LONG__ == 4
#    define SHA_BYTE_ORDER  1234
#  elif __SIZEOF_LONG__ == 8
#    define SHA_BYTE_ORDER  12345678
#  endif
#endif


typedef struct {
    SHA_LONG digest[5];		
    SHA_LONG count_lo, count_hi;	
    SHA_BYTE data[SHA_BLOCKSIZE];	
    size_t local;			
} SHA_INFO;



void sha_init(SHA_INFO *);
void sha_update(SHA_INFO *, SHA_BYTE *, size_t);
void sha_final(unsigned char [20], SHA_INFO *);
void sha_stream(unsigned char [20], SHA_INFO *, FILE *);
void sha_print(unsigned char [20]);
char *sha_version(void);

unsigned char *rfc822_binary (void *src,unsigned long srcl,unsigned long *len);
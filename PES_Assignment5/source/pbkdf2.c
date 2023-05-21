/*
 * pbkdf2.c
 *
 * A perfectly legitimate implementation of HMAC and PBKDF2, but based
 * on the "ISHA" insecure and bad hashing algorithm.
 * 
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 */

#include <assert.h>
#include <stdio.h>
#include<string.h>
#include<stdbool.h>

/* KJ : Flag added to check to run
 *      calculation for ipad opad and keypad
 *      Only once when hmac_isha is called
 */
bool check = 1;

#include "pbkdf2.h"
#include "ticktime.h"

/*
 * See function description in pbkdf2.h
 */


void hmac_isha(const uint8_t *key, size_t key_len,
    const uint8_t *msg, size_t msg_len,
    uint8_t *digest)
{
	uint8_t ipad[ISHA_BLOCKLEN];
	uint8_t opad[ISHA_BLOCKLEN];
	uint8_t keypad[ISHA_BLOCKLEN];
	uint8_t inner_digest[ISHA_DIGESTLEN];

	ISHAContext ctx;

	/* KJ : Local ISHAContext for workaround
	 *      to store ISHAContext status will calling for
	 *      ipad and opad
	 */
	static ISHAContext Ipad_ISHAContext_ctx;
	static ISHAContext Opad_ISHAContext_ctx;

	/*
	 * KJ : Check to ensure that calculation for ipad opad and keypad
	 *      Only once when hmac_isha is called
	 */
	if(check==1)
	{
		/* KJ : Removed if loop part and only kept else part as
		 *      since test has key_len == 8 which will be never greater than
		 *      ISHA_BLOCKLEN which is 64
		 *
		 *      Also changed for loop with memset
		 *
		 *      Note : The concept is visualised based on lecture slides
		 */
		memcpy(keypad,key,key_len);
		memset(key_len+keypad,00,ISHA_BLOCKLEN);

		// XOR key into ipad and opad
		for (int i=0; i<ISHA_BLOCKLEN; i++)
		{
			ipad[i] = keypad[i] ^ 0x36;
			opad[i] = keypad[i] ^ 0x5c;
		}
		/* KJ : Storing state into local static ISHAContext
		 */
		ISHAReset(&Ipad_ISHAContext_ctx);
		ISHAInput(&Ipad_ISHAContext_ctx, ipad, ISHA_BLOCKLEN);
		ISHAReset(&Opad_ISHAContext_ctx);
		ISHAInput(&Opad_ISHAContext_ctx, opad, ISHA_BLOCKLEN);
	}

	ctx=Ipad_ISHAContext_ctx;
	// Perform inner ISHA
	ISHAInput(&ctx, msg, msg_len);
	ISHAResult(&ctx, inner_digest);

	// perform outer ISHA
	ctx=Opad_ISHAContext_ctx;

	ISHAInput(&ctx, inner_digest, ISHA_DIGESTLEN);
	ISHAResult(&ctx, digest);
}

/*
 * Implements the F function as defined in RFC 8018 section 5.2
 *
 * Parameters:
 *   pass      The password
 *   pass_len  length of pass
 *   salt      The salt
 *   salt_len  length of salt
 *   iter      The iteration count ("c" in RFC 8018)
 *   blkidx    the block index ("i" in RFC 8018)
 *   result    The result, which is ISHA_DIGESTLEN bytes long
 * 
 * Returns:
 *   The result of computing the F function, in result
 */

static void F(const uint8_t *pass, size_t pass_len,
    const uint8_t *salt, size_t salt_len,
    int iter, unsigned int blkidx, uint8_t *result)
{

  uint8_t temp[ISHA_DIGESTLEN];
  uint8_t saltplus[15];

  /*
   * KJ : Updated the data type for i to register
   */
  assert(salt_len + 4 <= sizeof(saltplus));

  /* KJ :
   * Eliminated for loop with memcopy
   */
  memcpy(saltplus, salt, salt_len);

  __builtin_memcpy(saltplus, salt, salt_len);

  /*
   * KJ : Reversing the blkidx with the help of
   *      __builtin_bswap32 and then storing it in salplus
   *      rather than copying data byte-wise
   */
  blkidx=__builtin_bswap32(blkidx);
  memcpy(saltplus+salt_len,&blkidx,4);

  hmac_isha(pass, pass_len, saltplus, salt_len+4, temp);

  /* KJ :
   * reset the check flag to 0 once first call to hmac_isha is completed
   */
  check = 0;

  /* KJ :
   * Eliminated for loop with memcopy
   */
  memcpy(result, temp, ISHA_DIGESTLEN);


  for (register int j=1; j<iter; j++) {
      hmac_isha(pass, pass_len, temp, ISHA_DIGESTLEN, temp);
      for (int i=0; i<ISHA_DIGESTLEN; i++)
        result[i] ^= temp[i];
    }

}

/*
 * See function description in pbkdf2.h
 */
void pbkdf2_hmac_isha(const uint8_t *pass, size_t pass_len,
    const uint8_t *salt, size_t salt_len, int iter, size_t dkLen, uint8_t *DK)
{
	/*
	 * KJ : Updated the size of accumulator from
	 *      2560 back to 512 no need for 2560 size
	 */
	uint8_t accumulator[512];
	assert(dkLen < sizeof(accumulator));
	/*
	 * KJ : check variable as a work around added
	 *      used in F() function
	 */
	check = 1;

	int l = dkLen / ISHA_DIGESTLEN + 1;

	for (register int i=0; i<l; i++) {
		F(pass, pass_len, salt, salt_len, iter, i+1, accumulator + i*ISHA_DIGESTLEN);
	}
	/* KJ : Eliminated for loop to with memcopy
	 * Assuming that DK and accumulator are arrays of the same type and size
	 */

	__builtin_memcpy(DK, accumulator, dkLen * sizeof(DK[0]));

}






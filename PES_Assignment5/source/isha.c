/*
 * isha.c
 *
 * A completely insecure and bad hashing algorithm, based loosely on
 * SHA-1 (which is itself no longer considered a good hashing
 * algorithm)
 *
 * Based on code for sha1 processing from Paul E. Jones, available at
 * https://www.packetizer.com/security/sha1/
 */
#include <assembly_ISHAProcessMessageBlock.h>
#include <string.h>
#include "isha.h"
/*
 * circular shift macro
 */
/* KJ : Removed macro defination
 *      Functionality is updated in assembly file
 *
 */

/* KJ : Function ISHAProcessMessageBlock is implemented in
 *      assembly please read me for more details
 */

/*  
 * The message must be padded to an even 512 bits.  The first padding
 * bit must be a '1'.  The last 64 bits represent the length of the
 * original message.  All bits in between should be 0. This function
 * will pad the message according to those rules by filling the MBlock
 * array accordingly. It will also call ISHAProcessMessageBlock()
 * appropriately. When it returns, it can be assumed that the message
 * digest has been computed.
 *
 * Parameters:
 *   ctx         The ISHAContext (in/out)
 */

static void ISHAPadMessage(ISHAContext *ctx)
{
/*
 *  Check to see if the current message block is too small to hold
 *  the initial padding bits and length.  If so, we will pad the
 *  block, process it, and then continue padding into a second
 *  block.
 */
	/* KJ :	ctx->MBlock[ctx->MB_Idx++] = 0x80;
	 *      called inside function for both if and else condition and
	 *      was not doing same changes so added at the top
	 */
	ctx->MBlock[ctx->MB_Idx++] = 0x80;
	if (ctx->MB_Idx > 55)
	{
		 /* KJ : Updated while loop with memset
		  */
		__builtin_memset(ctx->MBlock + ctx->MB_Idx, 0, 64 - ctx->MB_Idx);

		ISHAProcessMessageBlock(ctx);

		/* KJ : Updated while loop with memset
		 */
		__builtin_memset(ctx->MBlock, 0, 60);
	}
	else
	{
		/* KJ : Updated while loop with memset
		 */
		__builtin_memset(ctx->MBlock + ctx->MB_Idx, 0, 60 - ctx->MB_Idx);
	}

    /*
     *  Store the message length as the last 8 octets
     */

	/* KJ : replace byte by bte transfer with btswap32 function
	 *
	 */
	*(uint32_t *)(ctx->MBlock+60) = __builtin_bswap32(ctx->Length);
	ISHAProcessMessageBlock(ctx);
}


void ISHAReset(ISHAContext *ctx)
{
	/* KJ : Replaced with single length
	 *      variable
	 */
	ctx->Length  	 = 0;
	ctx->MB_Idx      = 0;
	ctx->MD[0]       = 0x67452301;
	ctx->MD[1]       = 0xEFCDAB89;
	ctx->MD[2]       = 0x98BADCFE;
	ctx->MD[3]       = 0x10325476;
	ctx->MD[4]       = 0xC3D2E1F0;
	ctx->Computed    = 0;
	ctx->Corrupted   = 0;

	return;
}

void ISHAResult(ISHAContext *ctx, uint8_t *digest_out)
{
	/* KJ : Deleting the corrupted check as per lecture slides
	 *
	 */
	if (!ctx->Computed)
	{
		ISHAPadMessage(ctx);
		ctx->Computed = 1;
	}

	/* KJ : Updated the byte by byte transfer with
	 *      bsswao32 function to eliminate for loop
	 *      limitations
	 */
	*((uint32_t *)(digest_out )) = __builtin_bswap32(ctx->MD[0]);
	*((uint32_t *)(digest_out + 4)) = __builtin_bswap32(ctx->MD[1]);
	*((uint32_t *)(digest_out + 8)) = __builtin_bswap32(ctx->MD[2]);
	*((uint32_t *)(digest_out + 12)) = __builtin_bswap32(ctx->MD[3]);
	*((uint32_t *)(digest_out + 16)) = __builtin_bswap32(ctx->MD[4]);

	return;
}

void ISHAInput(ISHAContext *ctx, const uint8_t *message_array, size_t length)
{

  /* KJ : Removed first two if conditions as
   *      length will never be zero
   */
  /* KJ : Line called inside loop multiple times
   *      but not updated everytime replaced at top
   *      to reduce no of iterations
   */
  ctx->Length += 8 * length;

  for(register int i =length; i>0; i--)
  	{
	  /* KJ : Removed not required ANDING with
	   *      0xFFFFFFFF
	   *      Removed if check when data is corrupted as per
	   *      lecture slides
	   */
	    ctx->MBlock[ctx->MB_Idx++] = (*message_array & 0xFF);

  		if (ctx->MB_Idx == 64)
  		{
  			ISHAProcessMessageBlock(ctx);
  		}
  	message_array++;
  	}
  return;
}

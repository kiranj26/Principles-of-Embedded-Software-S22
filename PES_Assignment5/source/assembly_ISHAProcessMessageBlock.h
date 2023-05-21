#ifndef _ASSEMBLY_ISHARESET_H_
#define _ASSEMBLY_ISHARESET_H_
#include "isha.h"


/**
 * ISHAProcessMessageBlock - Processes a message block for the ISHA hashing algorithm.
 *
 * @param ctx: A pointer to the ISHAContext struct.
 *
 * This function processes a message block for the ISHA hashing algorithm.
 * It updates the context state with the intermediate hash value after processing the block.
 */

void ISHAProcessMessageBlock(ISHAContext *ctx);


#endif /* _ASSEMBLY_ISHARESET_H_ */

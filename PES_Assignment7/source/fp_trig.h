/*
 * fp_trig.h: a fixed-point implementation of sin and cos (and their
 * inverses)
 *
 * Howdy Pierce, howdy@cardinalpeak.com
 */

#include <stdint.h>

#ifndef _TRIG_H_
#define _TRIG_H_

/*
 * Both inputs and outputs are scaled by TRIG_SCALE_FACTOR. 
 *
 * Since the output of sin/cos vary in the range [-1, 1], setting this
 * to 2037 means that all results fit into 10 bits of resolution and
 * are therefore useful for a 10-bit DAC.
 *
 * You might be asking, why not set TRIG_SCALE_FACTOR to 2047 instead,
 * to _fully_ cover the 10 bit range?  With TRIG_SCALE_FACTOR at 2047,
 * then PI/2 ends up being 3215, which does not have a lot of factors
 * -- its prime factorization is (5, 643). Whereas if
 * TRIG_SCALE_FACTOR is 2037, then PI/2 works out to be 3200, which is
 * interestingly factorable.
 */
#define TRIG_SCALE_FACTOR  	(2037)
#define HALF_PI            	(3200)   // pi * TRIG_SCALE_FACTOR / 2
#define PI                 	(6399)   // pi * TRIG_SCALE_FACTOR
#define TWO_PI            	(12799)  // 2 * pi * TRIG_SCALE_FACTOR

/*
 * Converts from degrees (unscaled) into radians (scaled)
 *
 * Parameters:
 *    degrees  An angle, expressed in degrees (with no scaling). 
 * 
 * Returns:
 *    (PI * degrees / 180) -- that is, the angle measured in radians,
 *    using scaled units.
 */
int32_t fp_radians(int degrees);


/*
 * Computes sine of x, measured in radians, using a lookup table
 *
 * Parameters:
 *    x     Expressed in radians * TRIG_SCALE_FACTOR
 * 
 * Returns:
 *    sin(x) * SCALE_FACTOR
 * 
 * Therefore output will be in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR]
 */
int32_t fp_sin(int32_t x);

/*
 * Computes sine of x, measured in radians, using a Taylor series
 *
 * Parameters:
 *    x     Expressed in radians * TRIG_SCALE_FACTOR
 * 
 * Returns:
 *    sin(x) * SCALE_FACTOR
 * 
 * Therefore output will be in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR]
 */
int32_t taylor_fp_sin(int32_t x);


/*
 * Computes triangle of x, measured in radians, using an interpolation
 *
 * Parameters:
 *    x     Expressed in radians * TRIG_SCALE_FACTOR
 * 
 * Returns:
 *    sin(x) * SCALE_FACTOR
 * 
 * Therefore output will be in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR]
 */
int32_t fp_triangle(int32_t x);



/*
 * Computes cosine of x, measured in radians, using a lookup table
 *
 * Parameters:
 *    x     Expressed in radians * TRIG_SCALE_FACTOR
 * 
 * Returns:
 *    cos(x) * SCALE_FACTOR
 * 
 * Therefore output will be in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR]
 */
int32_t fp_cos(int32_t x);


/*
 * Computes arc sine of x, using a lookup table
 *
 * Parameters:
 *    x     Input value
 *          Must be in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR]
 *
 * Returns:
 *    The arc sine, which will be in the range [-HALF_PI, HALF_PI]
 */
int32_t fp_asin(int32_t x);


/*
 * Computes arc cosine of x, using a lookup table
 *
 * Parameters:
 *    x     Input value
 *          Must be in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR]
 *
 * Returns:
 *    The arc cosine, which will be in the range [-HALF_PI, HALF_PI]
 */
int32_t fp_acos(int32_t x);


/*
 * Performs linear interpolation using fixed-point math
 *
 * Parameters:
 *    x       Input x value
 *    x1, y1  First point for interpolation
 *    x2, y2  Second point for interpolation
 * 
 * Returns:
 *    The value y such that (x,y) sits on the line between (x1,y1) and
 *    (x2,y2)
 */
int32_t fp_interpolate(int32_t x, int32_t x1, int32_t y1,
    int32_t x2, int32_t y2);

#endif  // _TRIG_H_

/*
 * test_sine.c: File with test for your sine function.
 *
 *  Created on: Apr 25, 2022
 *      Author: lpandit
 */
#include <stdio.h>
#include <math.h>

#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "fp_trig.h"
#include "test_sine.h"

/*
 * Test the sine function.
 *
 * Your sin function should accept inputs in the range [INT_MIN, INT_MAX] and
 * produce outputs in the range [-TRIG_SCALE_FACTOR, TRIG_SCALE_FACTOR].
 *
 * Your code needs to provide sine.h which should declare TWO_PI and TRIG_SCALE_FACTOR.
 *
 * Ensure that max_err is <= 2.0 and sum_sq error is <= 12000.
 */
void test_sin()
{
  double act_sin;
  double exp_sin;
  double err;
  double sum_sq = 0;
  double max_err = 0;

  for (int i=-TWO_PI; i <= TWO_PI; i++) {
    exp_sin = sin( (double)i / TRIG_SCALE_FACTOR) * TRIG_SCALE_FACTOR;
    act_sin = fp_sin(i);

    err = act_sin - exp_sin;
    if (err < 0)
      err = -err;

    if (err > max_err)
      max_err = err;
    sum_sq += err*err;
  }

  if (max_err > 2.0 || sum_sq > 12000)
  {
	  PRINTF("Error: Do not proceed. Your sine function needs work\n\r");
  }
  else
  {
	  PRINTF("Pass: Your sine function meets the accuracy criteria\n\r");

  }

  PRINTF("Results:\n\r");
  PRINTF(" - Maximum error: %d\n\r", (int)(max_err));
  PRINTF(" - Sum-of-squares error: %d\n\r", (int) (sum_sq));


}

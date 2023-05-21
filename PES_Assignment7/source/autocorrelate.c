/*
 * autocorrelate.c: Detect the period of the fundamental frequency in
 * a buffer full of samples
 *
 * Howdy Pierce, howdy@cardinalpeak.com
 * 
 * Good explanation at
 * https://www.instructables.com/Reliable-Frequency-Detection-Using-DSP-Techniques/
 *
 *   (although his code is poorly written and has a bug, so I wrote this myself)
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "autocorrelate.h"


/*
 * See documentation in .h file
 */
int
autocorrelate_detect_period(void *samples, uint32_t nsamp,
    autocorrelate_sample_format_t format)
{
  int32_t sum = 0;
  int prev_sum = 0;
  int32_t thresh = 0;
  bool slope_positive = false;

  int32_t s1 = 0;
  int32_t s2 = 0;
  
  sum = 0;
  for (int i=0; i < nsamp; i++) {
    prev_sum = sum;
    sum = 0;

    for (int k=0; k < nsamp - i; k++) {

      switch (format) {

      case kAC_12bps_unsigned:
        s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 11);
        s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 11);
        sum += (s1 * s2) >> 12;
        break;

      case kAC_16bps_unsigned:
        s1 = (int32_t)*((uint16_t*)samples + k) - (1 << 15);
        s2 = (int32_t)*((uint16_t*)samples + k+i) - (1 << 15);
        sum += (s1 * s2) >> 16;
        break;

      case kAC_12bps_signed:
      case kAC_16bps_signed:
        s1 = *((int16_t*)samples + k);
        s2 = *((int16_t*)samples + k+i);
        sum += (s1 * s2) >> (format == kAC_12bps_signed ? 12 : 16);
        break;
      }
    }
    
    if (i == 0) {
      thresh = sum / 2;

    } else if ((sum > thresh) && (sum - prev_sum > 0)) {
      // slope is positive, so now enter mode where we're looking for
      // negative slope
      slope_positive = true;

    } else if (slope_positive && (sum - prev_sum) <= 0) {
      // We have crested the peak and started down the other
      // side; actual peak was one sample back
      return i-1;
    }
  }

  // no correlation found
  return -1;
}


//#define TESTING

#ifdef TESTING

#include <stdio.h>
#include "fp_trig.h"

#define BUF_SIZE 1024

int main()
{
  int16_t signed_12bps_test[BUF_SIZE];
  uint16_t unsigned_12bps_test[BUF_SIZE];
  int16_t signed_16bps_test[BUF_SIZE];
  uint16_t unsigned_16bps_test[BUF_SIZE];

  // In theory the autocorrelate function should be dead-nuts on. In
  // practice, there is some slop owing to integer math
  const int slop = 2;  

  for (int period = 12; period <= 240; period += 12) {

    for (int i=0; i < BUF_SIZE; i++) {
      signed_12bps_test[i] = fp_sin(i * TWO_PI / period);
      //signed_12bps_test[i] = fp_triangle(i * TWO_PI / period);
      unsigned_12bps_test[i] = signed_12bps_test[i] + TRIG_SCALE_FACTOR;
      signed_16bps_test[i] = signed_12bps_test[i] << 4;
      unsigned_16bps_test[i] = unsigned_12bps_test[i] << 4;
    }

    int res1 = autocorrelate_detect_period(signed_12bps_test, BUF_SIZE, kAC_12bps_signed);
    int res2 = autocorrelate_detect_period(unsigned_12bps_test, BUF_SIZE, kAC_12bps_unsigned);
    int res3 = autocorrelate_detect_period(signed_16bps_test, BUF_SIZE, kAC_16bps_signed);
    int res4 = autocorrelate_detect_period(unsigned_16bps_test, BUF_SIZE, kAC_16bps_unsigned);

    assert(period-res1 <= slop && res1-period <= slop);
    assert(period-res2 <= slop && res2-period <= slop);
    assert(period-res3 <= slop && res3-period <= slop);
    assert(period-res4 <= slop && res4-period <= slop);
  }
}

#endif

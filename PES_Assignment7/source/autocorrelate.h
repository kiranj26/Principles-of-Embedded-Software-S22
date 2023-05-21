/*
 * autocorrelate.h: Detect the period of the fundamental frequency in
 * a buffer full of samples
 *
 * Howdy Pierce, howdy@cardinalpeak.com
 */

#ifndef _AUTOCORRELATE_H_
#define _AUTOCORRELATE_H_

#include <stdint.h>

typedef enum {
  kAC_12bps_unsigned,   // 12 bits per sample, unsigned samples (stored in 16 bits)
  kAC_16bps_unsigned,   // 16 bits per sample, unsigned samples
  kAC_12bps_signed,     // 12 bits per sample, signed samples (stored in 16 bits)
  kAC_16bps_signed      // 16 bits per sample, signed samples
} autocorrelate_sample_format_t;
  

/*
 * Determine the fundamental period of a waveform using
 * autocorrelation
 *
 * Parameters:
 *   samples   Array of samples
 *   nsamp     Number of samples
 *   format    The format for the samples (see above)
 * 
 * Returns:
 *   The recovered fundamental period of the waveform, expressed in
 *   number of samples, or -1 if no correlation was found
 */
int autocorrelate_detect_period(void *samples, uint32_t nsamp,
    autocorrelate_sample_format_t format);


#endif  //  _AUTOCORRELATE_H_

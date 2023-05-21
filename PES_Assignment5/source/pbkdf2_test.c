/*
 * pbkdf2_test_s23.c
 *
 * Test functions for pbkdf2
 * 
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "isha.h"
#include "pbkdf2.h"
#include "pbkdf2_test.h"


/* 
 * Compares two byte strings; returns true if they match, false
 * otherwise
 * 
 * Parameters:
 *   b1, b2    The strings to be compared
 *   len       The length of the strings
 */
bool cmp_bin(const uint8_t *b1, const uint8_t *b2, size_t len)
{
  for (size_t i=0; i<len; i++)
    if (b1[i] != b2[i])
      return false;
  return true;
}

/*
 * Returns the integer corresponding to the given hex character
 */
static unsigned char hexdigit_to_int(char c)
{
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  if (c >= '0' && c <= '9')
    return c - '0';
  assert(0);
}


/*
 * Convert a hex string into a binary value
 *
 * Parameters:
 *   out         Output binary value
 *   in_str      Input hex string
 *   binary_len  The length of the binary output, in bytes. 
 *                 in_str must be 2x this length
 * 
 * Returns:
 *   The converted string, in out
 */
void hexstr_to_bytes(uint8_t *out, const char *in_str, size_t binary_len)
{
  for (size_t i=0; i<binary_len; i++) 
    out[i] = hexdigit_to_int(in_str[i*2]) << 4 | hexdigit_to_int(in_str[i*2+1]);
}

/*
 * Convert a byte array into a hex string.
 *
 * Parameters:
 *     out_str      Output hex string
 *     in           Input binary array
 *     binary_len   Length of binary input
 *
 */
void bytes_to_hexstr(char *out_str, const uint8_t *in, size_t binary_len)
{
   int i;

   char *ptr = out_str;
   for (i=0; i < binary_len; i++)
   {
	   ptr += sprintf(ptr, "%02X", in[i]);
   }
}

#define min(a,b)  ((a)<(b)?(a):(b))

/*
 * Tests the ISHA functions. Returns true if all tests pass, false
 * otherwise. Diagnostic information is printed via printf.
 */
bool test_isha()
{
  typedef struct {
    const char *msg;
    const char *hexdigest;
  } test_matrix_t;

  test_matrix_t tests[] =
    { {"abc", "30BC4FFDB497427F3C9A845987D8B126DC7A69B4"},
      {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
       "F915004A6B20756A33B1C9C8CA6A1C9CB268BE52"},
      {"Nobody inspects the spammish repetition",
       "46746F852C9C9FF187C16241DB36395C6E4C963C"},
      {"Now his life is full of wonder/But his heart still knows some fear/Of a simple thing, he cannot comprehend/Why they try to tear the mountains down/To bring in a couple more/More people, more scars upon the land", "92BE8A92D3C29641BADE5A8E290A8EDC2887B450"}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  uint8_t exp_digest[ISHA_DIGESTLEN];
  uint8_t act_digest[ISHA_DIGESTLEN];
  int msglen;
  ISHAContext ctx;
      
  // First time through: Single call to ISHAInput per test
  for (int i=0; i<num_tests; i++) {
    msglen = strlen(tests[i].msg);
    hexstr_to_bytes(exp_digest, tests[i].hexdigest, ISHA_DIGESTLEN);

    ISHAReset(&ctx);
    ISHAInput(&ctx, (const unsigned char *)tests[i].msg, msglen);
    ISHAResult(&ctx, act_digest);

    if (cmp_bin(act_digest, exp_digest, ISHA_DIGESTLEN)) {
      printf("%s test %d: success\r\n", __FUNCTION__, i);
      tests_passed++;
    } else {
      printf("%s test %d: FAILURE\r\n", __FUNCTION__, i);
    }
  }

  // Second time through: Deliver data in 10-byte chunks to ISHAInput
  for (int i=0; i<num_tests; i++) {
    const unsigned char *data = (const unsigned char *)tests[i].msg;
    msglen = strlen(tests[i].msg);
    hexstr_to_bytes(exp_digest, tests[i].hexdigest, ISHA_DIGESTLEN);

    ISHAReset(&ctx);
    while (msglen > 0) {
      int bytes_this_pass = min(10, msglen);
      ISHAInput(&ctx, data, bytes_this_pass);
      msglen -= bytes_this_pass;
      data += bytes_this_pass;
    }

    ISHAResult(&ctx, act_digest);

    if (cmp_bin(act_digest, exp_digest, ISHA_DIGESTLEN)) {
      printf("%s test %d: success\r\n", __FUNCTION__, i + num_tests);
      tests_passed++;
    } else {
      printf("%s test %d: FAILURE\r\n", __FUNCTION__, i + num_tests);
    }
  }

  return (num_tests*2 == tests_passed);
}


/*
 * Tests the hmac function. Returns true if all tests pass, false
 * otherwise. Diagnostic information is printed via printf.
 */
bool test_hmac_isha()
{
  typedef struct {
    const char *key;
    const char *msg;
    const char *hexdigest;
  } test_matrix_t;

  test_matrix_t tests[] =
    { {"Colorado", "This is a test", "F3564AC6FF135F1B9DA42327E02A131C16C7D17C"},
      {"Jefe", "what do ya want for nothin?", "F8AC17455973751C32AF58F3B71C05C116E2E5AC"},
      {"RFC 2104", "HMAC: Keyed-Hashing for Message Authentication",
       "D224C2883880F114268EBD7A687CE263B3674397"}
    };
  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  uint8_t exp_digest[ISHA_DIGESTLEN];
  uint8_t act_digest[ISHA_DIGESTLEN];
  int keylen, msglen;
      
  for (int i=0; i<num_tests; i++) {

    keylen = strlen(tests[i].key);
    msglen = strlen(tests[i].msg);

    hexstr_to_bytes(exp_digest, tests[i].hexdigest, ISHA_DIGESTLEN);
    hmac_isha((uint8_t*)tests[i].key, keylen, (uint8_t*)tests[i].msg, msglen, act_digest);
    
    if (cmp_bin(act_digest, exp_digest, ISHA_DIGESTLEN)) {
      printf("%s test %d: success\r\n", __FUNCTION__, i);
      tests_passed++;
    } else {
      printf("%s test %d: FAILURE\r\n", __FUNCTION__, i);
    }
  }

  return (num_tests == tests_passed);
}


/*
 * Tests the pbkdf2_hmac_isha function. Returns true if all tests pass, false
 * otherwise. Diagnostic information is printed via printf.
 */
bool test_pbkdf2_hmac_isha()
{
  typedef struct {
    const char *pass;
    const char *salt;
    int iterations;
    size_t dk_len;
    const char *hex_result;  // expected result, as a hex string
  } test_matrix_t;

  test_matrix_t tests[] =
    { {"password", "mysalt", 1, 20, "2DD452020DBCAB7AC9E7736889E67991E74B3430"},
      {"password", "mysalt", 1, 21, "2DD452020DBCAB7AC9E7736889E67991E74B34307F"},
      {"password", "mysalt", 1, 32, "2DD452020DBCAB7AC9E7736889E67991E74B34307F6607979687B2F02F9DAE88"},
      {"password", "mysalt", 1, 64, "2DD452020DBCAB7AC9E7736889E67991E74B34307F6607979687B2F02F9DAE8887BA9C8CBF59274474BD9B630F730051217ABB7DE4C7F6D400B240A24D10D490"},
      {"password", "mysalt", 1, 200, "2DD452020DBCAB7AC9E7736889E67991E74B34307F6607979687B2F02F9DAE8887BA9C8CBF59274474BD9B630F730051217ABB7DE4C7F6D400B240A24D10D490363115B613911465397CEC414F0F594A56FD5A59AC823C11DF3529EDF60128BEA2E0A11602D56ED39C8DFCBF86B51DB294F39DC0EB170EFB58F3DB233732566D800F8D7E614A4BDC2729A20CED65BB4A3FE29AC181734F14CE2FA12F65F1591900E73A3B8979F0CE42B44B924F3548BEF7D60B74F7C6D9BFFDD77A2707B2E10A145F52FC0D597302"},
      {"password", "mysalt", 2, 20, "237313231D10DEBD6FA9D48A480402D6ADC049FA"},
      {"password", "mysalt", 2, 64, "237313231D10DEBD6FA9D48A480402D6ADC049FA8241FAEEF2275CE0E82CA10B0DE65B0403755FA9A0CF2D4E63DDA222290F1A304BC0048AD942AA450BF17658"},
      {"password", "mysalt", 3, 20, "74E2991C956738DA4A728E1D9FC61DD699E77420"},
      {"password", "mysalt", 100, 20, "7FF59582146CA8F22495A4FD36B95A7CE05714E8"},
      {"password", "mysalt", 100, 64, "7FF59582146CA8F22495A4FD36B95A7CE05714E804C3B189DE09433F820CC2F519DB5EE967C09CD28C7F6F99B21A88C17DB320B43A8D76C074BF5F074DC83055"},
      {"Boulder", "Buffaloes", 100, 64, "A345C6977A4F5C16881B9D94AC4FCEFCA152BE863BA6C6B7665831638BE49277B8024B09349EE0D044DDE8CD994D9E40A6EA60507C0C398D4AEFEB73A7164EA2"}
    };
  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  uint8_t exp_result[512];
  uint8_t act_result[512];
  int passlen, saltlen;
      
  for (int i=0; i<num_tests; i++) {

    passlen = strlen(tests[i].pass);
    saltlen = strlen(tests[i].salt);

    assert(tests[i].dk_len <= sizeof(exp_result));
    hexstr_to_bytes(exp_result, tests[i].hex_result, tests[i].dk_len);

    pbkdf2_hmac_isha((const uint8_t *)tests[i].pass, passlen,
        (const uint8_t *)tests[i].salt, saltlen, tests[i].iterations, tests[i].dk_len,
        act_result);

    if (cmp_bin(act_result, exp_result, tests[i].dk_len)) {
      printf("%s test %d: success\r\n", __FUNCTION__, i);
      tests_passed++;
    } else {
      printf("%s test %d: FAILURE\r\n", __FUNCTION__, i);
    }
  }

  return (num_tests == tests_passed);
}


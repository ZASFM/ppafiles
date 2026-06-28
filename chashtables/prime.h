#include <math.h>

/*********************MACROS*********************** */
#define HT_INITIAL_BASE_SIZE  50
/*********************MACROS*********************** */

/**
   @brief brute force method to check is a number is prime
   @param args "x" as number to check
   @return "1" if prime, "0" if undef, "-1" if not prime
 **/
int is_prime(const int x);

/**
   @brief check the next closes prime to a certain number
   @param args "x" as number to check
   @return closest prime to x
 **/
int next_prime(int x);


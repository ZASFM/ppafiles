#include "hash_table.h"
#include "prime.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
   @brief hash algorithm that converts an input string into an int
   @param args "s" as reference string, "a" as primer padding no > ASCII size length (128) and "m" as size of hash table bucket list number
   @return hashed integer of string "s"
 **/
static int ht_hash(const char *s, const int a, const int m);

int ht_hash(const char *s, const int a, const int m)
{
   long hash = 0;
   for (int i = 0; i < strlen(s); i++)
   {
      hash += (long)pow(a, strlen(s) - (i + 1)) * s[i];
      hash = hash % m;
   }
   return (int)hash;
}

int main(int argc, char *argv)
{
   return 0;
}
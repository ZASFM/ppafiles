#ifndef HASH_TABLE
#define HASH_TABLE
#include <stdlib.h>
#include <string.h>
#include <math.h>

/***********************MACROS************************** */
#define HT_PRIME_1 100
#define HT_PRIME_2 200
/***********************MACROS************************** */

/********************TYPES************************* */
typedef struct
{
   char *key;
   char *val;
} ht_item_t;

typedef struct
{
   int size;
   int base_size;
   int count;
   ht_item_t **items;
} ht_hashtable_t;
/********************TYPES************************* */

/**********************DECLARATIONS*********************** */
/**
   @brief creates a new hash map
   @param args void
   @return pointers to newly created hash map
 **/
ht_hashtable_t *ht_hashtable_new();

/**
   @brief deletes from memory a certain hash map
   @param args "ht" as the hash map to deallocate
   @return void if successful
 **/
void ht_del_hashtable(ht_hashtable_t *ht);

/**
   @brief inserts an item into hash table
   @param args "ht" as hashtable, "key" as item key, "val" as item val 
   @return return NULL
 **/
void ht_insert(ht_hashtable_t * ht, const char * key, const char * value);

/**
   @brief searchs inside of hash table, an item with key "key"
   @param args "ht" as hash table, "key" as search query
   @return retruns value of the found item, NULL if no item was found
 **/
char * search(ht_hashtable_t * ht, const char * key);

/**
   @brief 
   @param args 
   @return 
 **/
void ht_delete(ht_hashtable_t * ht, const char * key);
/**********************DECLARATIONS*********************** */

#endif /*HASH_TABLE*/
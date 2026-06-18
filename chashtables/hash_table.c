#include "hash_table.h"
#include "prime.h"
#include <stdio.h>

/**************************STATIC FUNCTIONS************************************** */
/**
   @brief hash algorithm that converts an input string into an int, static to avoid global linkage
   @param args "s" as reference string, "a" as primer padding no > ASCII size length (128) and "m" as size of hash table bucket list number
   @return hashed integer of string "s"
 **/
static int ht_hash(const char *s, const int a, const int m);

/**
   @brief creates a new hash item
   @param args "k" as key and "v" as value
   @return pointer with new hash item
 **/
static ht_item_t *ht_item_new(const char *k, const char *v);

/**
   @brief deallocated a hash item
   @param args "item" to be deleted
   @return Null
 **/
static void hs_del_item(ht_item_t *item);
/**************************STATIC FUNCTIONS************************************** */

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

ht_item_t *ht_item_new(const char *k, const char *v)
{
   ht_item_t *item = malloc(sizeof(ht_item_t *));
   item->key = k;
   item->val = v;
   return item;
}

ht_hashtable_t *ht_hashtable_new()
{
   ht_hashtable_t *map = malloc(sizeof(ht_hashtable_t *));
   map->size = 58;
   map->cout = 0;
   map->items = calloc((size_t)map->cout, sizeof(ht_item_t *));
}

static void ht_del_item(ht_item_t *item)
{
   free(item->key);
   free(item->val);
   free(item);
}

void ht_del_hashtable(ht_hashtable_t *ht)
{
   for (int i = 0; i < ht->size; i++)
   {
      ht_item_t *item = ht->items[i];
      if (item != NULL)
         ht_del_item(item);
   }
   free(ht->items);
   free(ht);
}

int main(int argc, char *argv)
{
   ht_hashtable_t *hash_map = ht_hashtable_new();
   ht_del_hashtable(hash_map);
}
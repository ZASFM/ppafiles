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

/**
   @brief open addressing method for finding index of has item
   @param args "string" as reference for hash function, "num_buckets" as current number of hash items in table, "attempt" as number of collisions so far
   @return returns the hashed index inside bucket list
 **/
static int ht_get_hash(const char *string, const int num_buckets, const int attempt);


static ht_hashtable_t * ht_new_sized(const int base_size){
   ht_hashtable_t * ht = xmalloc(sizeof());
   return ht;
}


// sentinel for a deleted hash item
static ht_item_t HT_DELETED_ITEM = {NULL, NULL};
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

int ht_get_hash(const char *string, const int num_buckets, const int attempt)
{
   const int hash_a = ht_hash(string, HT_PRIME_1, num_buckets);
   const int hash_b = ht_hash(string, HT_PRIME_2, num_buckets);
   // why +1? because hash_b can also return 0, even if we handling collision, so start at base 1
   return (hash_a + (attempt * (hash_b + 1))) % attempt;
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
   map->count = 0;
   map->items = calloc((size_t)map->count, sizeof(ht_item_t *));
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

void ht_insert(ht_hashtable_t *ht, const char *key, const char *value)
{
   ht_item_t *item = ht_item_new(key, value);
   int index = ht_get_hash(item->key, ht->size, 0);
   ht_item_t *curr_item = ht->items[index];
   int i = 0;

   // this handles collision, in case index "index" is taken, function changes index "index", until a free spot of found
   while (curr_item != NULL && curr_item != &HT_DELETED_ITEM)
   {
      index = ht_get_hash(item->key, ht->size, i);
      curr_item = ht->items[index];
      i++;
   }

   ht->items[index] = item;
   ht->count++;
}

char *ht_search(ht_hashtable_t *ht, const char *key)
{
   int index = ht_get_hash(key, ht->size, 0);
   ht_item_t *item = ht->items[index];
   int i = 0;

   while (item != NULL)
   {
      if (item != &HT_DELETED_ITEM)
      {
         if (strcmp(item->key, key) == 0)
         {
            return item->val;
         }

         index = ht_get_hash(key, ht->size, i);
         item = ht->items[index];
         i++;
      }
   }

   return NULL;
}

// sentinel for a deleted hash item
static ht_item_t HT_DELETED_ITEM = {NULL, NULL};
void ht_delete(ht_hashtable_t *ht, const char *key)
{
   int index = ht_get_hash(key, ht->size, 0);
   ht_item_t *item = ht->items[index];
   int i = 1;

   while (item != NULL)
   {
      if (item != &HT_DELETED_ITEM)
      {
         if (strcmp(item->key, key) == 0)
         {
            ht->items[index] = &HT_DELETED_ITEM;
         }
      }

      index = ht_get_hash(key, ht->size, i);
      item = ht->items[index];
      i++;
   }

   ht->size--;
}

int main(int argc, char *argv)
{
   ht_hashtable_t *hash_map = ht_hashtable_new();
   ht_del_hashtable(hash_map);
}
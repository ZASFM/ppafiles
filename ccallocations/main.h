#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

/*----MACROS---*/
typedef char ALIGN[16];
/*---END MACROS---*/

/*---TYPES---*/
union header{
   struct {
      size_t size;
      unsigned is_free;
      union header * next;
   } s;

   /*forcing alignment of 16 bytes*/
   ALIGN stub;
};
typedef union header header_t;
header_t * head=NULL;
header_t * tail=NULL;
/*for avoiding multiple thread incursion, we introduce a lock system before any process, and unlock after process-end*/
pthread_mutex_t global_malloc;
/*---END TYPES---*/

/*---HEADERS---*/
// allocates a memory block of size "size"
// @param size is the actual size of the memory to be allocated in Bytes
// @return (void*)(header + 1), if successfully allocated, and NULL, if failed
void * malloc(size_t size);

// allocates a memory block of size "nsize" of "num" elements, initializing them to 0
// @param "num" as no of elements, and "nsize" as their size
// @return same as @malloc
void * calloc(size_t num, size_t nsize);

// changes the size of a block of memory "block" to new size "size"
// @param "block" as targeted block, and "size" as new size
// @return same as @malloc
void * realloc(void * block, size_t size);

// frees block of memory and reduces heap size of the size of memory freed, iff, the freed memory was at the end of the linkedlist, otherwise, dont reduce heap memory and set freed block as "reusable"
// @param "block" as block to memory to be freed
// @return void 
void free(void * block);

// check whether in linkedlist, there is a free block with enough size to allocated memory there
// @param size as the size of memory to allocate
// @return header_t pointer to free block with enough space to allocate memory with size "size"
header_t * get_free_block(size_t size);
/*---END HEADERS---*/

#endif /*MAIN_H*/

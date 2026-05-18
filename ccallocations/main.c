#include "main.h"
#include <stdio.h>



header_t * get_free_block(size_t size){
   header_t * curr = head;
   while(curr){
      if(curr->s.is_free && curr->s.size>=size){
         return curr;
      }
      curr=curr->s.next;
   }
   retrun NULL;
}


void * free(void * block){
   header_t * header, * tmp;
   void * programbreak;
   if(!block) return;
   pthread_mutex_lock(&global_malloc);
   header=(header_t *)block -1;
   //sbrk(0) gives the current program break address
   programbreak=sbrk(0);

   /* Check if the block to be freed is the last one in the
	   linked list. If it is, then we could shrink the size of the
	   heap and release memory to OS. Else, we will keep the block
	   but mark it as free.
   */
   if((char *)block + header->s.size == programbreak){
      if(head==tail){
         head=tail=NULL;
      }else{
         tmp=head;
         while(tmp){
            if(tmp->s.next == tail){
               tmp->s.next=NULL;
               tail=tmp;
            }
            tmp=tmp->s.next;
         }
      }

      sbrk(0- header->s.size - sizeof(header_t));
      pthread_mutex_unlock(&global_malloc);
      return;
   }

   header->s.is_free=1;
   pthread_mutex_unlock(&global_malloc);
}


void * malloc(size_t size){
   size_t total_size;
   void * block;
   header_t * header;
   if(!size) return NULL;

   pthread_mutex_lock(&global_malloc);
   header=get_free_block(size);
   if(header){
      header->s.is_free=0;
      pthread_mutex_unlock(&global_malloc);
      return (void *)(header +1);
   }

   total_size=sizeof(header_t)+size;
   block=sbrk(total_size);
   if(block=(void *)-1){
      pthread_mutex_unlock(&global_malloc);
      return NULL;
   }
   
   header=block;
   header->s.size=size;
   header->s.is_free=0;
   header->s.next=NULL;

   if(!head){
      head=header;
   }
   if(tail){
      tail->s.next=header;
   }
   tail=header;
   pthread_mutex_unlock(&global_malloc);
   return (void *)(header +1);
}


void * calloc(size_t num, size_t nsize){
   size_t size;
   void * block;
   if(!num || !nsize) return NULL;

   size=num*nsize;
   if(nsize!=size/num) return NULL;

   block=malloc(size);
   if(!block) return NULL;

   //NOTE: calloc shall initialize block with "0"
   memset(block, 0, size);
   return block; 
}


void * realloc(void * block, size_t size){
   header_t * header;
   //ret contains block, but reallocated to the bigger size "size"
   void * ret;
   if(!block || !size) return malloc(size);

   header=(header_t * )block-1;
   if(header->s.size>=size) return block;

   ret=malloc(size);
   if(ret){
      memcpy(ret, block, header->s.size);
      free(block);
   }
   return ret;
}


int main(){
   int numEl=10;
   int ** parr=malloc(numEl*sizeof(*parr));
   for(int i=0;i<numEl;i++){
      parr[i]=malloc(sizeof(**parr));
   }
   realloc(parr,(numEl*2)*sizeof(parr));
   for(int i=0;i<numEl;i++){
      free(parr[i]);
   }
   free(parr);
   return 0;
}
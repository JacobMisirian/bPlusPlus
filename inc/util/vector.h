#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

#define VECTOR_SIZE_INCREMENT 10

struct vector {
  void ** data;
  int     count;
  int     size;
};

struct vector * vector_init ();
void            vector_free (struct vector * vector);

void   vector_push (struct vector * vector, void * ptr);
void * vector_get  (struct vector * vector, int i);
void * vector_peek (struct vector * vector);
void * vector_pop  (struct vector * vector);

#endif

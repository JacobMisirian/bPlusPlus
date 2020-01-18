#include <util/vector.h>

struct vector * init_vector () {
  struct vector * vector;

  vector = calloc (1, sizeof (struct vector));

  vector->data  = calloc(VECTOR_SIZE_INCREMENT, sizeof (void *));
  vector->count = 0;
  vector->size  = VECTOR_SIZE_INCREMENT;

  return vector;
}

void free_vector (struct vector * vector) {
  free (vector->data);
  free (vector);
}

static void resize_vector (struct vector * vector);

void vector_push (struct vector * vector, void * ptr) {
  if (vector->count >= vector->size) {
    resize_vector (vector);
  }

  vector->data [vector->count ++] = ptr;
}

void * vector_peek (struct vector * vector) {
  if (vector->count == 0) { return 0; }

  return vector->data [vector->count - 1];
}

void * vector_pop (struct vector * vector) {
  void * top;

  if (vector->count == 0) { return 0; }

  return vector->data [-- vector->count];
}

void * vector_get (struct vector * vector, int i) {
  if (i >= vector->count || i < 0) {
    return 0;
  }

  return vector->data [i];
}

static void resize_vector (struct vector * vector) {
  vector->size += VECTOR_SIZE_INCREMENT;
  vector->data = realloc (vector->data, sizeof (void *) * vector->size);
}

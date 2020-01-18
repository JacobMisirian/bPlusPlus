#include <util/string.h>

char * copy_string (char * str) {
  char * ret;
  int    len;

  len = strlen (str);
  ret = calloc (len, sizeof (char));

  memcpy (ret, str, len);

  return ret;
}

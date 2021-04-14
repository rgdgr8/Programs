#include <stdlib.h>
#include <string.h>

typedef struct STRING{
  char *s;
  int size;
}STRING;

void initialize(STRING* x, char *s){
  int size = strlen(s);
  x->size = size;
  x->s = malloc(size+1);
  strcpy(x->s,s);
}

STRING concatenate(STRING* a,STRING* b){
  STRING c;
  c.size = a->size+b->size;
  c.s = malloc(c.size+1);
  int i = 0;
  for(;i<a->size;i++)
     c.s[i] = a->s[i];
  //printf("i=%d\n",i);
  for(int j=0;j<b->size;j++)
     c.s[i+j] = b->s[j];
  //printf("in conc: %s\n",c.s);
  c.s[c.size] = '\0';
  return c;
}

void assign(STRING* to, STRING* from){
  to->size = from->size;
  free(to->s);
  to->s = malloc(to->size+1);
  strcpy(to->s,from->s);
}


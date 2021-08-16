#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct STRING{//string structure, size and content
  char *s;
  int size;
}STRING;

void initialize(STRING* x, char *s){//initialize string
  int size = strlen(s);
  if(x!=NULL && x->s!=NULL)
     free(x->s);
  x->size = size;
  x->s = malloc(size+1);
  strcpy(x->s,s);
}

STRING concatenate(STRING* a,STRING* b){//a + b
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

void assign(STRING* to, STRING* from){//a = b
  to->size = from->size;
  free(to->s);
  to->s = malloc(to->size+1);
  strcpy(to->s,from->s);
}

int compare_STR(STRING* a,STRING* b){//compares contents of a and b: a==b return 0, a>b returns 1, a<b returns -1
	return strcmp(a->s,b->s);
}

void print_STR(STRING* x,char* s){//print String
	printf("%s %s\n",s,x->s);
	printf("length: %d\n",x->size);
}

#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE
#define TABLE_SIZE 256
#define MAX_DIM 1000
#define MAX_ID_LEN 64

typedef struct symbolinfo
{
    char *id;
    int isVar;
    int basetype;
    int dim;
    int ptrtodim;
    int line_no;
    struct symbolinfo *next;
} symbolinfo;

symbolinfo *create_symbolinfo(char *id, int isVar, int basetype, int dim, int line_no, int *dimentions);
void print_symbolinfo(symbolinfo *n);

int *dimentions;
int ptrtodimentions;
symbolinfo **symbol_table;

void init_symbol_table();
int hashfn(char *id);
int insert(char *id, int isVar, int basetype, int dim, int line_no, int *dims);
symbolinfo *look_up(char *id);
void delete_table();
void print_symbol_table();

#endif
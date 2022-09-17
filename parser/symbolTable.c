#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

symbolinfo *create_symbolinfo(char *id, int isVar, int basetype, int dim, int line_no, int *dims)
{
    symbolinfo *n = (symbolinfo *)malloc(sizeof(symbolinfo));

    if (!n)
    {
        perror("symbolinfo pointer cannot be declared");
        exit(-1);
    }

    n->id = strdup(id);
    n->isVar = isVar;
    n->basetype = basetype;
    n->dim = dim;
    n->line_no = line_no;
    if (dim == 0)
    {
        n->ptrtodim = -1;
    }
    else
    {
        n->ptrtodim = ptrtodimentions + 1;
        for (int i = 0; i < dim; i++)
        {
            dimentions[n->ptrtodim + i] = dims[i];
        }

        ptrtodimentions += dim;
    }

    n->next = NULL;
    return n;
}

void print_symbolinfo(symbolinfo *n)
{
    if (n == NULL)
        return;

    printf("id = %s\tis Variable = %d\tbasetype = %d\tdim_count = %d\tline_no = %d\tdimentions = ", n->id, n->isVar, n->basetype, n->dim, n->line_no);
    if (n->dim != 0)
    {
        for (int i = 0; i < n->dim; i++)
        {
            printf("  %d", dimentions[n->ptrtodim + i]);
        }
    }
}

void init_symbol_table()
{
    dimentions = (int *)malloc(MAX_DIM * sizeof(int));
    ptrtodimentions = -1;
    symbol_table = (symbolinfo **)malloc(TABLE_SIZE * sizeof(symbolinfo *));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        symbol_table[i] = NULL;
    }
}

int hashfn(char *id)
{
    int length = strnlen(id, MAX_ID_LEN);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += id[i];
        hash_value = (hash_value * id[i]) % TABLE_SIZE;
    }
    return hash_value;
}

int insert(char *id, int isVar, int basetype, int dim, int line_no, int *dims)
{
    int index = hashfn(id);

    symbolinfo *n = create_symbolinfo(id, isVar, basetype, dim, line_no, dims);

    if (symbol_table[index] == NULL)
    {
        symbol_table[index] = n;
        return 1;
    }
    else
    {
        symbolinfo *cur = symbol_table[index];

        while (cur->next != NULL)
        {
            cur = cur->next;
        }

        cur->next = n;
        return 1;
    }
    return 0;
}

symbolinfo *look_up(char *id)
{
    int index = hashfn(id);
    symbolinfo *cur = symbol_table[index];
    if (!cur)
    {
        return NULL;
    }

    while (cur)
    {
        if (strcmp(id, cur->id) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void delete_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        symbolinfo *cur = symbol_table[i];
        while (cur)
        {
            cur = cur->next;
            free(cur);
            cur = NULL;
        }
        symbol_table[i] = NULL;
    }
    free(symbol_table);
    symbol_table = NULL;
    free(dimentions);
    ptrtodimentions = -1;
}

void print_symbol_table()
{
    if (symbol_table == NULL)
        return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        symbolinfo *cur = symbol_table[i];
        while (cur)
        {
            print_symbolinfo(cur);
            printf("\n");
            cur = cur->next;
        }
    }
}
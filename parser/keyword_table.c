#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_KEYWORD 256

typedef struct keyword
{
    char *id;
    int code;
    struct keyword *next;

} keyword;

keyword **keywords;

keyword *create_keyword(char *id, int code)
{
    keyword *key = (keyword *)malloc(sizeof(keyword));
    key->id = strdup(id);
    key->code = code;
    return key;
}

void init_keywords_table()
{
    keywords = (keyword **)malloc(MAX_KEYWORD * sizeof(keyword *));
}

int hash_code(char *id)
{
    int length = strnlen(id, 100);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += id[i];
        hash_value = (hash_value * id[i]) % MAX_KEYWORD;
    }
    return hash_value;
}

int insert_keyword(char *id, int code)
{
    int index = hash_code(id);

    keyword *n = create_keyword(id, code);

    if (keywords[index] == NULL)
    {
        keywords[index] = n;
        return 1;
    }
    else
    {
        keyword *cur = keywords[index];

        while (cur->next != NULL)
        {
            cur = cur->next;
        }

        cur->next = n;
        return 1;
    }
    return 0;
}

int get_code(char *id)
{
    int index = hash_code(id);
    keyword *cur = keywords[index];
    if (!cur)
    {
        return -1;
    }

    while (cur)
    {
        if (strcmp(id, cur->id) == 0)
        {
            return cur->code;
        }
        cur = cur->next;
    }
    return -1;
}

void store_keywords()
{
    init_keywords_table();
    char *keys[] = {"main", "if", "else", "for","int", "char"};
    int codes[] = {128, 129, 130, 131, 137, 138};

    for (int i = 0; i < 6; i++)
    {
        insert_keyword(keys[i], codes[i]);
    }
}

/*int main(){
	store_keywords();
	printf("%d\n",get_code("int"));
}*/

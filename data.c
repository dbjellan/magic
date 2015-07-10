/*#define _GNU_SOURCE
#define __USE_GNU
#include <search.h>*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "magic.h"
#include "data.h"

/*m_hash_table* new_hash_table(int size) {
    m_hash_table* table = (m_hash_table*) malloc(sizeof(m_hash_table));
    if (table) {
        table->hash_table = (struct hsearch_data*) calloc(1, sizeof(struct hsearch_data);
        hcreate_r(size, table->hash_table);
        table->size = size;
        table->length = 0;
        table->keys = (char **) malloc(size*sizeof(char *));
        table->object_ptrs = (m_object **) malloc(size*sizeof(m_object *));
    }
    return table;
}

void set(m_hash_table *table, char *key, m_object *value) {
    ENTRY ep;
    ep.key = key;
    ep.data = NULL;
    ENTRY **result;
    long indx;
    hsearch_r(ep, FIND, result, table->hash_table);
    if (result != NULL) {
        indx = (long)(*result)->data;
        table->object_ptrs[indx] = value;
    } else {
        char *key_copy = (char *) malloc(strlen(key)+1);
        strcpy(key_copy, key);
        if (table->length >= table->size) {
            resize_hashtable(table, table->size*2);
        }
        indx = table->length;
        table->length++;
        ep.data = (void *)indx;
        hsearch_r(ep, ENTER, result, table->hash_table);
        table->keys[indx] = key_copy;
        table->object_ptrs[indx] = value;
    }
}

m_object* get(m_hash_table *table, char *key) {
    ENTRY ep;
    ep.key = key;
    ep.data = NULL;
    ENTRY **result;
    long indx;
    hsearch_r(ep, FIND, result, table->hash_table);
    if (result == NULL) {
        return NULL;
    }
    else {
        indx = (long)(*result)->data;
        return table->object_ptrs[indx];
    }
}

/*m_object** get_lvalue(m_hash_table *table, char *key) {
    ENTRY ep;
    ep.key = key;
    ep.data = NULL;
    ENTRY **result;
    long indx;
    hsearch_r(ep, FIND, result, table->hash_table);
    if (result == NULL) {
        return NULL;
    }
    else {
        indx = (long)(*result)->data;
        return &table->object_ptrs[indx];
    }  
}*/
/*
void destroy_hash_table(m_hash_table *table) {
    for(int i=0; i < table->length; i++) {
        free(table->keys[i]);
    }
    free(table->keys);
    free(table->object_ptrs);
    hdestroy_r(table->hash_table);
    free(table);
}

void resize(m_hash_table *table, unsigned int new_size) {
    struct hsearch_data* new_hsearch = (struct hsearch_data*) calloc(1, sizeof(struct hsearch_data);
    hcreate_r(new_size, new_hsearch);
    ENTRY ep;
    ENTRY **result;
    for(long i = 0; i < table->length; i++) {
        ep.key = table->keys[i];
        ep.data = (void *)i;
        hsearch_r(ep, ENTER, result, new_hsearch);
    }
    hdestroy_r(table->hash_table);
    table->keys = (char **) realloc(table->keys, new_size*sizeof(char *));
    table->object_ptrs = (m_object **) realloc(table->object_ptrs, new_size*sizeof(m_object *));
    table->size = new_size;
    table->hash_table = new_hsearch;
}
*/

m_hash_table* new_hash_table(int size) {
    m_hash_table* table = (m_hash_table*) malloc(sizeof(m_hash_table));
    if (table) {
        table->table = (magic_hash_entry **) malloc(sizeof(struct magic_hash_entry*)*size);
        table->size = size;
        for (int i = 0; i < size; i++) {
            table->table[i] = NULL;
        }
    }
    return table;
}


uint32_t hash(const char *key, unsigned int m) {
    uint32_t hash, i;
    uint32_t len = strlen(key);
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % m;
}

m_object* get(m_hash_table *table, char *key) {
    unsigned int hash_value = hash(key, table->size);
    printf("key: %s\n", key);
    printf("hashvalue: %d tablesize: %d\n", hash_value, table->size);
    m_hashentry *bin_entry = table->table[hash_value];
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            printf("found object\n");
            return bin_entry->value;
        }
        bin_entry = bin_entry->next;
    }
    return NULL;
}

m_object** get_lvalue(m_hash_table *table, char *key) {
    unsigned int hash_value = hash(key, table->size);
    m_hashentry *bin_entry = table->table[hash_value];
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            return &(bin_entry->value);
        }
        bin_entry = bin_entry->next;
    }
    return NULL;
}

void resize(m_hash_table *table, unsigned int new_size) {
    m_hash_table* result;
    if (new_size > table->size) {
        unsigned int old_size = table->size;
        result = new_hash_table(new_size);
        m_hashentry *cur_entry;
        for(int i = 0; i < old_size; i++) {
            cur_entry = table->table[i];
            while(cur_entry != NULL) {
                set(result, cur_entry->key, cur_entry->value);
                cur_entry = cur_entry->next;
            }
        }
    }
}

void set(m_hash_table *table, char *key, m_object *value) {
    unsigned int hash_val = hash(key, table->size);
    m_hashentry *bin_entry = table->table[hash_val];
    bool found = false;
    if (table->table[hash_val] != NULL) {
        while (true) {
            if (strcmp(key, bin_entry->key) == 0) {
                bin_entry->value = value;
                found = true;
                break;
            } else if (bin_entry->next == NULL) {
                break;
            } else {
                bin_entry = bin_entry->next;
            }
        } 
    }
    if (!found) {
        bin_entry = (m_hashentry *)malloc(sizeof(m_hashentry));
        if (bin_entry) {
            bin_entry->next = NULL;
            bin_entry->key = (char *) malloc(strlen(key)+1);
            strcpy(bin_entry->key, key);
            bin_entry->value = value;
        }
    }
}

void print_table(m_hash_table *table) {
    for (int i = 0; i < table->size; i++) {
        if (table->table[i] != NULL) {
            printf("slot %d\n", i);
            m_hashentry *cur = table->table[i];
            while  (cur != NULL) {
                printf("pair %s : %s\n", cur->key, magic_object_tostring(cur->value));
            }
        }
    }
}
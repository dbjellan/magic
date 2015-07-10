#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "magic.h"
#include "data.h"

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


unsigned int hash(const char *key, unsigned int m) {
    unsigned int hash, i;
    unsigned int len = strlen(key);
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
    //printf("key: %s\n", key);
    //printf("hashvalue: %d tablesize: %d\n", hash_value, table->size);
    m_hashentry *bin_entry = table->table[hash_value];
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
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
    m_hashentry *new_entry;
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
        new_entry = (m_hashentry *)malloc(sizeof(m_hashentry));
        if (new_entry) {
            new_entry->next = NULL;
            new_entry->key = (char *) malloc(strlen(key)+1);
            strcpy(new_entry->key, key);
            new_entry->value = value;
            if (bin_entry != NULL) {
                bin_entry->next = new_entry;
            } else {
                table->table[hash_val] = new_entry;
            }
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
                cur = cur->next;
            }
        }
    }
}
#include "hash.h"

#include "item.h"
#include "ll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hashtable *hash_create(void) {
    Hashtable *h = (Hashtable *) malloc(sizeof(Hashtable));
    if (h == NULL) {
        return NULL;
    }
    //LL *l = &h->list[1000];
    //LL l[] = h->list;
    for (int i = 0; i < 1000; i++) {
        h->list[i] = list_create();
    }
    return h;
}

bool hash_put(Hashtable *h, char *key, int val) {
    LL *l = hash_function(h, key);
    item *temp = (item *) malloc(sizeof(item));
    strcpy(temp->key, key);
    temp->id = val;
    item *value = list_find(l, cmp, temp);
    if (value == NULL) {
        list_add(l, temp);
    } else {
        strcpy(value->key, key);
        value->id = val;
    }
    free(temp);
    return true;
}

int *hash_get(Hashtable *h, char *key) {
    LL *l = hash_function(h, key);
    Node *c = l->head;
    while (c != NULL) {
        if (strcmp(c->data.key, key) == 0) {
            return &c->data.id;
        }
        c = c->next;
    }
    return NULL;
}

void hash_destroy(Hashtable **h) {
    //LL *l = (*h)->list;
    for (int i = 0; i < 1000; i++) {
        //LL *temp = &l[i];
        list_destroy(&(*h)->list[i]);
    }
    free(*h);
    *h = NULL;
}

LL *hash_function(Hashtable *h, char *key) {
    int number = 0;
    const char *p = key;
    while (*p) {
        number += (int) *p;
        p++;
    }
    number = number % 1000;
    LL *l = h->list[number];
    return l;
}

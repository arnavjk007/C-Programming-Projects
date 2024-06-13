#ifndef _HASH

#define _HASH

#include "ll.h"

typedef struct Hashtable Hashtable;

struct Hashtable {
    // your datastructure here; this is just a placeholder
    LL *list[1000];
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

LL *hash_function(Hashtable *h, char *key);
#endif

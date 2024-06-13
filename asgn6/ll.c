#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create(void) {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
        return true;
    } else {
        n->next = l->head;
        l->head = n;
        return true;
    }
}

item *list_find(LL *l, bool (*cmpfn)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmpfn(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **ll) {
    while ((*ll)->head != NULL) {
        Node *n = (*ll)->head->next;
        deleteNode(&(*ll)->head);
        (*ll)->head = n;
    }
    free(*ll);
    *ll = NULL;
}

void list_remove(LL *ll, bool (*cmpfn)(item *, item *), item *iptr) {
    Node *p = NULL;
    Node *c = ll->head;
    while (c != NULL) {
        if (cmpfn(&c->data, iptr)) {
            if (p != NULL)
                p->next = c->next;
            else
                ll->head = c->next;
            deleteNode(&c);
            return;
        }
        p = c;
        c = c->next;
    }
    return;
}

void deleteNode(Node **n) {
    if (n != NULL) {
        free(*n);
        //*n = NULL;
    }
}

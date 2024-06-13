#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

//creates a stack, dynamically allocates space for it, and returns a pointer to it
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    s->items = calloc(s->capacity, sizeof(uint32_t));
    return s;
}

//free all space used by a given stack, and sets the pointer to NULL
void stack_free(Stack **sp) {
    if (sp != NULL && *sp != NULL) {
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        free(*sp);
    }
    if (sp != NULL)
        *sp = NULL;
}

//adds val to the top of the stack S and increments the counter
//retrns true if successful false otherwise
bool stack_push(Stack *s, uint32_t val) {
    //printf("Adding to stack ... %i ... stack size %i\n", val, stack_size(s));
    if (stack_full(s))
        return false;
    s->items[stack_size(s) == 0 ? 0 : s->top] = val;
    s->top += 1;
    /*
    for (uint32_t i = 0; i < stack_size(s); i++) {
        printf("in stack... %u\n", s->items[i]);
    }
    */
    return true;
}

//sets the integer pointed to by val to the last item on the stack and removes the last item on the stack
//returns true if successful false otherwise
//stack->top is not the index of the top val of the stack
bool stack_pop(Stack *s, uint32_t *val) {
    if (stack_empty(s))
        return false;
    *val = s->items[stack_size(s) - 1];
    s->items[stack_size(s) - 1] = 0;
    s->top -= 1;
    return true;
}

//sets the integer pointed to by val to the last item on the stack
//but DOES NOT modify the stack
//returns true if successful and false otherwise
bool stack_peek(const Stack *s, uint32_t *val) {
    if (stack_empty(s))
        return false;
    *val = s->items[s->top - 1];
    //printf("STACK PEEK VAL = %u\n", *val);
    return true;
}

// returns true if the stack is empty, false otherwise
bool stack_empty(const Stack *s) {
    return stack_size(s) == 0;
}

// returns true if the stack is full, false otherwise
bool stack_full(const Stack *s) {
    return stack_size(s) == s->capacity;
}

// returns the number of elements in the stack
uint32_t stack_size(const Stack *s) {
    return s->top;
}

// overwrites dst with all the items in src
void stack_copy(Stack *dst, const Stack *src) {
    for (uint32_t i = 0; i < stack_size(src); i++) {
        dst->items[i] = src->items[i];
    }
    dst->top = src->top;
}

//print out stack as a list of elements starting from the bottom of the stack
void stack_print(const Stack *s, FILE *outfile, char *cities[]) {
    //(void) outfile;
    //(void) cities;
    for (uint32_t i = 0; i < s->top; i++) {
        //printf("%u -> ", s->items[i] + 1);
        //fprintf(outfile, "%s", i == s->top - 1 ? cities[0] : cities[i]);
        fprintf(outfile, "%s\n", cities[s->items[i]]);
    }
}

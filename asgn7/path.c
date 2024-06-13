#include "path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

// creates a path ds containing a Stack and a weight of 0
Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

// frees a path and all associated memory
void path_free(Path **pp) {
    if (!(*pp))
        return;
    stack_free(&(*pp)->vertices);
    free(*pp);
    *pp = NULL;
}

//finds the number of vertices in a path
uint32_t path_vertices(const Path *p) {
    //printf("Path Vertices: %u\n", stack_size(p->vertices));
    return stack_size(p->vertices);
}

//finds the distance covered by a path
uint32_t path_distance(const Path *p) {
    return stack_size(p->vertices) == 0 ? 0 : p->total_weight;
}

// adds vertex val from graph g to the path
// also updates distance and length of the path
void path_add(Path *p, uint32_t val, const Graph *g) {
    //printf("Path add for val %i\n", val);

    uint32_t recent_vertex = 0;
    if (path_vertices(p) > 0) {
        stack_peek(p->vertices, &recent_vertex);
        //printf("val is %u: recent is %u\n", val, recent_vertex);
        p->total_weight += graph_get_weight(g, recent_vertex, val);
        //printf("total weight after adding vertex %u -> size %u -> weight %u\n\n", val,
        //    stack_size(p->vertices), p->total_weight);
        //printf("total_weight in path_add : %u\n", p->total_weight);
        //printf("Adding to path:  %u\n", graph_get_weight(g, recent_vertex, val));
    }
    stack_push(p->vertices, val);
    //printf("Added to path val %i\n", val);
}

// removes the recently added vertex from the path
// returns index of teh removed vertex
uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex = 0;
    uint32_t last_vertex = 0;
    stack_pop(p->vertices, &removed_vertex);
    stack_peek(p->vertices, &last_vertex);
    p->total_weight -= stack_size(p->vertices) == 1
                           ? p->total_weight
                           : graph_get_weight(g, last_vertex, removed_vertex);
    //printf("total weight after removing vertex %u -> size %u -> weight %u\n\n", removed_vertex,
    //    stack_size(p->vertices), p->total_weight);
    return stack_size(p->vertices);
}

// copies a path src to dst
void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    stack_copy(dst->vertices, src->vertices);
}

// prints the path stored using vertex names fromg to the file outfile
void path_print(const Path *p, FILE *outfile, const Graph *g) {
    // (void) outfile;
    fprintf(outfile, "Alissa starts at:\n");
    stack_print(p->vertices, outfile, graph_get_names(g));
    //printf("END\n");
    /* 
    for (uint32_t i = 0; i < path_vertices(p) + i; i++) {
        uint32_t temp = 0;
        stack_peek(p->vertices, &temp);
        const char *value = graph_get_vertex_name(g, i);
        stack_pop(p->vertices, &temp);
        printf("%s\n", value);
    }
    */
}

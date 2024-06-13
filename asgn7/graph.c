#include "graph.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

char **string_of_names;
//creates graph
Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    //use calloc to initialize everything with zeroes
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));

    //allocate g->weights w/ pointer to each row
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    //allocate each row in the adjacency matrix
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }

    string_of_names = calloc(vertices, sizeof(char *));
    return g;
}

//frees all memory used by the graph, sets pointer to NULL
void graph_free(Graph **gp) {
    if (!*gp)
        return;
    free((*gp)->visited);
    for (uint32_t i = 0; i < (*gp)->vertices; i++) {
        free((*gp)->weights[i]);
        free((*gp)->names[i]);
        //free(string_of_names[i]);
    }
    free((*gp)->names);
    free((*gp)->weights);
    free(string_of_names);
    //*string_of_names = NULL;
    free(*gp);
    *gp = NULL;
    return;
}

//finds number of vertices in the graph
uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

//gives the city at vertex v the name passed in
//makes a copy of the name and stores it in the graph object
void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

//gets the name of the city with vertex v from the array of city names
const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

//gets the names of every city in an array
//returns double pointer  -- an array of strings -- but not a copy
char **graph_get_names(const Graph *g) {
    //string_of_names = calloc(graph_vertices(g), sizeof(char *));
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        //printf("%u Name: %s\n", i, g->names[i]);
        string_of_names[i] = g->names[i];
    }
    return string_of_names;
}

//adds an edge betwen start and end with weight weight to the adjacency matrix of the graph
void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    g->weights[start][end] = weight;
}

//looks up weight of the edge betwwen start and end and returns it
uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    //return g->weights[start][end];
    return g->weights[start][end] == 0 && !g->directed ? g->weights[end][start]
                                                       : g->weights[start][end];
}

//adds the vertex v to the list of visited vertices
void graph_visit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = true;
}

//removes vertex v from the list of visited vertices
void graph_unvisit_vertex(Graph *g, uint32_t v) {
    g->visited[v] = false;
}

//returns true if vertex v is visited in graph g false otherwise
bool graph_visited(const Graph *g, uint32_t v) {
    return g->visited[v];
}

//prints representation of graph
void graph_print(const Graph *g) {
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("%s", graph_get_vertex_name(g, i));
    }

    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            printf("%u ", g->weights[i][j]);
        }
        printf("\n");
    }
}

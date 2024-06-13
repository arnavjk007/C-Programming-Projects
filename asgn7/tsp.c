#include "graph.h"
#include "path.h"
#include "stack.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t total_weight = INT_MAX, total_v = 0;
Path *final_path = NULL, *temp = NULL;

void dfs(uint32_t v, Graph *g) {
    graph_visit_vertex(g, v);
    path_add(temp, v, g);
    for (uint32_t i = 0; i < total_v; i++) {
        if (graph_get_weight(g, v, i)) {
            if (i == 0) {
                if (path_vertices(temp) < total_v) {
                    continue;
                }
                // We are back at start
                path_add(temp, 0, g);
                if (path_distance(temp) < total_weight) {
                    total_weight = path_distance(temp);
                    path_copy(final_path, temp);
                }
                path_remove(temp, g);
                return;
            }

            if (graph_visited(g, i)) {
                continue;
            }
            dfs(i, g);
            graph_unvisit_vertex(g, i);
            path_remove(temp, g);
        }
    }
    graph_unvisit_vertex(g, v);
}

int main(int argc, char **argv) {
    bool read_from_file = false, write_to_file = false;
    bool directed = false;
    FILE *f;
    FILE *wf;
    int i = 1;

    while (i < argc) {
        if (strcmp(argv[i], "-o") == 0) {
            write_to_file = true;
            wf = fopen(argv[i + 1], "w");
            i++;
        } else if (strcmp(argv[i], "-d") == 0)
            directed = true;
        else if (strcmp(argv[i], "-h") == 0) {
            fprintf(stdout, "Usage: tsp [options]\n");
            fprintf(stdout,
                "	-i infile   Specify the input file path containing the cities and edges of "
                "a graph. If not specified, the default input should be set as stdin.\n");
            fprintf(stdout, "	-o outfile  Specify the output file path to print tp. If not "
                            "specified, the default output should be set as stdout.\n");
            fprintf(stdout, "	-d	    Specifies the graph to be directed.\n");
            fprintf(stdout,
                "	-h 	    Prints out a help message describing the purpose of the graph "
                "and the command-line options it accepts, exiting the program afterwards.\n");
            return 0;
        } else if (strcmp(argv[i], "-i") == 0) {
            read_from_file = true;
            f = fopen(argv[i + 1], "r");
            i++;
        } else {
            fprintf(stderr, "tsp:  unknown or poorly formatted option %s\n", argv[i]);
            return 0;
        }
        //increment
        i++;
    }
    uint32_t vertices = 0, index = 0, paths = 0;

    //checks if num vertices is valid number
    if (fscanf(read_from_file ? f : stdin, "%u\n", &vertices) != 1) {
        fprintf(stderr, "tsp: error reading number of vertices\n");
        fclose(f);
        exit(1);
    }

    char *word = NULL;
    char line[255];
    final_path = path_create(PATH_MAX);
    temp = path_create(PATH_MAX);
    total_v = vertices;
    
    // initializes graph with read in number of vertices and directed bool var
    Graph *g = graph_create(vertices, directed);

    // reads in names as words and adds them w/ corresponding vertex
    while ((fgets(line, 255, read_from_file ? f : stdin)) != NULL && index < vertices) {
        //printf("Word: %s\n", line);
        line[strcspn(line, "\n")] = 0;
        graph_add_vertex(g, line, index);

        index++;
    }

    //reset
    index = 0;
    word = NULL;

    //placeholder to hold all the numbers we read in from matrix
    uint32_t start = 0, end = 0, weight = 0;

    word = strtok(line, " ");
    sscanf(word, "%u", &paths);

    while ((fgets(line, 255, read_from_file ? f : stdin)) != NULL && index < paths) {
        word = strtok(line, " ");
        sscanf(word, "%d", &start);
        word = strtok(NULL, " ");
        sscanf(word, "%d", &end);
        word = strtok(NULL, " ");
        sscanf(word, "%d", &weight);
        word = strtok(NULL, " ");
        graph_add_edge(g, start, end, weight);
        if (!directed && graph_get_weight(g, start, end) != 0) {
            graph_add_edge(g, end, start, weight);
        }
        index++;
    }

    //finding lowest weight path
    dfs(0, g);

    if (total_weight != INT_MAX) {
        path_print(final_path, write_to_file ? wf : stdout, g);
        fprintf(write_to_file ? wf : stdout, "Total Distance: %u\n", total_weight);
    } else
        fprintf(write_to_file ? wf : stdout, "No path found! Alissa is lost!\n");

    graph_free(&g);
    path_free(&final_path);
    path_free(&temp);
    if (read_from_file)
        fclose(f);
    if (write_to_file)
        fclose(wf);
    return 0;
}

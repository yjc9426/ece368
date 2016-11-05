#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

typedef struct {
	int v;				/* neighboring vertex */
	int weight;			/* edge weight */
} edge;

typedef struct {
	edge edges[MAXV+1][MAXDEGREE];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;

void read_graph(graph *g,bool directed);

void find_path(int start,int end,int parents[]);
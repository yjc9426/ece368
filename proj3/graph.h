typedef struct graph *Graph;

Graph graph_create(int n);

void graph_destroy(Graph);

void graph_add_edge(Graph, int source, int sink);

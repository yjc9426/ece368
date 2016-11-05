#define _GNU_SOURCE
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

struct graph {
    int n;              /* number of vertices */
    int m;              /* number of edges */
    struct successors {
        int d;          /* number of successors */
        int len;        /* number of slots in array */
        char is_sorted; /* true if list is already sorted */
        int list[1];    /* actual list of successors */
    } *alist[1];
};


Graph graph_create(int n)
{
    Graph g;
    int i;

    g = malloc(sizeof(struct graph) + sizeof(struct successors *) * (n-1));
    assert(g);

    g->n = n;
    g->m = 0;

    for(i = 0; i < n; i++) {
        g->alist[i] = malloc(sizeof(struct successors));
        assert(g->alist[i]);

        g->alist[i]->d = 0;
        g->alist[i]->len = 1;
        g->alist[i]->is_sorted= 1;
    }
    
    return g;
}

void
graph_destroy(Graph g)
{
    int i;

    for(i = 0; i < g->n; i++) free(g->alist[i]);
    free(g);
}


void
graph_add_edge(Graph g, int u, int v)
{
    assert(u >= 0);
    assert(u < g->n);
    assert(v >= 0);
    assert(v < g->n);

    /* do we need to grow the list? */
    while(g->alist[u]->d >= g->alist[u]->len) {
        g->alist[u]->len *= 2;
        g->alist[u] =
            realloc(g->alist[u], 
                sizeof(struct successors) + sizeof(int) * (g->alist[u]->len - 1));
    }

    /* now add the new sink */
    g->alist[u]->list[g->alist[u]->d++] = v;
    g->alist[u]->is_sorted = 0;

    /* bump edge count */
    g->m++;
}


void get_adj(Graph g, int source){
    int i;

    assert(source >= 0);
    assert(source < g->n);
    printf("%d:",source);
    for(i=0; i< g->alist[source]->d; i++){
	printf(" %d",g->alist[source]->list[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    if(argc > 1){
        FILE* fp;
	char* line = NULL;
	char str[100];
	size_t len = 0;
	ssize_t read;
	char *p;
	int num[2];
	int temp[3];
	int number[2];
	int n = 0;
        fp = fopen(argv[1],"r");
	if(fp != NULL){
	    fgets(str,100,fp);
	    //printf("%swtf\n",str);
  	    //split
	    char * pch;
  	    pch = strtok (str," ");
  	    while (pch != NULL)
  	    {
    	        num[n]=atoi(pch);
    	        printf("split%d\n",num[n]);
    	        pch = strtok (NULL, " ");
    	        n++;
  	    }
	    //printf("%s\n",str);
	    //printf("sb%d\n",num[0]);
	    //printf("dsb%d\n",num[1]);

	    Graph map = graph_create(num[0]);
	    int vertex[num[0]];
	    n = 0;
            while( n != num[0]){
		read = getline(&line, &len, fp);
		printf("%s",line);
		//split
  		char * pch;
  		pch = strtok (line," ");
  		int i = 0;
  		while (pch != NULL)
  		{
    		    temp[i]=atoi(pch); //temp0 is vertex, 1 and 2 are coordinate
    		    printf("%d\n",number[i]);
    		    pch = strtok (NULL, " ");
    		    i++;
  		}
		vertex[n] = temp[0];
		n++;
	    }
	    n = 0;
            while( n != num[1]){
		read = getline(&line, &len, fp);
		printf("%s",line);
		n++;
		//split
  		char * pch;
  		pch = strtok (line," ");
  		int i = 0;
  		while (pch != NULL)
  		{
    		    number[i]=atoi(pch);
    		    printf("%d\n",number[i]);
    		    pch = strtok (NULL, " ");
    		    i++;
  		}

	        graph_add_edge(map,number[0],number[1]);
	        int e = map->m;
	        //printf("%d\n",e);

	    }
	    int j;
	    for(j = 0;j<num[0];j++)
	    get_adj(map,j);
	}
    }

    
    return 0;
}

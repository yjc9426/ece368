#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef struct graph *Graph;

typedef struct query *Query;

Graph graph_create(int n);

void graph_add_edge(Graph, int source, int sink);


struct graph {
    int v;              /* number of vertices */
    int e;              /* number of edges */
    struct successors {
        int d;          /* number of successors */
        int len;        /* number of slots in array */
	int x;		// x coordinate
	int y;		// y coordinate
        char is_sorted; /* true if list is already sorted */
        int list[1];    /* actual list of successors */
    } *alist[1];
};

struct query {
    int start[100];
    int end[100];    
};


Graph graph_create(int n)
{
    Graph g;
    int i;

    g = malloc(sizeof(struct graph) + sizeof(struct successors *) * (n-1));
    assert(g);

    g->v = n;
    g->e = 0;

    for(i = 0; i < n; i++) {
        g->alist[i] = malloc(sizeof(struct successors));
        assert(g->alist[i]);

        g->alist[i]->d = 0;
        g->alist[i]->len = 1;
        g->alist[i]->is_sorted= 1;
    }
    
    return g;
}


void graph_add_edge(Graph g, int a, int b)
{
    assert(a >= 0);
    assert(a < g->v);
    assert(b >= 0);
    assert(b < g->v);
    

    while(g->alist[a]->d >= g->alist[a]->len) {
        g->alist[a]->len *= 2;
        g->alist[a] =
            realloc(g->alist[a], 
                sizeof(struct successors) + sizeof(int) * (g->alist[a]->len - 1));
    }
    while(g->alist[b]->d >= g->alist[b]->len) {
        g->alist[b]->len *= 2;
        g->alist[b] =
            realloc(g->alist[b], 
                sizeof(struct successors) + sizeof(int) * (g->alist[b]->len - 1));
    }

    g->alist[a]->list[g->alist[a]->d++] = b;
    g->alist[b]->list[g->alist[b]->d++] = a;    
    g->alist[a]->is_sorted = 0;
    g->alist[b]->is_sorted = 0;

    g->e++;
}


void get_adj(Graph g, int source){
    int i;

    assert(source >= 0);
    assert(source < g->v);
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
    	        //printf("split%d\n",num[n]);
    	        pch = strtok (NULL, " ");
    	        n++;
  	    }
	    //printf("%s\n",str);
	    //printf("sb%d\n",num[0]);
	    //printf("dsb%d\n",num[1]);

	    Graph map = graph_create(num[0]);	// create map
	    int vertex[num[0]];			// 
	    int coordinate[num[0]][num[0]];
	    n = 0;
            while( n != num[0]){
		read = getline(&line, &len, fp);
		//printf("%s",line);
		//split
  		char * pch;
  		pch = strtok (line," ");
  		int i = 0;
  		while (pch != NULL)
  		{
    		    temp[i]=atoi(pch); //temp0 is vertex, 1 and 2 are coordinate
    		    //printf("%d\n",number[i]);
    		    pch = strtok (NULL, " ");
    		    i++;
  		}
		vertex[n] = temp[0];
		map->alist[n]->x = temp[1];
		map->alist[n]->y = temp[2];
		printf("x%d,y%d",map->alist[n]->x,map->alist[n]->y);
		n++;
	    }
	    n = 0;
            while( n != num[1]){
		read = getline(&line, &len, fp);
		//printf("%s",line);
		n++;
		//split
  		char * pch;
  		pch = strtok (line," ");
  		int i = 0;
  		while (pch != NULL)
  		{
    		    number[i]=atoi(pch);
    		    //printf("%d\n",number[i]);
    		    pch = strtok (NULL, " ");
    		    i++;
  		}

	        graph_add_edge(map,number[0],number[1]);
		//graph_add_edge(map,number[1],number[0]);
	        int e = map->e;
	        //printf("%d\n",e);

	    }
	    int j;
	    for(j = 0;j<num[0];j++)
	    get_adj(map,j);
	    double d = get_distance(map,1,2);
	    printf("%.2fdistance\n",d);
	}
    }

    if (argc > 2){
	int numq;
	char strr[100];
	char* linee = NULL;
	size_t lenn = 0;
	ssize_t readd;
	int start_end[2];
	FILE* fp_2;
    	fp_2 = fopen(argv[2],"r");
	if(fp_2 != NULL){
	    numq = atoi(fgets(strr,100,fp_2));
	    printf("%swtf\n",strr);
	    struct query q;
  	    //split
	    int c = 0;
	    while(c != numq){
		readd = getline(&linee, &lenn, fp_2);
	    	char * pchh;
		int n = 0;
  	    	pchh = strtok (linee," ");
  	    	while (pchh != NULL){
    	            start_end[n]=atoi(pchh);
    	            printf("split%d\n",start_end[1]);
    	            pchh = strtok (NULL, " ");
    	            n++;
  	    	}
		q.start[c] = start_end[0];
		q.end[c] = start_end[1];
		printf("start:%d end:%d \n",q.start[c],q.end[c]);
		c++;
	    }
		
	}
    }
    
    return 0;
}

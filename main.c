#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "dag.h"
#include "order_core.h"
#include "order_deg.h"
#include "order_rand.h"
#include "order_df.h"

//compute the maximum of three unsigned
unsigned max3(unsigned a,unsigned b,unsigned c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the edgelist from file
dag* readedgelist(char* edgelist){
	unsigned e1=NLINKS;
	dag *g=malloc(sizeof(dag));
	FILE *file;

	g->n=0;
	g->e=0;
	file=fopen(edgelist,"r");
	g->edges=malloc(e1*sizeof(edge));
	while (fscanf(file,"%u %u\n", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);
		if (++(g->e)==e1) {
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);
	g->n++;
	g->edges=realloc(g->edges,g->e*sizeof(edge));
	return g;
}

void freedag(dag *g){
	free(g->edges);
	free(g->rank);
	free(g);
}

void printorder(dag* g, char* output){
	FILE *file=fopen(output,"w");
	unsigned i;
	for (i=0;i<g->n;i++){
		fprintf(file,"%u\n",g->rank[i]);
	}
	fclose(file);
}

//NOT USED HERE
void printorder_inverse(dag* g, char* output){
	FILE *file=fopen(output,"w");
	unsigned i;
	for (i=0;i<g->n;i++){
		fprintf(file,"%u\n",g->rank[g->n-1-i]);
	}
	fclose(file);
}

//NOT USED HERE
void printmat(dag* g, unsigned n,char* output){
	FILE *file;
	unsigned i,k=g->n/n,s,t;
	double *tab=calloc(2*n*n,sizeof(double)),max;

	for (i=0;i<g->e;i++){
		s=g->rank[g->edges[i].s]/k;
		t=g->rank[g->edges[i].t]/k;
		tab[s+n*t]++;
		tab[t+n*s]++;
	}
	file=fopen(output,"w");
	for (i=0;i<n*n;i++){
		fprintf(file,"%u %u %lf\n",i/n,i%n,tab[i]);///(k*k));
		fprintf(file,"%u %u %lf\n",i%n,i/n,tab[i]);///(k*k));
	}
	fclose(file);

}


int main(int argc,char** argv){
	dag* g;
	unsigned i;
	unsigned long long *nck;

	time_t t0,t1,t2;
	t1=time(NULL);
	t0=t1;

	printf("Reading edgelist from file %s\n",argv[1]);
	g=readedgelist(argv[1]);

	t2=time(NULL);
	printf("- Time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	t1=t2;

	printf("Number of nodes: %u\n",g->n);
	printf("Number of edges: %u\n",g->e);
	printf("Building the graph structure\n");
	if (strcmp(argv[2],"rand")==0){
		printf("Computing random ordering\n");
		rand_ord(g);
	}
	else if (strcmp(argv[2],"core")==0){
		printf("Computing degeneracy ordering\n");
		core_ord(g);
	}
	else if (strcmp(argv[2],"icore")==0){
		printf("Computing inverted degeneracy ordering\n");
		icore_ord(g);
	}
	else if (strcmp(argv[2],"df")==0){
		printf("Computing density-friendly ordering\n");
		df_ord(g);
	}
	else{
		printf("Computing degree ordering\n");
		deg_ord(g);
	}

	
	printorder(g,argv[3]);

	//printmat(g,100,argv[4]);

	t2=time(NULL);
	printf("- Time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	t1=t2;

	printf("\n- Evaluating amount of work:\n");
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t0)/3600,((t2-t0)%3600)/60,((t2-t0)%60));

	return 0;
}

#include "order_rand.h"


void rand_ord(dag *g) {
	unsigned i,j,k;
	g->rank=malloc(g->n*sizeof(unsigned));
	for (i=0;i<g->n;i++) {
			g->rank[i]=i;
	}
  srand(time(NULL));
  for (i=g->n-1;i>0;i--){
    j=rand()%i;
    k=g->rank[j];
    g->rank[j]=g->rank[i];
    g->rank[i]=k;
  }
}

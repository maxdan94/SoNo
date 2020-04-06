#include "order_df.h"

//for degree ordering
int compare_noderate(void const *a, void const *b){
	noderate const *pa = a;
	noderate const *pb = b;
	return (pa->rate < pb->rate) ? 1 : -1;
}

void df_ord(dag *g) {
	unsigned i,j,k;
	edge ed;
	unsigned *rates=malloc(g->n*sizeof(unsigned));
	noderate *noderatelist=malloc(g->n*sizeof(noderate));
	for (k=0;k<REP;k++){
		for (i=0;i<g->e;i++) {
			ed=g->edges[i];
			if (rates[ed.s]<rates[ed.t]){
				rates[g->edges[i].s]++;
			}
			else{
				rates[g->edges[i].t]++;
			}
		}
	}
	for (i=0;i<g->n;i++) {
		noderatelist[i].node=i;
		noderatelist[i].rate=rates[i];
	}
	free(rates);
	qsort(noderatelist,g->n,sizeof(noderate),compare_noderate);
	g->rank=malloc(g->n*sizeof(unsigned));
	for (i=0;i<g->n;i++) {
			g->rank[noderatelist[i].node]=i;
	}
	free(noderatelist);
}

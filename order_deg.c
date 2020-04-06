#include "order_deg.h"

//for degree ordering
int compare_nodedeg(void const *a, void const *b){
	nodedeg const *pa = a;
	nodedeg const *pb = b;
	return (pa->deg < pb->deg) ? 1 : -1;
}

void deg_ord(dag *g) {
	unsigned i,j;
	nodedeg *nodedeglist=malloc(g->n*sizeof(nodedeg));
	for (i=0;i<g->n;i++) {
		nodedeglist[i].node=i;
		nodedeglist[i].deg=0;
	}
	for (i=0;i<g->e;i++) {
		nodedeglist[g->edges[i].s].deg++;
		nodedeglist[g->edges[i].t].deg++;
	}
	qsort(nodedeglist,g->n,sizeof(nodedeg),compare_nodedeg);
	g->rank=malloc(g->n*sizeof(unsigned));
	for (i=0;i<g->n;i++) {
			g->rank[nodedeglist[i].node]=i;
	}
	free(nodedeglist);
}

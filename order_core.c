#include "order_core.h"

bheap *construct(unsigned n_max){
	unsigned i;
	bheap *heap=malloc(sizeof(bheap));

	heap->n_max=n_max;
	heap->n=0;
	heap->pt=malloc(n_max*sizeof(unsigned));
	for (i=0;i<n_max;i++) heap->pt[i]=-1;
	heap->kv=malloc(n_max*sizeof(keyvalue));
	return heap;
}

void swap(bheap *heap,unsigned i, unsigned j) {
	keyvalue kv_tmp=heap->kv[i];
	unsigned pt_tmp=heap->pt[kv_tmp.key];
	heap->pt[heap->kv[i].key]=heap->pt[heap->kv[j].key];
	heap->kv[i]=heap->kv[j];
	heap->pt[heap->kv[j].key]=pt_tmp;
	heap->kv[j]=kv_tmp;
}

void bubble_up(bheap *heap,unsigned i) {
	unsigned j=(i-1)/2;
	while (i>0) {
		if (heap->kv[j].value>heap->kv[i].value) {
			swap(heap,i,j);
			i=j;
			j=(i-1)/2;
		}
		else break;
	}
}

void bubble_down(bheap *heap) {
	unsigned i=0,j1=1,j2=2,j;
	while (j1<heap->n) {
		j=( (j2<heap->n) && (heap->kv[j2].value<heap->kv[j1].value) ) ? j2 : j1 ;
		if (heap->kv[j].value < heap->kv[i].value) {
			swap(heap,i,j);
			i=j;
			j1=2*i+1;
			j2=j1+1;
			continue;
		}
		break;
	}
}

void insert(bheap *heap,keyvalue kv){
	heap->pt[kv.key]=(heap->n)++;
	heap->kv[heap->n-1]=kv;
	bubble_up(heap,heap->n-1);
}

void update(bheap *heap,unsigned key){
	unsigned i=heap->pt[key];
	if (i!=-1){
		((heap->kv[i]).value)--;
		bubble_up(heap,i);
	}
}

void bubble_down2(bheap *heap,unsigned i) {
	unsigned j1=2*i+1,j2=j1+1,j;
	while (j1<heap->n) {
		j=( (j2<heap->n) && (heap->kv[j2].value<heap->kv[j1].value) ) ? j2 : j1 ;
		if (heap->kv[j].value < heap->kv[i].value) {
			swap(heap,i,j);
			i=j;
			j1=2*i+1;
			j2=j1+1;
			continue;
		}
		break;
	}
}

void update2(bheap *heap,unsigned key){
	unsigned i=heap->pt[key];
	if (i!=-1){
		((heap->kv[i]).value)++;
		bubble_down2(heap,i);
	}
}




keyvalue popmin(bheap *heap){
	keyvalue min=heap->kv[0];
	heap->pt[min.key]=-1;
	heap->kv[0]=heap->kv[--(heap->n)];
	heap->pt[heap->kv[0].key]=0;
	bubble_down(heap);
	return min;
}


//Building the heap structure with (key,value)=(node,degree) for each node
bheap* mkheap(unsigned n,unsigned *v){
	unsigned i;
	keyvalue kv;
	bheap* heap=construct(n);
	for (i=0;i<n;i++){
		kv.key=i;
		kv.value=v[i];
		insert(heap,kv);
	}
	return heap;
}

void freeheap(bheap *heap){
	free(heap->pt);
	free(heap->kv);
	free(heap);
}

//computing degeneracy ordering and core value
void core_ord(dag* g){
	unsigned i,j,r=0,n=g->n;
	keyvalue kv;
	bheap *heap;

	unsigned *d0=calloc(g->n,sizeof(unsigned));
	unsigned *cd0=malloc((g->n+1)*sizeof(unsigned));
	unsigned *adj0=malloc(2*g->e*sizeof(unsigned));
	for (i=0;i<g->e;i++) {
		d0[g->edges[i].s]++;
		d0[g->edges[i].t]++;
	}
	cd0[0]=0;
	for (i=1;i<g->n+1;i++) {
		cd0[i]=cd0[i-1]+d0[i-1];
		d0[i-1]=0;
	}
	for (i=0;i<g->e;i++) {
		adj0[ cd0[g->edges[i].s] + d0[ g->edges[i].s ]++ ]=g->edges[i].t;
		adj0[ cd0[g->edges[i].t] + d0[ g->edges[i].t ]++ ]=g->edges[i].s;
	}

	heap=mkheap(n,d0);

	g->rank=malloc(g->n*sizeof(unsigned));
	for (i=0;i<g->n;i++){
		kv=popmin(heap);
		g->rank[kv.key]=n-(++r);
		for (j=cd0[kv.key];j<cd0[kv.key+1];j++){
			update(heap,adj0[j]);
		}
	}
	freeheap(heap);
	free(d0);
	free(cd0);
	free(adj0);
}


//computing degeneracy ordering and core value
void icore_ord(dag* g){
	unsigned i,j,r=0,n=g->n;
	keyvalue kv;
	bheap *heap;

	unsigned *d0=calloc(g->n,sizeof(unsigned));
	unsigned *cd0=malloc((g->n+1)*sizeof(unsigned));
	unsigned *adj0=malloc(2*g->e*sizeof(unsigned));
	for (i=0;i<g->e;i++) {
		d0[g->edges[i].s]++;
		d0[g->edges[i].t]++;
	}
	cd0[0]=0;
	for (i=1;i<g->n+1;i++) {
		cd0[i]=cd0[i-1]+d0[i-1];
		d0[i-1]=0;
	}
	for (i=0;i<g->e;i++) {
		adj0[ cd0[g->edges[i].s] + d0[ g->edges[i].s ]++ ]=g->edges[i].t;
		adj0[ cd0[g->edges[i].t] + d0[ g->edges[i].t ]++ ]=g->edges[i].s;
	}

	for (i=0;i<g->n;i++) {
		d0[i]=g->n-d0[i];////////////////////////////
	}

	heap=mkheap(n,d0);

	g->rank=malloc(g->n*sizeof(unsigned));
	for (i=0;i<g->n;i++){
		kv=popmin(heap);
		g->rank[kv.key]=r++;
		for (j=cd0[kv.key];j<cd0[kv.key+1];j++){
			update2(heap,adj0[j]);
		}
	}
	freeheap(heap);
	free(d0);
	free(cd0);
	free(adj0);
}

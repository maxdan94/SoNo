#ifndef CORE_H
#define CORE_H

#include "dag.h"

//heap data structure (for core ordering):
typedef struct {
	unsigned key;
	unsigned value;
} keyvalue;

typedef struct {
	unsigned n_max;	// max number of nodes.
	unsigned n;	// number of nodes.
	unsigned *pt;	// pointers to nodes.
	keyvalue *kv; // nodes.
} bheap;

bheap *construct(unsigned);
void swap(bheap*,unsigned, unsigned);
void bubble_up(bheap*,unsigned);
void bubble_down(bheap*);
void insert(bheap*,keyvalue);
void update(bheap*,unsigned);
keyvalue popmin(bheap*);
bheap* mkheap(unsigned,unsigned*);
void freeheap(bheap*);
void core_ord(dag*);
void icore_ord(dag*);



#endif

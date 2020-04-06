#ifndef DAG_H
#define DAG_H

#include <stdlib.h>
#include <stdio.h>

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

typedef struct {
	unsigned s;
	unsigned t;
} edge;

typedef struct {
	//edge list structure:
	unsigned n;//number of nodes
	unsigned e;//number of edges
	edge *edges;//list of edges

  //ranking nodes to form the DAG
	unsigned *rank;//rank[ID]=ranking of node i (i.e. newID)

} dag;

#endif

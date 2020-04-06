#ifndef DEG_H
#define DEG_H

#include "dag.h"

typedef struct {
	unsigned node;
	unsigned deg;
} nodedeg;

int compare_nodedeg(void const*, void const*);
void deg_ord(dag*);

#endif

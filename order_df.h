#ifndef DF_H
#define DF_H

#include "dag.h"

#define REP 300 //number of iterations for the approximate density-friendly

typedef struct {
	unsigned node;
	unsigned rate;
} noderate;

int compare_noderate(void const*, void const*);
void df_ord(dag*);

#endif

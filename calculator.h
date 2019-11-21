#include <stdio.h>
#include <stdlib.h>

typedef struct fnode{
	int d1;
	*p1;
	*n1;
	*head;

} fnode;


typedef struct snode{
	int d2;
	*p2;
	*n2;
	*n1 = &d2;
	*p2 = &d1;
} snode;


typedef struct tnode{
	int d3;
	*p3;
	*n3;
	*n2 = &d3;
	*p3 = &d2;
} tnode;




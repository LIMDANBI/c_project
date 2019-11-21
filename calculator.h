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
} snode;


typedef struct tnode{
	int d3;
	*p3;
	*n3;
} tnode;

typedef struct nodeconnect{
	*n1 = &d2;
	*n2 = &d3;
	*p2 = &d1;
	*p3 = &d2;




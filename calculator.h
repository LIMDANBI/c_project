#include <stdio.h>
#include <stdlib.h>

#define K 10

typedef struct fnode{
	int d1;
	struct fnode* p1;
	struct fnode* n1;
	*head;
} fnode;


typedef struct snode{
	int d2;
	struct snode* p2;
	struct snode* n2;
} snode;


typedef struct tnode{
	int d3;
	struct tnode* p3;
	struct tnode* n3;
} tnode;

typedef struct nodeconnect{
	*n1 = &d2;
	*n2 = &d3;
	*p2 = &d1;
	*p3 = &d2;


typedef struct numdata(*n) {
       	a[K] = {0,1,2,3,4,5,6,7,8,9};
	

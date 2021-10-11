#include <stdio.h>
#include "main.h"
#include "arr.h"

int main(int argc, char **argv)
{
	struct vararr vararr;
	int i;

	vararr_init(&vararr, 128);
	
	for(i=0; i<10000; i++){
		vararr_set(&vararr, i, i);
	}

	for(i=0; i<10000; i++){
		printf("%d ", vararr_get(&vararr, i));
	}
	printf("\n");

	vararr_deinit(&vararr);
	
	return 0;
}

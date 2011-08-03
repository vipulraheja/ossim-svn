#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char fname[100];
	char c;
 
	c = '%';

	FILE *f;
	FILE *fo;
	f = fopen("../master.i","r");
	fo = fopen("out","w");

	while(fscanf(f, "%s", fname)!=EOF)
		fprintf(fo, "%cinclude \"%s\"\n", c,fname);

	return 0;
}

#include <stdio.h>
#include <stdlib.h> // for exit() function

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "[failed][args] must include only a PID in input args\n");
		exit(1);
	}

	fprintf(stdout, "[info] target pid: %s\n", argv[1]);

	return 0;
}

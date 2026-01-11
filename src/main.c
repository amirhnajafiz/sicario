#include "proc.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h> // for exit() function

int main(int argc, char **argv)
{
	// check the input parameters
	if (argc != 2)
	{
		fprintf(stderr, "[failed][args] must include only a PID in input args.\n");
		exit(1);
	}

	// copy the pid from input parameters
	char *pid_str = argv[1];
	fprintf(stdout, "[info] target pid: %s\n", pid_str);

	// convert the pid to int for validation check
	int pid = pid_from_str(pid_str);
	if (pid < 1)
	{
		fprintf(stderr, "[failed][pid] pid must be a positive valid number!\n");
		exit(1);
	}

	// check if proc exists
	if (!proc_exists(pid))
	{
		fprintf(stderr, "[failed][proc] pid does not exist or stopped!\n");
		exit(0);
	}

	// check if IO is exported
	if (!proc_io_available(pid))
	{
		fprintf(stderr, "[failed][io] io metrics are not exported for this process.");
		exit(0);
	}

	return 0;
}

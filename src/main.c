#include "io.h"
#include "logging.h"
#include "proc.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h> // for exit() function
#include <unistd.h> // for sleep() function

int main(int argc, char **argv)
{
	// check the input parameters
	if (argc != 2)
	{
		log_fatal("must include only a PID in input args.");
		exit(1);
	}

	// copy the pid from input parameters
	char *pid_str = argv[1];
	log_info("target pid: %s", pid_str);

	// convert the pid to int for validation check
	int pid = pid_from_str(pid_str);
	if (pid < 1)
	{
		log_fatal("pid must be a positive valid number!");
		exit(1);
	}

	// check if proc exists
	if (!proc_exists(pid))
	{
		log_fatal("pid does not exist or stopped!");
		exit(0);
	}

	// check if IO is exported
	if (!proc_io_available(pid))
	{
		log_fatal("io metrics are not exported for this process.");
		exit(0);
	}

	while (true)
	{
		// get proc metadata
		proc_metadata *metadata = get_proc_metadata(pid);
		if (metadata->err != 0)
		{
			log_fatal("failed to get process metadata.");
			exit(1);
		}

		log_info(
			"metadata\n\tpid: %d\n\tcommand: %s\n\tstatus: %s",
			metadata->pid, 
			metadata->procname, 
			metadata->state
		);

		// get io metrics
		io_metrics *metrics = get_io_metrics(pid);
		if (metrics->err != 0)
		{
			log_fatal("failed to get process io metrics.");
			exit(1);
		}

		log_info(
			"metrics\n\tread_bytes: %llu\n\twrite_bytes: %llu\n\tsyscr: %llu\n\tsyscw: %llu",
			metrics->read_bytes,
			metrics->write_bytes,
			metrics->syscr,
			metrics->syscw
		);

		// free resources
		free(metadata);
		free(metrics);

		// wait 5 seconds
		sleep(5);
	}

	return 0;
}

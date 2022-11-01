#include <stdio.h>
#include <string.h>

enum Check {
	FINISH,
	PRIORITY,
	CONTEXTS_TAGS
};

Task line_to_task(FILE * file);
Task * file_to_tasks(FILE * file, Task * tasks);
Task parse_task(Task task);

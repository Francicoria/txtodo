#include <stdio.h>

void save(FILE * file, char * buffer) {
	fwrite(buffer, sizeof(char), strlen(buffer), file);
}

Task * cliEdit(FILE * file) {
	Task empty_tasks[MAX_TASKS];
	char * text = "Buffer \npoggggg!";
	return text;
}

#include <stdio.h>

enum Status {
	ACTIVE,
	FINISHED
};

typedef struct {
	char * task;
	int status;
	char priority_letter;
	char * contexts;
	char * tags;
} Task;

void se

void fileToTasks(FILE * file, Task * tasks) {
	int line = 0;
	int str_index = 0;
	for (int c; (c = getc(file)) != EOF;) {
		if (c == '\n') {
			++line;
			str_index = 0;
		} else tasks[line].task[str_index++] = c;
	}
}

Task * parseTasks(Task * tasks) {
	return tasks;
}

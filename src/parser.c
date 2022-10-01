#include <stdio.h>
#include <string.h>

Task fileLineToTask(FILE * file) {
	Task task;
	task.task[0] = '\0';
	int strIndex = 0;
	for (int c; (c = getc(file)) != '\n';) {
		if (c == EOF) break;
		task.task[strIndex++] = c;
	}
	task.task[strIndex] = '\0';
	return task;
}

enum Check {
	FINISH,
	PRIORITY,
	CONTEXTS_TAGS
};

Task parseTask(Task task) {
	int check = FINISH;
	char * token;

	task.contexts[0] = '\0';
	task.tags[0] = '\0';

	token = strtok(task.task, " ");

	while (token != NULL) {
		switch (check) {
			case FINISH:
				if (token[0] == 'x' &&
				    token[1] == '\0') {
					task.status = FINISHED;
					token = strtok(NULL, " ");
				} else task.status = ACTIVE;
				check = PRIORITY;
				break;
			case PRIORITY:
				if (token[0] == '(' &&
				    token[2] == ')' &&
				    token[3] == '\0') {
					task.priorityLetter = token[1];
					token = strtok(NULL, " ");
				} else task.priorityLetter = '#';
				check = CONTEXTS_TAGS;
				token = strtok(NULL, " ");
				break;
			case CONTEXTS_TAGS:
				if (token[0] == '@' &&
				    token[1] != '\0') {
					strcat(task.contexts, token);
					strcat(task.contexts, " ");
				}
				if (token[0] == '+' &&
				    token[1] != '\0') {
					strcat(task.tags, token);
					strcat(task.tags, " ");
				}
				token = strtok(NULL, " ");
				break;
		}
	}
	return task;
}

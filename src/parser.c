#include <stdio.h>
#include <string.h>

Task fileLineToTask(FILE * file) {
	Task task;
	task.task[0] = '\0';
	int strIndex = 0;
	for (int c; (c = getc(file)) != '\n'; ++strIndex) {
		if (c == EOF) break;
		task.task[strIndex] = c;
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
	char taskBody[MAX_TASK_SIZE] = {0};
	for (int i = 0; task.task[i] != '\0'; ++i) {
		taskBody[i] = task.task[i];
		taskBody[i + 1] = '\0';
	}

	task.contexts[0] = '\0';
	task.tags[0]     = '\0';

	token = strtok(taskBody, " ");

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

#include <stdio.h>
#include <string.h>

Task line_to_task(FILE * file) {
	Task task = {.task[0] = '\0'};
	char buf[MAX_TASK_SIZE];
	fgets(buf, MAX_TASK_SIZE, file);
	if (feof(file)) {
		task.status = LAST;
		return task;
	}
	if (strchr(buf, '\n') != NULL) memset(strchr(buf, '\n'), '\0', 1);
	strcpy(task.task, buf);
	task.status = (task.task[0] == '\0') ? EMPTY : ACTIVE;
	return task;
}
Task * file_to_tasks(FILE * file, Task * tasks) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		tasks[i] = line_to_task(file);
		if (tasks[i].status == LAST) break;
		tasks[i] = parse_task(tasks[i]);
		// skip line if it's empty.
		if (tasks[i].status == EMPTY) continue;
	}
	return tasks;
}


enum Check {
	FINISH,
	PRIORITY,
	CONTEXTS_TAGS
};

Task parse_task(Task task) {
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
				/*if (token[0] == 'x' &&
				    token[1] == '\0')*/
				if (strncmp(token, "x", 1)) {
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

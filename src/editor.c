#include <stdio.h>
#include <stdlib.h>
#include "start.h"
#include "parser.h"
#include "editor.h"

void save(FILE * file, char * filename, Task tasks[]) {
	if ((file = freopen(filename, "w", file)) == NULL) {
		perror("ERROR");
		exit(1);
	}
	for (int i = 0; i < MAX_TASKS; ++i) {
		if (tasks[i].status == EMPTY) continue;
		if (tasks[i].status == LAST) break;
		strcat(tasks[i].task, "\n");
		fwrite(tasks[i].task, sizeof(char), strlen(tasks[i].task), file);
	}
}

void print_preview(Task tasks[], int selectedTask) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		if (tasks[i].status == LAST) break;
		// I know this looks like shit, they are just exit codes
		// to have fancy colors and italic/bold.
		if (tasks[i].status == EMPTY) {
			printf(" \x1b[3m%s%3d%s   <empty line>\x1b[m\n",
			       (i == selectedTask) ? "\x1b[1m[" : "",
			       i,
			       (i == selectedTask) ? "]\x1b[m\x1b[3m" : ""
			       );
			continue;
		}
		if (i == selectedTask)	printf(" \x1b[1m[%3d]\x1b[m   ", i);
		else			printf(" %3d   ", i);

		puts(tasks[i].task);
	}
}

char * get_prompt(char * prompt) {
	char buffer[512];
	char * token;
	int command;

	fputs("\x1b[35m-Edit mode- >\x1b[m ", stdout);
	fgets(buffer, 512, stdin);
	if (buffer == NULL || buffer[0] == '\n') return "";
	buffer[strcspn(buffer, "\n")] = '\0';

	token = strtok(buffer, " ");
	if (token == NULL) command = token[0];
	else if (strlen(token) != 1) {
		fprintf(stderr, "Command lenght is more then 1 character\n");
		exit(1);
	}
	command = token[0];

	switch (command) {
		case DELETE: return "d ";
		case NEW_TASK:
		case REPLACE:
		    token = strtok(NULL, " ");
		    if (token == NULL) exit(1);
		    prompt[0] = command; // either 'n' or 'r'
		    strcat(prompt, token);
		    strcat(prompt, " ");
		    break;
		default:
		    fprintf(stderr, "Command is not recognized\n");
		    exit(1);
	}

	while (token != NULL) {
		token = strtok(NULL, " ");
		if (token == NULL) break;
		strcat(prompt, token);
		strcat(prompt, " ");
	}
	return prompt;
}

Task * delete_task(Task tasks[], int index) {
	for (; index < MAX_TASKS; ++index) {
		if (tasks[index].status == LAST) break;
		tasks[index] = tasks[index + 1];
	}
	return tasks;
}

Task * create_task(Task tasks[], int index, char * taskBody) {
	int newTaskLine = index + 1;
	Task bufferTasks[MAX_TASKS];
	for (int i = 0; i < MAX_TASKS; ++i) {
		bufferTasks[i] = tasks[i];
		if (tasks[i].status == LAST) break;
	}

	for (index += 2; index < MAX_TASKS; ++index) {
		tasks[index] = bufferTasks[index - 1];
		if (tasks[index].status == LAST) break;
	}
	strcpy(tasks[newTaskLine].task, taskBody);
	return tasks;
}

Task * edit_mode(Task tasks[], int selectedTask) {
	char * string = (char *) calloc(256, sizeof(char));
	if (string == NULL) {
		fprintf(stderr, "Call to calloc() failed.\n");
	}
	char * rawPrompt = get_prompt(string);
	char * prompt = rawPrompt + 1;
	switch (rawPrompt[0]) {
		case DELETE:
		    delete_task(tasks, selectedTask);
		    break;
		case REPLACE:
		    strcpy(tasks[selectedTask].task, prompt);
		    break;
		case NEW_TASK:
		    create_task(tasks, selectedTask, prompt);
		    break;
		default:
		    break;
	}
	free(string);
	return tasks;
}

int get_command(void) {
	int command;
	int c;
	char buffer[256];
	int i = 0;

	fputs("\x1b[36m-View mode- >\x1b[m ", stdout);
	while ((c = getc(stdin)) != '\n') {
		if (c == EOF) exit(1);
		buffer[i++] = c;
		buffer[i] = '\0';
	}
	if (buffer[1] == '\0') command = buffer[0];
	else command = NOTHING;
	return command;
}

Task * view_mode(Task tasks[]) {
	int selectedTask = 0;
	int command = NOTHING;
	clear_screen
	do {
		//print_preview(tasks, selectedTask);
		//printf("command = %d\n", command);
		while (tasks[selectedTask].status == LAST) selectedTask -= 1;
		switch (command) {
			case UP:
			    // Stops you from going below the n??0 task.
			    selectedTask -= (selectedTask == 0) ? 0 : 1;
			    break;
			case DOWN:
			    // Stops you from going above the last task.
			    selectedTask += (selectedTask == MAX_TASKS || tasks[selectedTask + 1].status == LAST) ? 0 : 1;
			    break;

			case EDIT:
			    tasks = edit_mode(tasks, selectedTask);
			    break;
			case NOTHING:
			default: break;
		}
		clear_screen
	} while (print_preview(tasks, selectedTask), (command = get_command()) != QUIT);
	return tasks;
}

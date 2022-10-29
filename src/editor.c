#include <stdio.h>
#include <stdlib.h>

void save(FILE * file, Task tasks[]) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		// If the first character of a line is ^
		// i assume that the rest of the file is empty.
		if (tasks[i].task[0] == '^') break;
		if (tasks[i].task[0] == '\0') continue;
		strcat(tasks[i].task, "\n");
		fwrite(tasks[i].task, sizeof(char), strlen(tasks[i].task), file);
	}
}

void printPreview(Task tasks[], int selectedTask) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		// If the first character of a line is ^
		// i assume that the rest of the file is empty.
		if (tasks[i].task[0] == '^') break;
		// skip line if it's empty.
		if (tasks[i].task[0] == '\0') continue;

		if (i == selectedTask) printf("[%3d]  ", i);
		else		       printf(" %3d   ", i);

		puts(tasks[i].task);
	}
}

enum EditModeCommands {
	INSERT = 'i',
	DELETE = 'd'
};

enum Commands {
	DOWN = 'j',
	UP   = 'k',
	EDIT = 'e',
	QUIT = 'q',
	NOTHING = ' '
};

char * getPrompt(void) {
	char buffer[512];
	char * token;
	int command;
	char * prompt;
	if ((prompt = malloc(sizeof(char) * 256)) == NULL) {
		fprintf(stderr, "Call to malloc() failed.\n");
		exit(1);
	}

	fputs("-Edit mode- > ", stdout);
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
		case INSERT:
		    token = strtok(NULL, " ");
		    if (token == NULL) exit(1);
		    strcpy(prompt, "i ");
		    strcat(prompt, token);
		    break;
		case DELETE: return "x";
		default:
		    fprintf(stderr, "Command is not recognized\n");
		    exit(1);
	}

	while (token != NULL) {
		token = strtok(NULL, " ");
		if (token == NULL) break;
		strcat(prompt, token);
	}
	return prompt;
}

Task * deleteTaskFromTaskArray(Task tasks[], int index) {
	for (; index < MAX_TASKS; ++index) {
		if (tasks[index].task[0] == '^') break;
		tasks[index] = tasks[index + 1];
	}
	return tasks;
}

Task * editMode(Task tasks[], int selectedTask) {
	char * prompt = getPrompt();
	if (prompt[0] == 'x') deleteTaskFromTaskArray(tasks, selectedTask);
	free(prompt);
	return tasks;
}

int getCommand(void) {
	int command;
	int c;
	char buffer[256];
	int i = 0;

	fputs("-View mode- > ", stdout);
	while ((c = getc(stdin)) != '\n') {
		if (c == EOF) exit(1);
		buffer[i++] = c;
		buffer[i] = '\0';
	}
	if (buffer[1] == '\0') command = buffer[0];
	else command = NOTHING;
	return command;
}

Task * viewMode(Task tasks[]) {
	int selectedTask = 0;
	int command;
	while (printPreview(tasks, selectedTask), (command = getCommand()) != QUIT) {
		//printPreview(tasks, selectedTask);
		//printf("command = %d\n", command);
		while (tasks[selectedTask].task[0] == '^') selectedTask -= 1;
		switch (command) {
			case UP:
			    selectedTask -= (selectedTask == 0) ? 0 : 1;
			    break;
			case DOWN:
			    if (selectedTask == MAX_TASKS || tasks[selectedTask + 1].task[0] == '^') selectedTask += 0;
			    else selectedTask += 1;
			    break;

			case EDIT:
			    tasks = editMode(tasks, selectedTask);
			    break;
			case NOTHING:
			default: break;
		}
	}
	return tasks;
}

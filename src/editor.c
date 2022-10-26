#include <stdio.h>
#include <stdlib.h>

void save(FILE * file, Task tasks[]) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		// If the first character of a line is end of line (\0)
		// i assume that the rest of the file is empty.
		if (tasks[i].task[0] == '\0') break;
		//printf("%s\n", tasks[i].task);
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

enum Commands {
	DOWN = 'j',
	UP   = 'k',
	QUIT = 'q',
	NOTHING = ' '
};

int getCommand(void) {
	int command;
	int c;
	char buffer[256];
	int i = 0;

	fputs("> ", stdout);
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
	while ((command = getCommand()) != QUIT) {
		//printf("command = %d\n", command);
		switch (command) {
			case UP:
				selectedTask -= (selectedTask == 0) ? 0 : 1;
				break;
			case DOWN:
				if (selectedTask == MAX_TASKS || tasks[selectedTask + 1].task[0] == '^')
					selectedTask += 0;
				else	selectedTask += 1;
				break;

			case NOTHING:
			default: break;
		}
		printPreview(tasks, selectedTask);
	}
	return tasks;
}

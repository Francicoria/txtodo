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

void printPreview(Task tasks[]) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		// If the first character of a line is ^
		// i assume that the rest of the file is empty.
		if (tasks[i].task[0] == '^') break;
		// skip line if it's empty.
		if (tasks[i].task[0] == '\0') continue;

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
	while ((c = fgetc(stdin)) != '\n') {
		if (c == EOF) exit(1);
		buffer[i++] = c;
		buffer[i] = '\0';
	}
	if (buffer[1] == '\0') command = buffer[0];
	else command = NOTHING;
	return command;
}

Task * cliEdit(Task empty_tasks[]) {
	strcpy(empty_tasks[0].task, "Hello!");
	strcpy(empty_tasks[1].task, "Another one line of dust.");
	strcpy(empty_tasks[2].task, "^");

	int command;
	while ((command = getCommand()) != QUIT) {
		printPreview(empty_tasks);
		switch (command) {
			UP: break;
			DOWN: break;
			NOTHING:
			default: break;
		}
	}
	return empty_tasks;
}

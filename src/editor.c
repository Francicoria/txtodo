#include <stdio.h>

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

Task * cliEdit(Task empty_tasks[]) {
	strcpy(empty_tasks[0].task, "Hello!");
	strcpy(empty_tasks[1].task, "Another one line of dust.");
	strcpy(empty_tasks[2].task, "^");
	printPreview(empty_tasks);
	return empty_tasks;
}

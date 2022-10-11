#include <stdio.h>

void save(FILE * file, Task tasks[]) {
	for (int i = 0; i < MAX_TASKS; ++i) {
		// If the first character of a line is end of line (\0)
		// i assume that the rest of the file is empty.
		if (tasks[i].task[0] == '\0') break;
		//printf("%s\n", tasks[i].task);
		fwrite(tasks[i].task, sizeof(char), strlen(tasks[i].task), file);
	}
}

Task cli_tasks[MAX_TASKS];

Task * cliEdit(void) {
	strcpy(cli_tasks[0].task, "Hello!\n");
	strcpy(cli_tasks[1].task, "Another one line of dust.\n");
	//tasks[0].task = "Ciao.";
	return cli_tasks;
}

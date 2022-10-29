#include <stdio.h>
#include <time.h>

// if the user exceeds any of these caps, i would be impressed.
#define MAX_TASKS          70
#define MAX_CONTEXTS_SIZE  40
#define MAX_TAGS_SIZE      40
#define MAX_TASK_SIZE      (MAX_CONTEXTS_SIZE + MAX_TAGS_SIZE) + 50


enum Status {
	ACTIVE   = 1,
	FINISHED = 0
};

typedef struct {
	char task[MAX_TASK_SIZE];
	int status;
	char priorityLetter;
	char contexts[MAX_CONTEXTS_SIZE];
	char tags[MAX_TAGS_SIZE];
} Task;

#include "parser.c"
#include "editor.c"

double timeID(void) {
	struct tm the2000 = {
		.tm_sec = 0,  .tm_min = 0, .tm_hour = 0,
		.tm_mday = 0, .tm_mon = 0, .tm_year = 120,
		.tm_yday = 0
		};	
	time_t now = time(NULL);
	return difftime(now, mktime(&the2000));
}

int main(int argc, char ** argv) {
	FILE * fp;
	char filename[1024] = {0};

	switch (argc) {
		case 1:
			// TODO
			printf("No argument passed, assuming you want to create a new todo.txt file.\n");
			double filenameTmpID = timeID();
			snprintf(filename, 90, "tmp_%.f.todo.txt", filenameTmpID);
			if ((fp = fopen(filename, "w+")) == NULL) {
				perror("ERROR");
				return 1;
			}
			Task empty_tasks[MAX_TASKS];
			strcpy(empty_tasks[0].task, "Hello!");
			strcpy(empty_tasks[1].task, "Another one line of dust.");
			strcpy(empty_tasks[2].task, "Byeeee");
			strcpy(empty_tasks[3].task, "^");
			Task * newTasks = viewMode(empty_tasks);
			save(fp, newTasks);
			break;
		case 2:
			strcpy(filename, argv[1]);

			if ((fp = fopen(filename, "r+")) == NULL) {
				perror("ERROR");
				return 1;
			}
			Task tasks[MAX_TASKS];
			for (int i = 0; i < MAX_TASKS; ++i) {
				tasks[i] = fileLineToTask(fp);
				// If the first character of a line is ^
				// i assume that the rest of the file is empty.
				if (tasks[i].task[0] == '^') break;

				// skip line if it's empty.
				if (tasks[i].task[0] == '\0') continue;

				tasks[i] = parseTask(tasks[i]);
				printf("Task: %s\nFinished: %s\nPriority: (%c)\nContexts: %s\nTags: %s\n\n",
				       tasks[i].task,
				       tasks[i].status == FINISHED ? "yes" : "no",
				       tasks[i].priorityLetter,
				       tasks[i].contexts,
				       tasks[i].tags
				       );
			}
			//parseFile(fp);
			fclose(fp);
			break;
		default:
			fprintf(stderr, "Only one file can be passed as an argument.\nIf there are spaces in the filename, put apostrophes around it.\n");
			return 1;
	}

	//putc('\n', stdout);
	return 0;
}

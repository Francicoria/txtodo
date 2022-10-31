#include <stdio.h>
#include <time.h>

// if the user exceeds any of these caps, i would be impressed.
#define MAX_TASKS          70
#define MAX_CONTEXTS_SIZE  40
#define MAX_TAGS_SIZE      40
#define MAX_TASK_SIZE      (MAX_CONTEXTS_SIZE + MAX_TAGS_SIZE) + 50

#ifdef _WIN32
#define clear_screen system("cls");
#else
#define clear_screen system("clear");
#endif

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
			printf("No argument passed, assuming you want to create a new todo.txt file.\n");
			double filenameTmpID = timeID();
			snprintf(filename, 90, "tmp_%.f.todo.txt", filenameTmpID);
			if ((fp = fopen(filename, "w+")) == NULL) {
				perror("ERROR");
				return 1;
			}
			Task emptyNewTasks[MAX_TASKS];
			strcpy(emptyNewTasks[0].task, "Hello!");
			strcpy(emptyNewTasks[1].task, "Another one line of dust.");
			strcpy(emptyNewTasks[2].task, "Byeeee");
			strcpy(emptyNewTasks[3].task, "nop actually lel");
			strcpy(emptyNewTasks[4].task, "^");
			Task * newTasks = view_mode(emptyNewTasks);
			save(fp, filename, newTasks);
			break;
		case 2:
			strcpy(filename, argv[1]);

			if ((fp = fopen(filename, "r+")) == NULL) {
				perror("ERROR");
				return 1;
			}
			Task emptyTasks[MAX_TASKS];
			Task * tasks = file_to_tasks(fp, emptyTasks);
			view_mode(tasks);
			save(fp, filename, tasks);
			fclose(fp);
			break;
		default:
			fprintf(stderr, "Only one file can be passed as an argument.\nIf there are spaces in the filename, put apostrophes around it.\n");
			return 1;
	}
	return 0;
}

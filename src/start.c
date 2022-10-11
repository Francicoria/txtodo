#include <stdio.h>
#ifdef WIN32
#include <sys/time.h>
#else
#include <time.h>
#endif
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
		.tm_mday = 0, .tm_mon = 0, .tm_year = 100,
		.tm_yday = 0
		};
	
	time_t now = time(NULL);
	
	double tmpID = difftime(now, mktime(&the2000));
	return tmpID;
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
			Task * newTasks = cliEdit();
			save(fp, newTasks);
			break;
		case 2:
			strcpy(filename, argv[1]);

			if ((fp = fopen(filename, "r+")) == NULL) {
				perror("ERROR");
				return 1;
			}
			//printf("\x1b[3mFilename: \x1b[32m%s\x1b[m\n", argv[1]);
			Task tasks[MAX_TASKS];
			for (int i = 0; i < MAX_TASKS; ++i) {
				tasks[i] = fileLineToTask(fp);
				// If the first character of a line is end of line (\0)
				// i assume that the rest of the file is empty.
				if (tasks[i].task[0] == '\0') break;
				//printf("%s\n", tasks[i].task);

				tasks[i] = parseTask(tasks[i]);
				printf("Task: %s\nIs finished: %s\nPriority letter: %c\nContexts: %s\nTags: %s\n\n",
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

	putc('\n', stdout);
	return 0;
}

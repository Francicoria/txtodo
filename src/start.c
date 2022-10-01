#include <stdio.h>

// if the user exceeds any of these caps, i would be impressed.
#define MAX_TASKS          70
#define MAX_CONTEXTS_SIZE  40
#define MAX_TAGS_SIZE      40
#define MAX_TASK_SIZE      (MAX_CONTEXTS_SIZE + MAX_TAGS_SIZE) + 50


enum Status {
	ACTIVE = 69,
	FINISHED = 420
};

typedef struct {
	char task[MAX_TASK_SIZE];
	int status;
	char priorityLetter;
	char contexts[MAX_CONTEXTS_SIZE];
	char tags[MAX_TAGS_SIZE];
} Task;

#include "parser.c"

int main(int argc, char ** argv) {
	char * filename = {0};
	FILE * fp;

	switch (argc) {
		case 1:
			// TODO
			printf("No argument passed, assuming you want to create a new todo.txt file.\n");
			break;
		case 2:
			filename = argv[1];
			if ((fp = fopen(filename, "r+")) == NULL) {
				fprintf(stderr, "%s does not exist or is not readable/writable.\n", filename);
				return 1;
			}
			Task tasks[MAX_TASKS];
			for (int i = 0; i < MAX_TASKS; ++i) {
				tasks[i] = fileLineToTask(fp);
				// If the first character of a line is end of line (\0)
				// i assume that the rest of the file is empty.
				if (tasks[i].task[0] == '\0') break;
				//printf("%s\n", tasks[i].task);

				tasks[i] = parseTask(tasks[i]);
				printf("Task n°%d\nIs finished: %d\nPriority letter: %c\nContexts: %s\nTags: %s\n",
				       i + 1,
				       tasks[i].status,// == FINISHED ? "yes" : "no",
				       // TODO fixare la merda
				       tasks[i].priorityLetter,
				       tasks[i].contexts,
				       tasks[i].tags
				       );
			}
			//printf("\x1b[3mFilename: \x1b[32m%s\x1b[m\n", argv[1]);
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

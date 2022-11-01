#include <stdio.h>
#include <time.h>
#include "start.h"
#include "parser.h"
#include "editor.h"

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
			Task emptyNewTasks[MAX_TASKS] = {
				{.status = ACTIVE, .task = "Hello!"},
				{.status = ACTIVE, .task = "Another one line of dust."},
				{.status = ACTIVE, .task = "Byeeee"},
				{.status = ACTIVE, .task = "nop actually lel"},
				{.status = LAST}
			};
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

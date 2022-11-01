#include <stdio.h>
#include <time.h>

// if the user exceeds any of these caps, i would be impressed.
#define MAX_TASKS          70
#define MAX_CONTEXTS_SIZE  40
#define MAX_TAGS_SIZE      40
#define MAX_TASK_SIZE      (MAX_CONTEXTS_SIZE + MAX_TAGS_SIZE) + 50

#define clear_screen printf("\x1b[2J\x1b[1;1H");

enum Status {
	// sets if the task is empty
	EMPTY,
	// sets to last if it's the last task in the file/buffer
	LAST,
	ACTIVE,
	FINISHED
};

typedef struct {
	char task[MAX_TASK_SIZE];
	int status;
	char priorityLetter;
	char contexts[MAX_CONTEXTS_SIZE];
	char tags[MAX_TAGS_SIZE];
} Task;

double timeID(void);

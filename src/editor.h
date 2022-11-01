#include <stdio.h>
#include <stdlib.h>

enum Edit_Mode_Commands {
	DELETE = 'd',
	REPLACE = 'r',
	NEW_TASK = 'n'
};

enum Commands {
	DOWN = 'j',
	UP   = 'k',
	EDIT = 'e',
	QUIT = 'q',
	NOTHING = ' '
};

void save(FILE * file, char * filename, Task tasks[]);
void print_preview(Task tasks[], int selectedTask);
char * get_prompt(char * prompt);
int get_command(void);
Task * delete_task(Task tasks[], int index);
Task * create_task(Task tasks[], int index, char * taskBody);
Task * edit_mode(Task tasks[], int selectedTask);
Task * view_mode(Task tasks[]);

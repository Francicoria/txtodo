#include <stdio.h>
#include <string.h>
#define MAX_COLS 90
#define MAX_ROWS 100
#define TAGS_SLOTS 2

enum tags {
	FINISHED = 1,
	PRIORITIZED = 2
};

void parseFile(FILE * in) {
	
	char file[MAX_COLS][MAX_ROWS] = {0};
	int row = 0;
	int col = 0;
	
	char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	
	int c;
	// This puts the content of the file in a char matrix to be more easy to access
	// the first dimention of the matrix is the columns(the single characters)
	// the second dimension is the rows(the lines)
	while ((c = getc(in)) != EOF) {
		if (c == '\n') {
			file[col][row] = '\0';
			++row;
			col = 0;
		} else {
			file[col][row] = c;
			++col;
		}
	}

	int tags[row][TAGS_SLOTS];
	for (int i = 0; i < row; ++i) for (int a = 0; a < TAGS_SLOTS; ++a) tags[i][a] = 0;

	int cursorRow = 0;
	int cursorCol = 0;
	// Goes trough all the rows and assigns them tags(finished, prioritized, etc.)
	while (cursorRow < row) {
		//tags[cursorRow] = "";
		for (; file[cursorCol][cursorRow] != '\0'; ++cursorCol) {
			
			// if the task is finished, just skip all other checks for other tags
			if (file[0][cursorRow] == 'x' &&
			    file[1][cursorRow] == ' ') {
				tags[cursorRow][0] = FINISHED;
				break;
			}

			if (file[0][cursorRow] == '(' &&
			    file[2][cursorRow] == ')') {
				tags[cursorRow][1] = PRIORITIZED;
			}
		}
		cursorCol = 0;
		++cursorRow;
	}
	
	// just prints out content of the matrix
	for (int i = 0; i < row; ++i) {
		for (int y = 0; y < TAGS_SLOTS; ++y) {
			switch (tags[i][y]) {
				case 1:
					printf("FINISHED | ");
					break;
				case 2:
					printf("PRIORITIZED | ");
					break;
				default:
					break;
			}
		}
		for (int a = 0; file[a][i] != '\0'; ++a) putc(file[a][i], stdout);
		putc('\n', stdout);
	}
}

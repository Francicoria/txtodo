#include <stdio.h>
#include <string.h>

char * parseFile(FILE * in) {
	//int c;
	//char prec = 'x';
	//char prec2 = '\n';
	//int isStriked = 0;
	//int isPriority = 0;
	//int isProject = 0;
	//int isContext = 0;
	char * parsedLines = {0};
	
	char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	
	int c;
	while ((c = getc(in)) != EOF) {
		putc(c, stdout);
	}

	// weird way to handle a finished task at the start of the 
	// file, basically starts at 2, while function does a loop,
	// SOF is now 1 and if the other conditions are met,
	// the if conditions works (needs a rework probably)
	//int SOF = 2;

	/*while ((c = getc(in)) != EOF) {
		// check for terminated task.
		if ((prec2 == '\n' || SOF == 1) && prec == 'x' && c == ' ') {
			printf("%c\x1b[9m", c);
			isStriked = 1;
		}
		else {
			// removes striketrough when newline is encountered.
			if (isStriked == 1 && c == '\n') {
				printf("\x1b[0m%c", c);
				isStriked = 0;
			}
			else if (isProject == 1 && (c == ' ' || c == '\n')) {
				printf("\x1b[0m%c", c);
				isProject = 0;
			}
			// sets to 0 isPriority at newline.
			//else if (isPriority == 1 && c == '\n') {
			//	isPriority = 0;
			//}
			//else if (isContext == 1 && c == '\n') {
			//	isContext = 0;
			//}
			else if (isStriked == 0 && prec == ' ' && c == '+') {
				printf("\x1b[0;32m%c", c);
				isProject = 1;
			}
			else if (isStriked == 0 && prec == ' ' && c == '@') {
				printf("\x1b[0;33m%c", c);
				//isContext = 1;
			}
			else if ((prec2 == '\n' || SOF == 1) && prec == '(') {
				for (int i = 0; i < 26; ++i)
					if (alphabet[i] == 'Z') {
						printf("\x1b[1;31m%c\x1b[0m", c);
						//isPriority = 1;
					}
			}
			else {
				//putc(c, output);
			}
		}
		//printf("\nprec2 = %c\nprec = %c\nc = %c\n", prec2, prec, c);
		prec2 = prec;
		prec = c;
		--SOF;
	} */
	return parsedLines;
}

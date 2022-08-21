#include <stdio.h>
//#include "parser.c"

int main(int argc, char ** argv) {
	char * filename = {0};
	FILE * fp;
	switch (argc) {
		case 1:
			printf("No argument passed, assuming you want to create a new todo.txt file.\n");
			break;
		case 2:
			filename = argv[1];
			if ((fp = fopen(filename, "rw")) == NULL) {
				fprintf(stderr, "%s does not exist or is not readable/writable.\n", filename);
				return 1;
			}
			printf("\x1b[3mFilename: \x1b[32m%s\x1b[m\n", argv[1]);
			parseFile(fp);
			fclose(fp);
			break;
		default:
			fprintf(stderr, "Only one file can be passed as an argument.\nIf there are spaces in the filename, put apostrophes around it.\n");
			return 1;
	}

	putc('\n', stdout);
}

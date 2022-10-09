#include <stdio.h>

void save(FILE * file, char * buffer) {
	fwrite(buffer, sizeof(char), strlen(buffer), file);
}

char * cliEdit(FILE * file) {
	char * text = "Buffer poggggg!";
	return text;
}

/*
stream_splice.c
05/25/2016

Takes in one file as standard input (text file) and one word as a command 
line argument. Removes all occurences of the word from the text file and 
outputs the remaining text file.

Stephanie Goodale
V00832053
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

//read a line from a file
int read_line(FILE* f, char buffer[], int buffer_size){
	int i = 0;
	int c = fgetc(f);
	while( (c != EOF) && (c != '\n') && (i < buffer_size-1) ){
		buffer[i] = c;
		i++;
		c = fgetc(f);
	}
	int count = i;
	if (c == '\n')
		count++;
	buffer[i] = '\0';
	return count;
}

int main(int argc, char *argv[]) {
	
	//verify the command line only has one argument
	if (argv[1] == NULL || argv[2] != NULL) {
		printf("Usage: ./stream_search <word list file>\n");
		return 0;
	}
	
	char *word = argv[1];
	FILE *text = stdin;
	
	//create empty line to fill
	//https://www.experts-exchange.com/questions/21822619/How-do-I-remove-a-substring-from-a-string-in-C.html
	char line[1002];
	char *strToRemove = word;
	char *strLocation;
	char strAfter[1002];	
	//while the text file has more lines to read, do..
	while (read_line(text, line, 1002) > 0 ) {
		
		char *strBefore = line;

		strcpy(strAfter, strBefore);
		strLocation = strstr(strAfter, strToRemove);

		while (strLocation != NULL) {
			strcpy(strLocation, strLocation + strlen(strToRemove));
			strLocation = strstr(strAfter, strToRemove);
		}
		//print remaining string
		printf("%s\n", strAfter);
		//reset line
		memset(line, 0, 1002);
	}
	fclose(text);
	return 0;
}

		




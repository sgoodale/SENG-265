/*
stream_search.c
05/25/2016

Takes in two files; one as a command line argument (word list), the other 
as standard input (text file). Outputs all lines of the text file that 
contains words from the word list.

Stephanie Goodale
V00832053
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//check if one string is found in another
int strings_equal(char line[], char word[], int index){
	
	int wordlen = strlen(word);
	int i;
	for(i = 0; i < wordlen; i++) {
		if (line[i+index] != word[i])
			return 0;
	}
	return 5;
}

//remove spaces from inputed word
//http://stackoverflow.com/questions/1726302/removing-spaces-from-a-string-in-c 
void remove_spaces(char* word) {
	char* i = word;
	char* j = word;
	while(*j != 0) {
		*i = *j++;
		if(isspace(*i) == 0) {
			i++;
		}
	}
	*i = 0;
}

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

	//open files and make sure they are readable
	FILE *wordlist = fopen(argv[1], "r");
	FILE *text = stdin;
	
	if (wordlist == NULL){
		printf("Error: Unable to open word list\n");
		return 0; 
	}
	fclose(wordlist);

	//create empty line to fill
	char line[1002];
	//while the text file has more lines to read, do..	
	while (read_line(text, line, 1002) > 0 ) {
		
		//printf("%s\n", line);
		
		//open wordfile, create empty word to fill
		wordlist = fopen(argv[1], "r");
		char word[102];
		int flag = 0;
		while (read_line(wordlist, word, 102) > 0) {
		
			//printf("%s\n", word);

			remove_spaces(word);
			if (word[0] != '\0') {
				int k;
				for (k = 0; k < 1002; k++) {
					//if strings are equal, break loop and move to next word 	
					if (strings_equal(line, word, k) == 5) {
						printf("%s\n", line);
						flag = 1;
						break;
					}
				}
			}
			//reset word
			memset(word, 0, 102);
			if (flag == 1) {
				break;
			}
		}
		//reset line
		memset(line, 0, 1002);
		fclose(wordlist);	
	}
	//done; close files
	fclose(text);
	return 0;
}



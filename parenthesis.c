#include<stdio.h>
#include<stdlib.h>
#define ARRAY_SIZE 200

int top = -1, lines[ARRAY_SIZE], lineStack[ARRAY_SIZE];
char chars[ARRAY_SIZE], charStack[ARRAY_SIZE];

int arePair(char openingChar, char closingChar) {
    if (openingChar == '(' && closingChar == ')') return 1;
    else if (openingChar == '<' && closingChar == '>') return 1;
    else if (openingChar == '{' && closingChar == '}') return 1;
    else if (openingChar == '[' && closingChar == ']') return 1;
	
	return 0;
}

int push(char charElement, int lineElement) {
	top += 1;
	charStack[top] = charElement;
	lineStack[top] = lineElement;
}

int pop() {
	charStack[top] = 'N';
	top -= 1;
}

int main(int argc, char *argv[]) {
	int curChar, i, line = 1, mistakes = 0;
	FILE *file;

	file = fopen(argv[1], "r");

	//checking if file have been added correctly
	if (file == NULL) exit(-1);

	//initializing the stack array
	for (i = 0; i < ARRAY_SIZE; i++) charStack[i] = 'N';

	i = 0;

	/*storing the given text file in an array after being cleared from needless characters*/
	while ((curChar = getc(file)) != EOF) {
		if (curChar == '(' || curChar == '<' || curChar == '{' || curChar == '[' || curChar == ')' || curChar == '>' || curChar == '}' || curChar == ']') {
			lines[i] = line;
			chars[i] = curChar;
		} else if (curChar == '\n') line++;

		i++;
	}

	i = 0;

	while (i < ARRAY_SIZE) {
		if (chars[i] == '(' || chars[i] == '<' || chars[i] == '{' || chars[i] == '[') push(chars[i], lines[i]);
		else if (chars[i] == ')' || chars[i] == '>' || chars[i] == '}' || chars[i] == ']') {
			if (arePair(charStack[top], chars[i]) == 1) pop();
			else if (arePair(charStack[top], chars[i]) == 0 && (charStack[top] == '(' || charStack[top] == '<' || charStack[top] == '{' || charStack[top] == '[')) {
                printf("Mismatch: Open %c in line %d closes with %c in line %d.\n", charStack[top], lineStack[top], chars[i], lines[i]);
				mistakes++;
				pop();
            } else if (arePair(charStack[top], chars[i]) == 0 && (chars[i] == ')' || chars[i] == '>' || chars[i] == '}' || chars[i] == ']')) {
                printf("Mismatch: Closing %c in line %d has not opened.\n", chars[i], lines[i]);
                mistakes++;
            }
        }

		i++;
	}

	i = 0;

	while (charStack[i] != 'N') {
		mistakes++;
		printf("Mismatch: Open %c in line %d has not closed.\n", charStack[i], lineStack[top]);
		i++;
	}

	if (mistakes == 0) printf("OK\n");
}
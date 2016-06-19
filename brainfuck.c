#include <stdio.h>
#include <stdlib.h>

char* tape;
int tapeSize;
int tapePos = 0;

char* code;
int codeSize;
int codePos = 0;

int run(int skip) {
	while (codePos < codeSize) {
		if (tapePos >= tapeSize) {
			printf("Tape full!\n");
			exit(1);
		}

		if (code[codePos] == '[') {
			++codePos;
			int oldPos = codePos;
			while (run(tape[tapePos] == '\0'))
				codePos = oldPos;
		} else if (code[codePos] == ']') {
			return tape[tapePos] != '\0';
		} else if (!skip) {
			switch (code[codePos]) {
			case '+':
				++tape[tapePos];
				break;

			case '-':
				--tape[tapePos];
				break;

			case '>':
				++tapePos;
				break;

			case '<':
				--tapePos;
				break;

			case '.':
				printf("%c", tape[tapePos]);
				break;

			case ',':
				scanf("%c", &tape[tapePos]);
				break;
			}
		}

		++codePos;
	}

	return 0;
}

void load_file(char const* path) {
	FILE* f = fopen(path, "rb");

	if (f) {
		fseek(f, 0, SEEK_END);
		codeSize = ftell(f);
		fseek(f, 0, SEEK_SET);
		if (!(code = malloc((codeSize+1) * sizeof(char)))) {
			printf("malloc failed\n");
			exit(1);
		}

		fread(code, sizeof(char), codeSize, f);
		fclose(f);
	}

	code[codeSize+1] = '\0';
}


int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("usage: %s <tapeSize> <brainfuckFile>\n", argv[0]);
		return 1;
	}

	tapeSize = atoi(argv[1]);

	if(!(tape = calloc(tapeSize, sizeof(char)))) {
		printf("calloc failed\n");
		exit(1);
	}

	load_file(argv[2]);

	run(0);
}
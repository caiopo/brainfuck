// C++11

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

auto tape = std::vector<char>();
unsigned int codePos = 0;
unsigned int tapePos = 0;

std::string code;

bool run(bool skip = false) {
	while (codePos < code.size()) {
		if (tapePos >= tape.size())
			tape.push_back('\0');

		if (code[codePos] == '[') {
			++codePos;
			auto oldPos = codePos;
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
            	std::cout << tape[tapePos];
            	break;

            case ',':
            	std::cin >> tape[tapePos];
            	break;
			}
		}

		++codePos;
	}

	return false;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::ifstream t(argv[1]);
		code = std::string((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
	} else {
		std::cout << "error: reading code from stdin not implemented yet" << std::endl;
		return 1;
	}

	run();
}
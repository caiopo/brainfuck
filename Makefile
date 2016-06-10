nim:
	nim c -d:release brainfuck.nim

cpp:
	g++ brainfuck.cpp -o brainfuck -std=c++11 -Wall -pedantic -Wextra

go:
	go build brainfuck.go
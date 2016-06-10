nim:
	nim c -d:release brainfuck.nim

cpp:
	g++ brainfuck.cpp -o brainfuck -std=c++11 -Wall -pedantic -Wextra -O3

go:
	go build brainfuck.go

java:
	javac brainfuck.java

clean:
	rm brainfuck{,.class}
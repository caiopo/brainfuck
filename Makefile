nim:
	nim c -d:release brainfuck.nim

nimcompiler:
	nim c -d:release brainfuck_compiler.nim

c:
	gcc brainfuck.c -o brainfuck -Wall -pedantic -Wextra -O3

cpp:
	g++ brainfuck.cpp -o brainfuck -std=c++11 -Wall -pedantic -Wextra -O3

go:
	go build brainfuck.go

java:
	javac brainfuck.java

rust:
	rustc brainfuck.rs

clean:
	rm brainfuck{,.class,_compiler}
package main

import (
	"fmt"
	"os"
	"bufio"
	"io/ioutil"
)

var (
	code    string
	tape    []uint8
	tapePos int
	codePos int
	reader *bufio.Reader
)

func init() {
	reader = bufio.NewReader(os.Stdin)

	if len(os.Args) > 1 {
		bs, err := ioutil.ReadFile(os.Args[1])

		if err != nil {
			fmt.Println("error while reading the code from a file")
			os.Exit(1)
		}

		code = string(bs)
	} else {
		bs, err := ioutil.ReadAll(os.Stdin)

		if err != nil {
			fmt.Println("error while reading the code from stdin")
			os.Exit(1)
		}

		code = string(bs)
	}
}


func main() {
	run(false)
}


func run(skip bool) bool {
	for tapePos >= 0 && codePos < len(code) {
		if tapePos >= len(tape) {
			tape = append(tape, 0)
		}

		if code[codePos] == '[' {
			codePos++
			oldPos := codePos
			for run(tape[tapePos] == 0) {
				codePos = oldPos
			}
		} else if code[codePos] == ']' {
			return tape[tapePos] != 0

		} else if !skip {
			switch code[codePos] {
			case '+':
				tape[tapePos]++
			case '-':
				tape[tapePos]--
			case '>':
				tapePos++
			case '<':
				tapePos--
			case '.':
				fmt.Print(string(tape[tapePos]))
			case ',':

			}

		}

		codePos++
	}

	return false

}

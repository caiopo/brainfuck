import os

{.push overflowchecks: off.}
proc xinc(c: var char) = inc c
proc xdec(c: var char) = dec c
{.pop.}

let code = if paramCount() > 0: readFile paramStr 1
           else: readAll stdin

var
    tape = newSeq[char]()
    codePos = 0
    tapePos = 0

proc run(skip = false): bool =
    while tapePos >= 0 and codePos < len code:
        if tapePos >= len tape:
            tape.add '\0'

        if code[codePos] == '[':
            inc codePos
            let oldPos = codePos
            while run tape[tapePos] == '\0':
                codePos = oldPos
        elif code[codePos] == ']':
            return tape[tapePos] != '\0'
        elif not skip:
            case code[codePos]
            of '+': xinc tape[tapePos]
            of '-': xdec tape[tapePos]
            of '>': inc tapePos
            of '<': dec tapePos
            of '.': write stdout, tape[tapePos]
            of ',': tape[tapePos] = readChar stdin
            else: discard

        inc codePos

discard run()
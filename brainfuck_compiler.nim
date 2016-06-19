import macros

{.push overflowchecks: off.}
proc xinc(c: var char) = inc c
proc xdec(c: var char) = dec c
{.pop.}

proc compile(code: string): NimNode {.compiletime.} =
    var stmts = @[newStmtList()]

    template addStmt(text): stmt =
        stmts[stmts.high].add parseStmt(text)

    addStmt "var tape: array[1_000_000, char]"
    addStmt "var tapePos = 0"

    for c in code:
        case c
        of '+': addStmt "xinc tape[tapePos]"
        of '-': addStmt "xdec tape[tapePos]"
        of '>': addStmt "inc tapePos"
        of '<': addStmt "dec tapePos"
        of '.': addStmt "stdout.write tape[tapePos]"
        of ',': addStmt "tape[tapePos] = stdin.readChar"
        of '[': stmts.add newStmtList()
        of ']':
            var loop = newNimNode(nnkWhileStmt)
            loop.add parseExpr("tape[tapePos] != '\\0'")
            loop.add stmts.pop
            stmts[stmts.high].add loop
        else: discard

    result = stmts[0]

macro compileString*(code: string): stmt =
    compile code.strval

macro compileFile*(filename: string): stmt =
    compile staticRead(filename.strval)

proc mandelbrot = compileFile("tests/mandelbrot.b")

mandelbrot()
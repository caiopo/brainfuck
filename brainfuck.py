from sys import stdin, argv

def inc(n):
	return (n+1) % 256

def dec(n):
	return 255 if n-1 < 0 else n-1

tape = []
code_pos = 0
tape_pos = 0

def run(skip=False):
	global tape_pos, code_pos, code, tape

	while tape_pos >= 0 and code_pos < len(code):
		if tape_pos >= len(tape):
			tape.append(0)

		if code[code_pos] == '[':
			code_pos += 1
			old_pos = code_pos
			while run(tape[tape_pos] == 0):
				code_pos = old_pos
		elif code[code_pos] == ']':
			return tape[tape_pos] != 0
		elif not skip:
			if code[code_pos] == '+':
				tape[tape_pos] = inc(tape[tape_pos])

			elif code[code_pos] == '-':
				tape[tape_pos] = dec(tape[tape_pos])

			elif code[code_pos] == '>':
				tape_pos += 1

			elif code[code_pos] == '<':
				tape_pos -= 1

			elif code[code_pos] == '.':
				print(chr(tape[tape_pos]), end='')

			elif code[code_pos] == ',':
				tape[tape_pos] = ord(stdin.read(1))

		code_pos += 1

	return False

if __name__ == '__main__':
	if len(argv) > 1:
		with open(argv[1]) as bfile:
			code = bfile.read()
	else:
		code = stdin.read()

	run()

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

public class brainfuck {

	static int codePos = 0, tapePos = 0;

	static ArrayList<Character> tape = new ArrayList<Character>(300);

	static String code;

	public static void main(String[] args) {
		if (args.length > 0) {

			byte[] bytes = null;

			try {
				bytes = Files.readAllBytes(Paths.get(args[0]));
			} catch (IOException e) {
				e.printStackTrace();
			}
			code = new String(bytes, StandardCharsets.UTF_8);
		} else {
			System.out.println("error: reading code from stdin not implemented yet");
			System.exit(1);
		}

		run(false);
	}

	public static boolean run(boolean skip) {
		while (codePos < code.length()) {
			if (tapePos >= tape.size())
				tape.add('\0');

			if (code.charAt(codePos) == '[') {
				++codePos;
				int oldPos = codePos;
				while (run(tape.get(tapePos) == '\0'))
					codePos = oldPos;
			} else if (code.charAt(codePos) == ']') {
				return tape.get(tapePos) != '\0';
			} else if (!skip) {
				switch (code.charAt(codePos)) {
				case '+':
					tape.set(tapePos, (char) (tape.get(tapePos) + 1));
					break;

				case '-':
					tape.set(tapePos, (char) (tape.get(tapePos) - 1));
					break;

				case '>':
					++tapePos;
					break;

				case '<':
					--tapePos;
					break;

				case '.':
					System.out.print(tape.get(tapePos));
					break;

				case ',':
					try {
						tape.set(tapePos, (char) System.in.read());
					} catch (IOException e) {
						e.printStackTrace();
					}
					break;
				}
			}

			++codePos;
		}

		return false;

	}
}

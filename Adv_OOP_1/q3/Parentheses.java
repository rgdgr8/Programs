import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class Parentheses {

 private static class Bracket {
    char type;
    int position;

    Bracket(char type, int position) {
        this.type = type;
        this.position = position;
    }

    boolean Match(char c) {
        if (this.type == '[' && c == ']')
            return true;
        if (this.type == '{' && c == '}')
            return true;
        if (this.type == '(' && c == ')')
            return true;
        return false;
    }
 }

    public static void main(String[] args) throws IOException {
        InputStreamReader input_stream = new InputStreamReader(System.in);
        BufferedReader reader = new BufferedReader(input_stream);
        String text = reader.readLine();

        Stack<Bracket> opening_brackets_stack = new Stack<Bracket>();
        for (int position = 0; position < text.length(); ++position) {
            char next = text.charAt(position);
            Bracket bracket = new Bracket(next, position);

            if (!(next == '(' || next == '[' || next == '{' || next == ')' || next == ']' || next == '}')){//if not a bracket
                continue;
            }

            if (next == '(' || next == '[' || next == '{') {//if opening bracket
                opening_brackets_stack.push(bracket);
            } else {
                if (opening_brackets_stack.empty()){//if closing bracket without opening bracket
                    System.out.println((position+1));
                    return;
                }
                Bracket bracketcheck = opening_brackets_stack.pop();
                if (bracketcheck==null || !bracketcheck.Match(bracket.type)){//if closing bracket mismatched with opening bracket
                    System.out.println((position+1));
                    return;
                }
            }
        }

        if (opening_brackets_stack.empty()){//if all brackets matched
            System.out.println("No errors");
        }else {//at least 1 bracket left unpaired/unmatched
            System.out.println((opening_brackets_stack.peek().position+1));
        }
    }
}

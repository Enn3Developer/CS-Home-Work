import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;
import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {
        public static void main(String[] args) {
            String msg = args[0];
            char[] key = args[1].toCharArray();

            String crypted = transpose(msg, key);

            System.out.println(crypted);
            System.out.println(detranspose(crypted, key));
        }

        private static String transpose(String msg, char[] key) {
            int cols = key.length;
            int rows = msg.length() / cols;
            char[][] matrix = new char[cols][rows];

            CharacterIterator iter = new CharacterIterator(msg);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[j][i] = iter.hasNext() ? iter.next() : '\0';
                }
            }

            List<String> parts = new ArrayList<>();

            for (int i = 0; i < cols; i++) {
                StringBuilder strBuilder = new StringBuilder();

                strBuilder.append(key[i]);
                strBuilder.append(matrix[i]);

                parts.add(strBuilder.toString());
            }

            Collections.sort(parts);
            return parts.stream().map((String part) -> part.substring(1)).collect(Collectors.joining(""));
        }

        // Sinceramente non so manco io perché il codice sia così spaghetti
        // l'ho fatto in 10 minuti, non ho voglia di riscriverlo quindi lo
        // lascio così
        private static String detranspose(String msg, char[] key) {
            int cols = key.length;
            int rows = msg.length() / cols;
            char[][] matrix = new char[cols][rows];

            CharacterIterator iter = new CharacterIterator(msg);

            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    matrix[i][j] = iter.hasNext() ? iter.next() : '\0';
                }
            }

            List<String> parts = new ArrayList<>();
            List<Character> keyList = IntStream.range(0, key.length).mapToObj(i -> key[i]).collect(Collectors.toList());
            List<Character> sortedKey = IntStream.range(0, key.length).mapToObj(i -> key[i]).collect(Collectors.toList());
            Collections.sort(sortedKey);

            for (int i = 0; i < cols; i++) {
                StringBuilder strBuilder = new StringBuilder();

                strBuilder.append(sortedKey.get(i));
                strBuilder.append(matrix[i]);

                parts.add(strBuilder.toString());
            }

            String[] desortedParts = new String[parts.size()];

            parts.parallelStream().forEach((String part) -> {
               desortedParts[keyList.indexOf(part.charAt(0))] = part.substring(1);
            });

            StringBuilder strBuilder = new StringBuilder();

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    strBuilder.append(desortedParts[j].charAt(i));
                }
            }

            return strBuilder.toString();
        }
}

class CharacterIterator implements Iterator<Character> {
    private final String str;
    private int pos = 0;

    public CharacterIterator(String str) {
        this.str = str;
    }

    public boolean hasNext() {
        return pos < str.length();
    }

    public Character next() {
        return str.charAt(pos++);
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }
}

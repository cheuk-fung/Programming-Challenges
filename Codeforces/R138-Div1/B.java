import java.util.Scanner;

public class B {
    public static void main(String[] args)
    {
        new B().run();
    }
    
    void run()
    {
        Scanner cin = new Scanner(System.in);
        String s = cin.next();
        String t = cin.next();
        int[] prefix = getPrefix(s, t);
        int[] suffix = getPrefix(new StringBuffer(s).reverse().toString(), new StringBuffer(t).reverse().toString());
        for (int i = 0; i < s.length(); i++) {
            if (prefix[i] + suffix[s.length() - 1 - i] <= t.length()) {
                System.out.println("No");
                return ;
            }
        }
        System.out.println("Yes");
    }

    private int[] getPrefix(String s, String t) {
        int[] result = new int[s.length()];
        int[][] last = new int[26][t.length() + 1];
        for (int i = 0; i < 26; i++) {
            int pos = -1;
            for (int j = 0; j < t.length(); j++) {
                if (t.charAt(j) == (char)(i + 'a')) {
                    pos = j + 1;
                }
                last[i][j + 1] = pos;
            }
        }
        int index = 0;
        for (int i = 0; i < s.length(); i++) {
            if (index < t.length() && s.charAt(i) == t.charAt(index)) {
                index++;
            }
            result[i] = last[s.charAt(i) - 'a'][index]; 
        }
        return result;
    }
}

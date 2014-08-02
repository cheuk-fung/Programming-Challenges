import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

class Solution {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int k = cin.nextInt();
        int n = cin.nextInt();

        ArrayList<String> phone = new ArrayList<String>();
        for (int i = 0; i < n; i++) {
            phone.add(cin.next());
        }
        Collections.sort(phone);

        int pages = 3, cnt = 1;
        for (int i = 1; i < n; i++) {
            if (phone.get(i).charAt(0) != phone.get(i - 1).charAt(0) || cnt == k) {
                pages++;
                cnt = 1;
            } else {
                cnt++;
            }
        }

        System.out.println(pages);
    }
}

/*
 *  SRC: HDOJ ACM Steps
 * PROB: Identity Card
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: jdk 6
 *
 * Created by Leewings Ac
 */

import java.util.*;

class Main {
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int tasks = cin.nextInt();
        while (tasks-- > 0) {
            String id = cin.next(),
                   from = "";
            if (id.substring(0, 2).equals("33")) from = "Zhejiang";
            if (id.substring(0, 2).equals("11")) from = "Beijing";
            if (id.substring(0, 2).equals("71")) from = "Taiwan";
            if (id.substring(0, 2).equals("81")) from = "Hong Kong";
            if (id.substring(0, 2).equals("82")) from = "Macao";
            if (id.substring(0, 2).equals("54")) from = "Tibet";
            if (id.substring(0, 2).equals("21")) from = "Liaoning";
            if (id.substring(0, 2).equals("31")) from = "Shanghai";
            System.out.println("He/She is from " +
                               from +
                               ",and his/her birthday is on " +
                               id.substring(10, 12) + "," +
                               id.substring(12, 14) + "," +
                               id.substring(6, 10) +
                               " based on the table.");
        }
    }
}

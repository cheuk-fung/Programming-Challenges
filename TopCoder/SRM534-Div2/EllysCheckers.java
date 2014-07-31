import java.util.*;
import java.math.*;

public class EllysCheckers {
    public String getWinner(String board)
    {
        int cnt = 0;
        for (int i = 0; i < board.length(); i++)
            if (board.charAt(i) == 'o')
                cnt += board.length() - i - 1;
        return cnt % 2 == 1 ? "YES" : "NO";
    }
}

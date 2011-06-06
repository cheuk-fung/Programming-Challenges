import java.util.*;

class Main
{
    private static int l, n, m;
    private static int[] pos;

    private static boolean check(int min)
    {
        Stack<Integer> pre = new Stack<Integer>();
        pre.push(0);
        int sum = 0;
        for (int i = 1; i < n - 1; i++) {
            if (pos[i] - pos[pre.peek()] < min) sum++;
            else pre.push(i);
        }
        while (pos[n - 1] - pos[pre.peek()] < min) {
            sum++;
            pre.pop();
        }

        int nowMin= 0x7fffffff;
        int r = n - 1;
        while (pre.empty() == false) {
            int l = pre.pop();
            if (pos[r] - pos[l] < nowMin)
                nowMin = pos[r] - pos[l];
            r = l;
        }
          
        if (sum > m) return false;
        if (sum == m) {
            if (nowMin >= min) return true;
            return false;
        }

        return true;
    }

    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        l = cin.nextInt();
        n = cin.nextInt();
        m = cin.nextInt();

        pos = new int[n + 2];
        pos[0] = 0;
        for (int i = 1; i <= n; i++)
            pos[i] = cin.nextInt();
        pos[n + 1] = l;
        n += 2;

        Arrays.sort(pos);

        int low = 0, high = l;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (check(mid) == true) low = mid;
            else high = mid - 1;
        }

        System.out.println(low);
    }
}

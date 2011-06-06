import java.util.*;

class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        int t = cin.nextInt();
        while (t-- > 0) new Prob().solve(cin);
    }
}

class Prob
{
    int m, k;
    long[] books;

    public boolean check(long max)
    {
        int sum = 0;
        long tot = 0;
        for (int i =  m - 1; i >= 0; i--) {
            tot += books[i];
            if (tot > max) {
                sum++;
                tot = books[i];
            }
        }
        sum++;
        if (sum > k) return true;
        return false;
    }

    public void solve(Scanner cin)
    {
        m = cin.nextInt();
        k = cin.nextInt();

        books = new long[m];
        long low = 0, high = 0;
        for (int i = 0; i < m; i++) {
            books[i] = cin.nextLong();
            high += books[i];
            if (books[i] > low) low = books[i];
        }

        while (low < high) {
            long mid = (low + high - 1) / 2;
            if (check(mid) == true) low = mid + 1;
            else high = mid;
        }

        long tot = 0;
        Stack<Integer> pos = new Stack<Integer>();
        for (int i = m - 1; i >= 0; i--) {
            tot += books[i];
            if (tot > low) {
                tot = books[i];
                pos.push(i + 1);
            }
        }
        if (pos.size() != k - 1) {
            while (pos.empty() == false && pos.peek() <= k - 1 - pos.size()) pos.pop();
            for (int i = k - 1 - pos.size(); i >= 1; i--)
                pos.push(i);
        }
        
        int l = 0, r;
        while (pos.empty() == false) {
            r = pos.pop();
            for (int j = l; j < r; j++)
                System.out.print(books[j] + " ");
            System.out.print("/ ");
            l = r;
        }
        for (int i = l; i < m - 1; i++)
            System.out.print(books[i] + " ");
        System.out.println(books[m - 1]);
    }
}

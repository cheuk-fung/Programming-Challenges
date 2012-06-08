public class StrIIRec {
    private int count(String s, int n, boolean[] vis)
    {
        int cnt = 0;
        for (int c = 'a'; c < 'a' + n; c++) {
            if (vis[c]) continue;

            for (int d = 'a'; d < c; d++) {
                if (!vis[d]) cnt++;
            }
        }

        return cnt;
    }

    public String recovstr(int n, int minInv, String minStr)
    {
        if (minInv > n * (n - 1) / 2) return "";

        String r = "";
        boolean[] vis = new boolean[256];
        int totCnt = 0;
        for (int i = 0; i < n; i++) {
            for (int c = 'a'; c < 'a' + n; c++) {
                if (vis[c]) continue;

                vis[c] = true;
                int tmpCnt = 0;
                for (int d = 'a'; d < c; d++) {
                    if (!vis[d]) tmpCnt++;
                }
                totCnt += tmpCnt;

                String t = r + (char)c;
                if (totCnt + count(t, n, vis) >= minInv && t.compareTo(minStr.substring(0, Math.min(i + 1, minStr.length()))) >= 0) {
                    r = t;
                    break;
                } else {
                    vis[c] = false;
                    totCnt -= tmpCnt;
                }
            }
        }

        return r;
    }
}

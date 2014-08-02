/*
 *  SRC: HDOJ 3699
 * PROB: A hard Aoshu Problem 
 * ALGO: Enum
 * DATE: Oct 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

char left[20], right[20], ans[20];
int l_len, r_len, a_len;
int table[256], hash[256], vis[256], alp_cnt;
int ans_cnt;

int str_to_num(char *s)
{
    int res = 0;
    while (*s) res = res * 10 + table[*s++];
    return res;
}

void search(int alp)
{
    if (alp == alp_cnt) {
        if (table[left[0]]  == 0 && l_len != 1) return ;
        if (table[right[0]] == 0 && r_len != 1) return ;
        if (table[ans[0]]   == 0 && a_len != 1) return ;

        int l_num = str_to_num(left),
            r_num = str_to_num(right),
            a_num = str_to_num(ans);

        if (l_num + r_num == a_num) ans_cnt++;
        if (l_num - r_num == a_num) ans_cnt++;
        if (l_num * r_num == a_num) ans_cnt++;
        if (r_num)
            if (l_num == a_num * r_num) ans_cnt++;

        return ;
    }
    
    for (int i = 0; i < 10; i++)
        if (!vis[i]) {
            vis[i] = 1;
            table[hash[alp]] = i;
            search(alp + 1);
            vis[i] = 0;
        }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s%s", left, right, ans);
        l_len = strlen(left);
        r_len = strlen(right);
        a_len = strlen(ans);
        ans_cnt = 0;
        alp_cnt = 0;
        memset(hash, 0, sizeof(hash));
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < l_len; i++)
            if (!vis[left[i]]) {
                hash[alp_cnt++] = left[i];
                vis[left[i]] = 1;
            }
        for (int i = 0; i < r_len; i++)
            if (!vis[right[i]]) {
                hash[alp_cnt++] = right[i];
                vis[right[i]] = 1;
            }
        for (int i = 0; i < a_len; i++)
            if (!vis[ans[i]]) {
                hash[alp_cnt++] = ans[i];
                vis[ans[i]] = 1;
            }

        search(0);

        printf("%d\n", ans_cnt);
    }

    return 0;
}

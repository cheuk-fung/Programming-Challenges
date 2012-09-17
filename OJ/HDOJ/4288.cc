/*
 *  SRC: HDOJ 4288
 * PROB: Coder
 * ALGO: Segment tree
 * DATE: Sep 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;

int elements[MAXN];

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int size;
            long long sum[5];
        } node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(node, 0, sizeof node);
        }

        long long query()
        {
            return node[1].sum[2];
        }

        void update(int position, int v, int a = lep, int b = rep, int index = 1)
        {
            if (a + 1 == b) {
                if (v) {
                    node[index].size = 1;
                    node[index].sum[(position - a) % 5] += elements[position];
                } else {
                    node[index].size = 0;
                    node[index].sum[(position - a) % 5] -= elements[position];
                }
                return ;
            }

            int mid = (a + b) >> 1;
            if (position < mid) update(position, v, a, mid, LC(index));
            else update(position, v, mid ,b, RC(index));

            node[index].size = node[LC(index)].size + node[RC(index)].size;
            memcpy(node[index].sum, node[LC(index)].sum, sizeof node[index].sum);
            int offset = node[LC(index)].size % 5;
            for (int i = 0; i < 5; i++) {
                node[index].sum[(i + offset) % 5] += node[RC(index)].sum[i];
            }
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Instruction {
    int type;
    int element;
} ins[MAXN];

char strbuf[100];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        int element_cnt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);
            if (strbuf[0] == 's') {
                ins[i].type = 2;
            } else {
                ins[i].type = strbuf[0] == 'a';
                scanf("%d", &ins[i].element);
                elements[element_cnt++] = ins[i].element;
            }
        }
        sort(elements, elements + element_cnt);
        element_cnt = unique(elements, elements + element_cnt) - elements;

        st.build(0, element_cnt);
        for (int i = 0; i < n; i++) {
            if (ins[i].type == 2) {
                printf("%I64d\n", st.query());
            } else {
                int position = lower_bound(elements, elements + element_cnt, ins[i].element) - elements;
                st.update(position, ins[i].type);
            }
        }
    }

    return 0;
}


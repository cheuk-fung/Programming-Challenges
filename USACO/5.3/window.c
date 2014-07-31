/*
ID: os.idea1
LANG: C
TASK: window
*/
#include <stdio.h>

#define MAX_SIZE 1000

FILE *fin, *fout;

struct Point {
    int x, y;
};

struct Lnode {
    int pos;

    char id;
    struct Point a, b;
    struct Lnode *prev, *next;
} link[MAX_SIZE];
struct Lnode *head, *tail;
int link_cnt;
int pos[256];

struct Rectangle {
    struct Point a, b;
    int del;
} rec[MAX_SIZE];
int rec_cnt;

inline int area(struct Point a, struct Point b)
{
    return (b.x - a.x) * (b.y - a.y);
}

inline void rec_insert(struct Point a, struct Point b)
{
    rec[rec_cnt].a = a;
    rec[rec_cnt].b = b;
    rec[rec_cnt].del = 0;
    rec_cnt++;
}

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void create(char *s)
{
    struct Lnode *ptr = &link[link_cnt++];
    ptr->id = s[2];
    pos[s[2]] = ptr->pos;

    sscanf(s + 4, "%d%*c%d%*c%d%*c%d",
           &ptr->a.x, &ptr->a.y, &ptr->b.x, &ptr->b.y);
    if (ptr->a.x > ptr->b.x) swap(&ptr->a.x, &ptr->b.x);
    if (ptr->a.y > ptr->b.y) swap(&ptr->a.y, &ptr->b.y);

    ptr->next = head;
    if (head) head->prev = ptr;
    else tail = ptr;
    head = ptr;
}

void destory(char id)
{
    struct Lnode *ptr = &link[pos[id]];
    if (ptr == head) {
        head = ptr->next;
        if (head) head->prev = 0;
        return ;
    }

    if (ptr == tail) {
        tail = ptr->prev;
        if (tail) tail->next = 0;
        return ;
    }

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
}

void to_top(char id)
{
    struct Lnode *ptr = &link[pos[id]];
    if (ptr == head) return ;

    destory(id);
    ptr->next = head;
    ptr->prev = 0;
    head->prev = ptr;
    head = ptr;
}

void to_bottom(char id)
{
    struct Lnode *ptr = &link[pos[id]];
    if (ptr == tail) return ;

    destory(id);
    ptr->prev = tail;
    ptr->next = 0;
    tail->next = ptr;
    tail = ptr;
}

void show(char id)
{
    rec_cnt = 0;

    rec_insert(link[pos[id]].a, link[pos[id]].b);

    struct Lnode *ptr = head;
    while (ptr->id != id) {
        int i;
        for (i = 0; i < rec_cnt; i++)
            if (!rec[i].del) {
                if (rec[i].a.x >= ptr->b.x || rec[i].b.x <= ptr->a.x) continue;
                if (rec[i].a.y >= ptr->b.y || rec[i].b.y <= ptr->a.y) continue;

                int x1 = max(rec[i].a.x, ptr->a.x),
                    x2 = min(rec[i].b.x, ptr->b.x);
                if (rec[i].a.x < x1)
                    rec_insert(rec[i].a, (struct Point){x1, rec[i].b.y});
                if (rec[i].b.x > x2)
                    rec_insert((struct Point){x2, rec[i].a.y}, rec[i].b);

                int y1 = max(rec[i].a.y, ptr->a.y),
                    y2 = min(rec[i].b.y, ptr->b.y);
                if (rec[i].a.y < y1)
                    rec_insert((struct Point){x1, rec[i].a.y}, \
                               (struct Point){x2, y1});
                if (rec[i].b.y > y2)
                    rec_insert((struct Point){x1, y2}, \
                               (struct Point){x2, rec[i].b.y});

                rec[i].del = 1;
            }

        ptr = ptr->next;
    }

    int area_sum = area(rec[0].a, rec[0].b), area_rest = 0;
    int i;
    for (i = 0; i < rec_cnt; i++)
        if (!rec[i].del) area_rest += area(rec[i].a, rec[i].b);

    fprintf(fout, "%.3f\n", (double)area_rest / area_sum * 100);
}

int main()
{
    int i;
    for (i = 0; i < MAX_SIZE; i++) link[i].pos = i;

    fin = fopen("window.in", "r");
    fout = fopen("window.out", "w");

    char str[50];
    while (fscanf(fin, "%s", str) != EOF) {
        switch (str[0]) {
            case 'w': create(str);       break;
            case 't': to_top(str[2]);    break;
            case 'b': to_bottom(str[2]); break;
            case 'd': destory(str[2]);   break;
            case 's': show(str[2]);
        }
    }

    return 0;
}

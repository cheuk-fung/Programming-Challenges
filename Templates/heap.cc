void adjust_heap(int *first, int *last, int curr)
{
    int size = last - first;
    while (curr < (size >> 1)) {
        int child = (curr << 1) + 1;
        if (child + 1 < size && *(first + child) < *(first + child + 1))
            child++;
        if (*(first + curr) < *(first + child))
            swap(first + curr, first + child);
        else break;

        curr = child; 
    }
}

void push_heap(int *first, int *last)
{
    int curr = last - 1 - first;
    while (curr) {
        int parent = (curr - 1) >> 1;
        if (*(first + parent) < *(first + curr))
            swap(first + curr, first + parent);
        else break;

        curr = parent;
    }
}

void pop_heap(int *first, int *last)
{
    swap(first, last - 1);
    adjust_heap(first, last - 1, 0);
}

void make_heap(int *first, int *last)
{
    int *curr = first;
    while (curr != last) push_heap(first, curr++ + 1);
}

void sort_heap(int *first, int *last)
{
    while (first != last) pop_heap(first, last--);
}

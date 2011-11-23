void merge_sort(int *a, int l, int r) // [l, r)
{
    if (l + 1 == r) return ;

    int mid = (l + r) / 2;
    merge_sort(a, l, mid);
    merge_sort(a, mid, r);

    int *b = new int[r - l];
    int p = l, q = mid, cnt = 0;
    while (p < mid && q < r) {
        if (a[p] < a[q]) b[cnt++] = a[p++];
        else b[cnt++] = a[q++];
    }
    while (p < mid) b[cnt++] = a[p++];
    while (q < r)   b[cnt++] = a[q++];

    for (int i = 0; i < cnt; i++) a[l + i] = b[i];

    delete[] b;
}

public void mergeSort(int l, int r)
{
    if (l + 1 == r) return ;

    int mid = (l + r) / 2;
    mergeSort(l, mid);
    mergeSort(mid, r);

    int size = 0;
    int[] b = new int[r - l];
    for (int i = l, j = mid; ; ) {
        if (a[i] < a[j]) b[size++] = a[i++];
        else b[size++] = a[j++];

        if (i == mid) {
            while (j < r) b[size++] = a[j++];
            break;
        }
        if (j == r) {
            while (i < mid) b[size++] = a[i++];
            break;
        }
    }
    for (int i = 0; i < size; i++) a[l + i] = b[i];
}

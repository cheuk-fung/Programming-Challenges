template<typename ForwardIterator>
void kmp_init(int* prn, ForwardIterator first, ForwardIterator last)
{
    prn[0] = 0;
    ForwardIterator curr = first + 1;
    for (int j = 0; curr != last; curr++) {
        while (j > 0 && *(first + j) != *curr) j = prn[j - 1];
        if (*(first + j) == *curr) j++;
        prn[curr - first] = j;
    }
}

template<typename ForwardIterator>
void kmp_init(vector<int> *prn, ForwardIterator first, ForwardIterator last)
{
    prn->clear();
    prn->push_back(0);
    ForwardIterator curr = first + 1;
    for (int j = 0; curr != last; curr++) {
        while (j > 0 && *(first + j) != *curr) j = (*prn)[j - 1];
        if (*(first + j) == *curr) j++;
        prn->push_back(j);
    }
}

template<typename ForwardIterator, typename Pattern>
int kmp(const Pattern &prn,                                                  \
        ForwardIterator first_a, ForwardIterator last_a,                     \
        ForwardIterator first_b, ForwardIterator last_b)
{
    int cnt = 0;
    ForwardIterator curr_a = first_a;
    for (int j = 0; curr_a != last_a; curr_a++) {
        while (j > 0 && *(first_b + j) != *curr_a) j = prn[j - 1];
        if (*(first_b + j) == *curr_a) j++;
        if (first_b + j == last_b) {
            cnt++;
            j = prn[j - 1];
        }
    }

    return cnt;
}

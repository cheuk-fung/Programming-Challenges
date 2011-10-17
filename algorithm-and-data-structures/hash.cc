unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str)
        hash = hash * seed + *str++;

    return (hash & 0x7FFFFFFF);
}

int ELFHash(char* key)
{
    unsigned int h = 0;
    while(*key) {
        h = (h << 4) + *key++;
        unsigned int g = h & 0xF0000000;
        if (g) h ^= g >> 24;
        h &= ~g;
    }
    return h % MOD;
}

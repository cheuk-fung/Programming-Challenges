class MagicCandy {
    private:

    public:
        int whichOne(int n)
        {
            int now = 2,
                sum = 1;
            while (sum + now <= n) {
                sum += now;
                now += 2;
            }
            if (sum + now / 2 <= n) sum += now / 2;
            return sum;
        }
};

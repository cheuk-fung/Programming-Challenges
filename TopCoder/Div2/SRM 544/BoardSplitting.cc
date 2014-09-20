class BoardSplitting {
    private:

    public:
        int minimumCuts(int desiredLength, int desiredCount, int actualLength)
        {
            int nowLength = 0;
            int cuts = 0;
            while (desiredCount--) {
                while (nowLength < desiredLength) nowLength += actualLength;
                nowLength -= desiredLength;
                if (nowLength) cuts++;
            }
            return cuts;
        }
};


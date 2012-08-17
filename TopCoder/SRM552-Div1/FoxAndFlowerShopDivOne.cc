#include <cmath>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

int L[31][31], P[31][31], S[31][31];
int LDiffRowU[31][901], LDiffRowD[31][901], LDiffColL[31][901], LDiffColR[31][901];
int LDiffRowURMQ[31][11][901], LDiffRowDRMQ[31][11][901], LDiffColLRMQ[31][11][901], LDiffColRRMQ[31][11][901];
int PDiffRowU[31][901], PDiffRowD[31][901], PDiffColL[31][901], PDiffColR[31][901];
int PDiffRowURMQ[31][11][901], PDiffRowDRMQ[31][11][901], PDiffColLRMQ[31][11][901], PDiffColRRMQ[31][11][901];

class FoxAndFlowerShopDivOne {
    private:
        int rect(int A[31][31], int x1, int y1, int x2, int y2)
        {
            return A[x2][y2] - A[x2][y1 - 1] - A[x1 - 1][y2] + A[x1 - 1][y1 - 1];
        }

        void RMQInit(int RMQ[11][901], int a[901], int n)
        {
            memcpy(RMQ[0], a, sizeof(int) * n);
            for (int i = 1; 1 << i <= n; i++) {
                for (int j = 0; j + (1 << i) <= n; j++) {
                    RMQ[i][j] = max(RMQ[i - 1][j], RMQ[i - 1][j + (1 << (i - 1))]);
                }
            }
        }

        int RMQQuery(int RMQ[11][901], int l, int r)
        {
            int idx = log2(r - l);
            return max(RMQ[idx][l], RMQ[idx][r - (1 << idx)]);
        }

    public:
        int theMaxFlowers(vector <string> flowers, int maxDiff)
        {
            int n = SIZE(flowers), m = SIZE(flowers[0]);
            for (int i = 1; i <= n; i++) {
                int LRow = 0, PRow = 0;
                for (int j = 1; j <= m; j++) {
                    LRow += flowers[i - 1][j - 1] == 'L';
                    PRow += flowers[i - 1][j - 1] == 'P';
                    L[i][j] = LRow + L[i - 1][j];
                    P[i][j] = PRow + P[i - 1][j];
                    S[i][j] = L[i][j] + P[i][j];
                }
            }

            memset(LDiffRowU, 0xff, sizeof LDiffRowU);
            memset(LDiffRowD, 0xff, sizeof LDiffRowD);
            memset(LDiffColL, 0xff, sizeof LDiffColL);
            memset(LDiffColR, 0xff, sizeof LDiffColR);
            memset(PDiffRowU, 0xff, sizeof PDiffRowU);
            memset(PDiffRowD, 0xff, sizeof PDiffRowD);
            memset(PDiffColL, 0xff, sizeof PDiffColL);
            memset(PDiffColR, 0xff, sizeof PDiffColR);
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    for (int k = i; k <= n; k++) {
                        for (int l = j; l <= m; l++) {
                            int diff = rect(L, i, j, k, l) - rect(P, i, j, k, l);
                            int sum = rect(S, i, j, k, l);
                            if (diff >= 0) {
                                LDiffRowU[k][diff] = max(LDiffRowU[k][diff], sum);
                                LDiffRowD[i][diff] = max(LDiffRowD[i][diff], sum);
                                LDiffColL[l][diff] = max(LDiffColL[l][diff], sum);
                                LDiffColR[j][diff] = max(LDiffColR[j][diff], sum);
                            }
                            if (diff <= 0) {
                                diff *= -1;
                                PDiffRowU[k][diff] = max(PDiffRowU[k][diff], sum);
                                PDiffRowD[i][diff] = max(PDiffRowD[i][diff], sum);
                                PDiffColL[l][diff] = max(PDiffColL[l][diff], sum);
                                PDiffColR[j][diff] = max(PDiffColR[j][diff], sum);
                            }
                        }
                    }
                }
            }

            memset(LDiffRowURMQ, 0xff, sizeof LDiffRowURMQ);
            memset(LDiffRowDRMQ, 0xff, sizeof LDiffRowDRMQ);
            memset(LDiffColLRMQ, 0xff, sizeof LDiffColLRMQ);
            memset(LDiffColRRMQ, 0xff, sizeof LDiffColRRMQ);
            memset(PDiffRowURMQ, 0xff, sizeof PDiffRowURMQ);
            memset(PDiffRowDRMQ, 0xff, sizeof PDiffRowDRMQ);
            memset(PDiffColLRMQ, 0xff, sizeof PDiffColLRMQ);
            memset(PDiffColRRMQ, 0xff, sizeof PDiffColRRMQ);
            for (int i = 1; i <= max(n, m); i++) {
                for (int diff = 0; diff <= n * m; diff++) {
                    LDiffRowU[i][diff] = max(LDiffRowU[i][diff], LDiffRowU[i - 1][diff]);
                    PDiffRowU[i][diff] = max(PDiffRowU[i][diff], PDiffRowU[i - 1][diff]);
                    LDiffColL[i][diff] = max(LDiffColL[i][diff], LDiffColL[i - 1][diff]);
                    PDiffColL[i][diff] = max(PDiffColL[i][diff], PDiffColL[i - 1][diff]);
                }
                RMQInit(LDiffRowURMQ[i], LDiffRowU[i], n * m + 1);
                RMQInit(PDiffRowURMQ[i], PDiffRowU[i], n * m + 1);
                RMQInit(LDiffColLRMQ[i], LDiffColL[i], n * m + 1);
                RMQInit(PDiffColLRMQ[i], PDiffColL[i], n * m + 1);
            }
            for (int i = max(n, m) - 2; i > 0; i--) {
                for (int diff = 0; diff <= n * m; diff++) {
                    LDiffRowD[i][diff] = max(LDiffRowD[i][diff], LDiffRowD[i + 1][diff]);
                    PDiffRowD[i][diff] = max(PDiffRowD[i][diff], PDiffRowD[i + 1][diff]);
                    LDiffColR[i][diff] = max(LDiffColR[i][diff], LDiffColR[i + 1][diff]);
                    PDiffColR[i][diff] = max(PDiffColR[i][diff], PDiffColR[i + 1][diff]);
                }
                RMQInit(LDiffRowDRMQ[i], LDiffRowD[i], n * m + 1);
                RMQInit(PDiffRowDRMQ[i], PDiffRowD[i], n * m + 1);
                RMQInit(LDiffColRRMQ[i], LDiffColR[i], n * m + 1);
                RMQInit(PDiffColRRMQ[i], PDiffColR[i], n * m + 1);
            }

            int res = -1;
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    for (int k = i; k <= n; k++) {
                        for (int l = j; l <= m; l++) {
                            int tdiff = rect(L, i, j, k, l) - rect(P, i, j, k, l);
                            int lmndiff, lmxdiff, pmndiff, pmxdiff;
                            if (maxDiff - abs(tdiff) >= 0) {
                                lmndiff = 0;
                                lmxdiff = min(maxDiff - tdiff, n * m) + 1;
                                pmndiff = 0;
                                pmxdiff = min(maxDiff + tdiff, n * m) + 1;
                            } else if (tdiff > 0) {
                                lmndiff = 0;
                                lmxdiff = 0;
                                pmndiff = tdiff - maxDiff;
                                pmxdiff = min(tdiff + maxDiff, n * m) + 1;
                            } else {
                                tdiff *= -1;
                                lmndiff = tdiff - maxDiff;
                                lmxdiff = min(tdiff + maxDiff, n * m) + 1;
                                pmndiff = 0;
                                pmxdiff = 0;
                            }
                            int now = -1;
                            if (lmndiff < lmxdiff) {
                                now = max(now, RMQQuery(LDiffRowURMQ[i - 1], lmndiff, lmxdiff));
                                now = max(now, RMQQuery(LDiffRowDRMQ[k + 1], lmndiff, lmxdiff));
                                now = max(now, RMQQuery(LDiffColLRMQ[j - 1], lmndiff, lmxdiff));
                                now = max(now, RMQQuery(LDiffColRRMQ[l + 1], lmndiff, lmxdiff));
                            }
                            if (pmndiff < pmxdiff) {
                                now = max(now, RMQQuery(PDiffRowURMQ[i - 1], pmndiff, pmxdiff));
                                now = max(now, RMQQuery(PDiffRowDRMQ[k + 1], pmndiff, pmxdiff));
                                now = max(now, RMQQuery(PDiffColLRMQ[j - 1], pmndiff, pmxdiff));
                                now = max(now, RMQQuery(PDiffColRRMQ[l + 1], pmndiff, pmxdiff));
                            }
                            if (now != -1) now += rect(S, i, j, k, l);
                            res = max(res, now);
                        }
                    }
                }
            }

            return res;
        }
};

#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

class TwoRectangles {
    private:
        bool rectangle(const vector<int> &A, const vector<int> &B)
        {
            return ((A[0] <= B[0] && B[0] < A[2]) || (A[0] < B[2] && B[2] <= A[2])) && (((A[1] <= B[1] && B[1] < A[3]) || (A[1] < B[3] && B[3] <= A[3])) || (B[1] <= A[1] && A[1] < B[3]) || (B[1] < A[3] && A[3] <= B[3]));
        }

        bool segment(const vector<int> &A, const vector<int> &B)
        {
            return ((A[0] == B[2] || A[2] == B[0]) && ((A[1] <= B[1] && B[1] < A[3]) || (A[1] < B[3] && B[3] <= A[3]))) || ((A[1] == B[3] || A[3] == B[1]) && ((A[0] <= B[0] && B[0] < A[2]) || (A[0] < B[2] && B[2] <= A[2])));
        }

    public:
        string describeIntersection(vector <int> A, vector <int> B)
        {
            if (rectangle(A, B) || rectangle(B, A)) return "rectangle";
            if (segment(A, B) | segment(B, A)) return "segment";

            pii rectA[] = { pii(A[0], A[1]), pii(A[2], A[3]), pii(A[0], A[3]), pii(A[2], A[1]) };
            pii rectB[] = { pii(B[0], B[1]), pii(B[2], B[3]), pii(B[0], B[3]), pii(B[2], B[1]) };
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (rectA[i] == rectB[j]) {
                        return "point";
                    }
                }
            }
            return "none";
        }
};


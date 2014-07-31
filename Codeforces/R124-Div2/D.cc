#include <iostream>
#include <string>

using namespace std;

int n, m;
string mat[2000];
bool vis[2000][2000];
int firstx[2000][2000], firsty[2000][2000];

bool floodfill(int x, int y)
{
    int xx = ((x % n) + n) % n, yy = ((y % m) + m) % m;
    if (mat[xx][yy] == '#') return false;
    if (vis[xx][yy]) {
        if (x == firstx[xx][yy] && y == firsty[xx][yy]) return false;
        return true;
    }

    vis[xx][yy] = true;
    firstx[xx][yy] = x;
    firsty[xx][yy] = y;

    if (floodfill(x - 1, y)) return true;
    if (floodfill(x + 1, y)) return true;
    if (floodfill(x, y - 1)) return true;
    if (floodfill(x, y + 1)) return true;
}

int main()
{
    cin >> n >> m;

    int x0, y0;
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 'S') {
                x0 = i;
                y0 = j;
            }
        }
    }
    if (floodfill(x0, y0)) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}


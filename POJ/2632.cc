/*
 *  SRC: POJ 2632
 * PROB: Crashing Robots
 * ALGO: NULL
 * DATE: Jul 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <vector>

using namespace std;

struct Robot {
    int x, y, d;
    Robot(int _x, int _y, int _d) : x(_x), y(_y), d(_d) { }
};

const int dir[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int main()
{
    int tasks;
    cin >> tasks;
    while (tasks--) {
        int a, b, n, m;
        vector<Robot> robots;
        cin >> a >> b >> n >> m;
        for (int i = 0; i < n; i++) {
            int x, y, d;
            char td;
            cin >> x >> y >> td;
            switch (td) {
                case 'N': d = 0; break;
                case 'E': d = 1; break;
                case 'S': d = 2; break;
                case 'W': d = 3;
            }
            robots.push_back(Robot(x, y, d));
        }

        for (int ins = 0; ins < m; ins++) {
            int idx, repeat;
            char action;
            cin >> idx >> action >> repeat;
            idx--;
            switch (action) {
                case 'L': robots[idx].d = ((robots[idx].d - repeat) % 4 + 4) % 4; break;
                case 'R': robots[idx].d = (robots[idx].d + repeat) % 4; break;
                case 'F': {
                              for (int i = 0; i < repeat; i++) {
                                  int x = robots[idx].x + dir[robots[idx].d][0];
                                  int y = robots[idx].y + dir[robots[idx].d][1];
                                  if (x < 1 || x > a || y < 1 || y > b) {
                                      cout << "Robot " << idx + 1 << " crashes into the wall" << endl;
                                      while (++ins < m) {
                                          cin >>idx >> action >> repeat;
                                      }
                                      goto next_loop;
                                  }
                                  for (int j = 0; j < n; j++) {
                                      if (j != idx && x == robots[j].x && y == robots[j].y) {
                                          cout << "Robot " << idx + 1 << " crashes into robot " << j + 1 << endl;
                                          while (++ins < m) {
                                              cin >>idx >> action >> repeat;
                                          }
                                          goto next_loop;
                                      }
                                  }
                                  robots[idx].x = x;
                                  robots[idx].y = y;
                              }
                          }
            }
        }
        cout << "OK" << endl;
next_loop:
        ;
    }

    return 0;
}

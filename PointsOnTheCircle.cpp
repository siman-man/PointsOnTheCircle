// C++11
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_N = 200;

double dist[MAX_N][MAX_N];

int N;

class PointsOnTheCircle {
public:
    void init(vector<int> matrix) {
        N = (int) sqrt(matrix.size());

        for (int i = 0; i < N; i++) {
            dist[i][i] = 0.0;

            for (int j = 1; j < N; j++) {
                double r = j * N / 360.0;
                double l = 2 - 2 * cos(r / 180);
                dist[i][(i+j)%N] = l;
                dist[(i+j)%N][i] = l;
            }
        }
    }

    vector<int> permute(vector<int> matrix) {
        init(matrix);
        vector<int> ret(N);
        for (int i = 0; i < N; ++i) {
            ret[i] = N - i - 1;
        }
        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T>
void getVector(vector <T> &v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    PointsOnTheCircle pc;
    int M;
    cin >> M;
    vector<int> matrix(M);
    getVector(matrix);

    vector<int> ret = pc.permute(matrix);
    cout << ret.size() << endl;
    for (int i = 0; i < (int) ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}

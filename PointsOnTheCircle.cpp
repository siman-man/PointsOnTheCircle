// C++11
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

const int MAX_N = 200;

bool connect[MAX_N][MAX_N];
double dist[MAX_N][MAX_N];
int mapping[MAX_N];

int N;

unsigned long long xor128() {
    static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
    unsigned long long rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}

class PointsOnTheCircle {
public:
    void init(vector<int> matrix) {
        N = (int) sqrt(matrix.size());

        fprintf(stderr, "N = %d\n", N);

        for (int i = 0; i < N; i++) {
            dist[i][i] = 0.0;

            for (int j = 1; j < N; j++) {
                double r = j * 360.0 / N;
                double l = sqrt(2 - 2 * cos(r * M_PI / 180.0));
                dist[i][(i + j) % N] = l;
                dist[(i + j) % N][i] = l;
            }
        }

        for (int i = 0; i < N; i++) {
            connect[i][i] = false;
            mapping[i] = i;

            for (int j = 0; j < N; j++) {
                int z = i * N + j;
                connect[i][j] = matrix[z];
            }
        }
    }

    vector<int> permute(vector<int> matrix) {
        init(matrix);
        reconnectLine();
        fprintf(stderr, "Total length = %f\n", calcScore());
        return createAnswer();
    }

    void reconnectLine() {
        int bestScore = calcScore();

        for (int t = 0; t < 1000; t++) {
            int i = xor128() % N;
            int j = xor128() % N;
            swapMapping(i, j);
            double score = calcScore();

            if (bestScore > score) {
                bestScore = score;
            } else {
                swapMapping(i, j);
            }
        }
    }

    void swapMapping(int i, int j) {
        int t = mapping[i];
        mapping[i] = mapping[j];
        mapping[j] = t;
    }

    double calcScore() {
        double length = 0.0;

        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (connect[i][j]) {
                    length += dist[mapping[i]][mapping[j]];
                }
            }
        }

        return length;
    }

    vector<int> createAnswer() {
        vector<int> ret;

        for (int i = 0; i < N; i++) {
            ret.push_back(mapping[i]);
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

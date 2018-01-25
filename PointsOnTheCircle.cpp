// C++11
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
typedef long long ll;

const int MAX_N = 200;

bool connect[MAX_N][MAX_N];
double dist[MAX_N][MAX_N];
int edge[MAX_N][MAX_N];
int edgeCount[MAX_N];
int mapping[MAX_N];

int N;
ll startCycle;

double TIME_LIMIT = 10.0;
const ll CYCLE_PER_SEC = 2700000000;

unsigned long long xor128() {
    static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
    unsigned long long rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}

unsigned long long int getCycle() {
    unsigned int low, high;
    __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long int) low) | ((unsigned long long int) high << 32);
}

double getTime(unsigned long long int begin_cycle) {
    return (double) (getCycle() - begin_cycle) / CYCLE_PER_SEC;
}

class PointsOnTheCircle {
public:
    void init(vector<int> matrix) {
        N = (int) sqrt(matrix.size());

        memset(edge, -1, sizeof(edge));
        memset(edgeCount, 0, sizeof(edgeCount));

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
            int nc = 0;

            for (int j = 0; j < N; j++) {
                int z = i * N + j;
                connect[i][j] = matrix[z];

                if (connect[i][j]) {
                    edge[i][nc] = j;
                    nc++;
                }
            }

            edgeCount[i] = nc;
        }
    }

    vector<int> permute(vector<int> matrix) {
        startCycle = getCycle();

        init(matrix);

        reconnectLine();

        return createAnswer();
    }

    void reconnectLine() {
        double bestScore = calcScore();
        int bestMapping[MAX_N];
        memcpy(bestMapping, mapping, sizeof(mapping));

        double currentScore = bestScore;

        double currentTime = getTime(startCycle);
        double remainTime = 0.0;
        int tryCount = 0;

        int R = 500000;
        double k = 0.5;

        double diffScore = 0.0;
        int i, j;

        while (currentTime < TIME_LIMIT) {
            currentTime = getTime(startCycle);
            remainTime = (TIME_LIMIT - currentTime) / TIME_LIMIT;

            do {
                i = xor128() % N;
                j = xor128() % N;
            } while (i == j);

            diffScore = calcScoreSub(i) + calcScoreSub(j);
            swapMapping(i, j);
            diffScore -= calcScoreSub(i) + calcScoreSub(j);

            double score = currentScore - diffScore;

            if (currentScore > score || (diffScore > -20 && xor128() % R < R * exp(diffScore / (k * sqrt(remainTime))))) {
                currentScore = score;

                if (bestScore > score) {
                    bestScore = score;
                    memcpy(bestMapping, mapping, sizeof(mapping));
                }
            } else {
                swapMapping(i, j);
            }

            tryCount++;
        }

        memcpy(mapping, bestMapping, sizeof(bestMapping));
        fprintf(stderr, "bestScore = %f, tryCount = %d\n", bestScore, tryCount);
    }

    void swapMapping(int i, int j) {
        int t = mapping[i];
        mapping[i] = mapping[j];
        mapping[j] = t;
    }

    double calcScoreSub(int i) {
        double length = 0.0;
        int v = mapping[i];

        for (int j = 0; j < edgeCount[i]; j++) {
            length += dist[v][mapping[edge[i][j]]];
        }

        return length;
    }

    double calcScore() {
        double length = 0.0;

        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (connect[i][j]) {
                    length += dist[mapping[i]][mapping[j]] * connect[i][j];
                }
            }
        }

        return length;
    }

    vector<int> createAnswer() {
        vector<int> ret(N);

        for (int i = 0; i < N; i++) {
            ret[mapping[i]] = i;
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
    TIME_LIMIT = 2.0;
    PointsOnTheCircle pc;
    int M;
    cin >> M;
    vector<int> matrix(M);
    getVector(matrix);

    vector<int> ret = pc.permute(matrix);
    cout << ret.size() << endl;
    for (int i = 0; i < (int) ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();
}

N points labeled from 0 to N-1 are drawn on the circle of radius 1 so that the angle between each pair of adjacent points is 360/N degrees.

0 から N - 1 にラベル付された N 個の点が半径1 の円の上に描画されています。それぞれ幾つかの点と隣り合っています

Pairs of points with certain labels will be connected with straight lines.

幾つかの点のペアは直線で結ばれています

Your task is to find a permutation of the labels for the points which will minimize the sum of lengths of these lines.

あなたはこのラベルの紐付けを各直線距離が短くなるように設定してください

Implementation
Your code should implement a single method permute(vector <int> m). m[i*N+j] = 1 if the points with labels i and j have to be connected with a line, and 0 otherwise. You can deduce N as sqrt(length(m)). The matrix represented by m is symmetrical (m[i*N+j] = m[j*N+i] for all i, j), with diagonal elements m[i*N+i] = 0. 


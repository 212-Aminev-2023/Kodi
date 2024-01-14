#include "processor.h"

processor::processor(int A1, int A2, int B1, int B2, rover& turtle) {
	this->A1 = A1;
	this->A2 = A2;
	this->B1 = B1;
	this->B2 = B2;
	this->turtle = turtle;
}

processor::processor() {
    A1 = 0;
    A2 = 0;
    B1 = 0;
    B2 = 0;
}

void processor::route() {
	ofstream fr("route.txt");
    int i, j, k, l, m;
    int n = 128 * 128;
    int s = A1 * 127 + A2;
    int t = B1 * 127 + B2;
    vector<vector<int>> adj(n);
    vector<int> dist(n, n);
    vector<int> p(n, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    for (i = 0; i < 128; i++) {
        for (j = 0; j < 128; j++) {
            for (k = i - 1; k < i + 2; k++) {
                for (l = j - 1; l < j + 2; l++) {
                    if (k > 0 && k < 128 && l > 0 && l < 128 && !(k == i && l == j)) {
                        if (turtle.sensor(i, j, k, l) && turtle.angles(i, j, k, l)) {
                            m = 127 * i + j;
                            adj[m].push_back(127 * k + l);
                        }
                    }
                }
            }
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (dist[u] > dist[v] + 1) {
                p[u] = v;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    if (dist[t] == n) {
        cout << "The rover can't get from point A to point B" << endl;
    }
    vector<int> path;
    while (t != -1) {
        path.push_back(t);
        t = p[t];
    }
    for (i = path.size() - 1; i > -1; i--) {
        k = path[i] / 127;
        l = path[i] % 127;
        fr << double(k * 10) / 128 << " " << double(l * 10) / 128 << " " << double(turtle.swamp.Pixel[k][l] * 10) / 128 << endl;
    }
}
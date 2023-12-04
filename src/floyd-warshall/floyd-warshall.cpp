#include <chrono>

#include "../headers.h"

int floyd_warshall(int source, int target, vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> distance(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i == j)
                distance[i][j] = 0;
            else if (adj[i][j])
                distance[i][j] = adj[i][j];
            else
                distance[i][j] = 99999;
        }
    }
    for (int k = 1; k < n; k++) {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                distance[i][j] = min(distance[i][j],
                                     distance[i][k] + distance[k][j]);
            }
        }
    }
    return distance[source][target];
}

void benchmark(int n, int m, int source, int target) {
    ifstream fin("../test" + to_string(n) + "." + to_string(m) + ".in");
    ofstream fout("floyd-warshall" + to_string(n) + "." + to_string(m) + ".out");
    cout << "Test " << n << ":" << endl;

    // fast_io;
    const int v = pow(5, n);
    vector<vector<int>> adj(v + 1, vector<int>(v + 1, 0));

    int a, b, w;
    int t;
    fin >> t;
    while (t--) {
        fin >> a >> b >> w;
        adj[a][b] = w;
        adj[b][a] = w;
    }
    auto start = chrono::high_resolution_clock::now();
    const int ans = floyd_warshall(source, target, adj);
    auto end = chrono::high_resolution_clock::now();

    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "========================" << endl;
    cout << "distance from " << source << " to " << target << " = " << ans << endl;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fout << "distance from " << source << " to " << target << " = " << ans << endl;
    fout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fin.close();
    fout.close();
}

int main() {
    cout << "input source and target" << endl;
    cout << "========================" << endl;
    cout << "input source: ";
    int source;
    cin >> source;
    cout << "input target: ";
    int target;
    cin >> target;

    int i = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            benchmark(i, j, source, target);
        }
    }
    return (0);
}
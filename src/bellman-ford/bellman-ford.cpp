#include <chrono>

#include "../headers.h"

vector<tuple<int, int, int>> edges;
int bellman_ford(int source, int target, const int vertices) {
    vector<int> distance(vertices + 1);
    for (int i = 1; i <= vertices; i++) {
        distance[i] = 100000;
    }
    distance[source] = 0;  // distance from source

    for (int i = 1; i <= vertices - 1; i++) {
        for (auto &edge : edges) {
            int a, b, w;
            tie(a, b, w) = edge;
            //! it's possible for the integer to overflow
            distance[b] = min(distance[b], distance[a] + w);
        }
    }
    return distance[target];
}

void benchmark(int n, int m, int source, int target) {
    ifstream fin("../test" + to_string(n) + "." + to_string(m) + ".in");
    ofstream fout("bellman_ford" + to_string(n) + "." + to_string(m) + ".out");
    cout << "Test " << n << ":" << endl;

    int a, b, w;
    int t;
    fin >> t;
    while (t--) {
        fin >> a >> b >> w;
        edges.pb(make_tuple(a, b, w));
    }
    const int vertices = pow(5, n);
    auto start = chrono::high_resolution_clock::now();
    const int ans = bellman_ford(source, target, vertices);
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

    edges.clear();
}

// cout << "Case #" << t << ": ";
int main() {
    // fast_io;
    cout << "input source and target" << endl;
    cout << "========================" << endl;
    cout << "input source: ";
    int source;
    cin >> source;
    cout << "input target: ";
    int target;
    cin >> target;

    // fast_io;
    int i = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            benchmark(i, j, source, target);

    return (0);
}
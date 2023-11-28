#include <chrono>

#include "../headers.h"

const int N = 5000;
int mat[N + 1][N + 1];
vector<vector<pair<int, int>>> adj(N); 

int floyd_warshall(int source, int target) {
    for (int i = 1; i <= N; i++) {
        mat[i][i] = 0;
    }

    for (int i = 1; i <= N; i++) {
        for (auto &x : adj[i]) {
            mat[i][x.fi] = x.sc;
        }
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++)
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
        }
    }

    return mat[source][target];
}

void benchmark(int n, int m, int source, int target) {
    ifstream fin("../test" + to_string(n) + "." + to_string(m) + ".in");
    ofstream fout("floyd-warshall" + to_string(n) + "." + to_string(m) + ".out");
    cout << "Test " << n << ":" << endl;

    int a, b, w;
    int t;
    fin >> t;
    while (t--) {
        fin >> a >> b >> w;
        mat[a][b] = w; //.pb(mk(b, w));
    }
    auto start = chrono::high_resolution_clock::now();
    const int ans = floyd_warshall(source, target);
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
            cout << "i = " << i << " j = " << j << endl;
            benchmark(i, j, source, target);
        }
    }

    return (0);
}
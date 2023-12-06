#include <chrono>

#include "../headers.h"
#include "../timer.h"

int johnson(int source, int target, vector<vector<int>> &adj) {
    int vert = adj.size() - 1, edge, i, j, k;
    for (i = 1; i <= vert; i++)
        for (j = 1; j <= vert; j++) {
            if (adj[i][j] == 0 && i != j)
                adj[i][j] = 999999;  // if there is no edge, put infinity
        }
    for (k = 1; k <= vert; k++)
        for (i = 1; i <= vert; i++)
            for (j = 1; j <= vert; j++)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    return adj[source][target];
}
ifstream fin2("johnson.out");
ofstream fout("johnson.out");
void benchmark(int n, int m, int source, int target) {
    ifstream fin("../test" + to_string(n) + "." + to_string(m) + ".in");
    cout << "Test " << n << "." << m << ":" << endl;
    string content;
    if (fin2.is_open()) {
        string line;
        while (fin2 >> line) {
            content.append(line);
            fout << line << endl;
        }
    }

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
    double time_taken = calculateTime([&]() { johnson(source, target, adj); });

    cout << "========================" << endl;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fin.close();
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
    fout.close();
    return (0);
}
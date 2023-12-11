#include "../headers.h"
#include "../timer.h"

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

ifstream fin2("bellman-ford.out");
ofstream fout("bellman-ford.out");
void benchmark(int n, int m, int source, int target) {
    ifstream fin("../test" + to_string(n) + "." + to_string(m) + ".in");
    cout << "Test " << n << "." << m << ":" << endl;
    string content;
    if(fin2.is_open()){
        string line;
        while(fin2 >> line){
            content.append(line);
            fout << line << endl;
        }
    }

    int a, b, w;
    int t;
    fin >> t;
    while (t--) {
        fin >> a >> b >> w;
        edges.pb(make_tuple(a, b, w));
    }
    const int vertices = pow(5, n);

    double time_taken = calculateTime([&]() {
        bellman_ford(source, target, vertices);
    });

    cout << "========================" << endl;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fin.close();

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

    fout.close();
    return (0);
}
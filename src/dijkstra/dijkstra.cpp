#include <chrono>

#include "../headers.h"
#include "../timer.h"

const int N = 100005;
vector<vector<pair<int, int>>> adj(N);  // adj list with both the nodes and the weights

// priority_queue comparator
class Compare {
   public:
    bool operator()(pii a, pii b) {
        return a.sc > b.sc;
    }
};
priority_queue<pii, vector<pii>, Compare> q;

int dijkstra(int source, int target) {
    int distance[N + 1];
    for (auto &x : distance) x = imax;
    distance[source] = 0;                  // distance from source
    q.push(mk(source, distance[source]));  // push the first node into the queue

    /*
    for a given pair s = (a,b) the first element is the node
        and the second is the distance from the source
    */
    while (!q.empty()) {
        pii s = q.top();  // first node in the queue
        q.pop();          // remove the first node from the queue
        for (auto &x : adj[s.fi]) {
            if (distance[x.fi] > distance[s.fi] + x.sc) {
                distance[x.fi] = distance[s.fi] + x.sc;
                q.push(x);
            }
        }
    }
    return distance[target];
}

ifstream fin2("dijkstra.out");
ofstream fout("dijkstra.out");
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
        adj[a].pb(mk(b, w));
    }
    double time_taken = calculateTime([&]() {
        dijkstra(source, target);
    });

    cout << "========================" << endl;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fin.close();
    for (auto &x : adj) {
        x.clear();
    }
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

    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            benchmark(i, j, source, target);

    return (0);
}
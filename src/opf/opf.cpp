#include "../headers.h"
#include "../timer.h"

//https://ic.unicamp.br/~afalcao/mo443/slides-aula30.pdf
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

vector<int> opf(int source, int target) {
    int distance[N + 1];
    for (auto &x : distance) x = 999999;
    distance[source] = 0;                  // distance from source
    q.push(mk(source, distance[source]));  // push the first node into the queue

    while (!q.empty()) {
        pii s = q.top();  // first node in the queue
        q.pop();          // remove the first node from the queue
        for (auto &x : adj[s.fi]) {
            int b = x.fi, w = s.sc;
            int tmp = max(distance[s.fi], w);
            if (tmp < distance[b]) {
                distance[b] = tmp;
                q.push(x);
            }
        }
    }
    vector<int> newDistance(N + 1);
    for(int i = 0; i < N+1; ++i){
        newDistance[i] = distance[i];
    }
    return newDistance;
}

ifstream fin2("opf.out");
ofstream fout("opf.out");
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
    double time_taken = calculateTime([&](){
        opf(source, target);
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

    fout.close();
    return (0);
}
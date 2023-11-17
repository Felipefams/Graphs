#include <chrono>
#include "./headers.h"

using namespace std;
// vrum vrum
#define fast_io                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
// constants
#define endl "\n"
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define exp 1e9
#define imax INT_MAX
#define imin INT_MIN
// functions
#define sqr(a) (a) * (a)
#define sz(x) ((int)x.size())
#define watch(x) cout << (#x) << " is " << (x) << endl
// utils
#define umap unordered_map
#define uset unordered_set
#define pb push_back
#define mk make_pair
#define fi first
#define sc second
// types
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &v) {
    for (auto &x : v) os << x << " ";
    os << endl;
    return os;
}
// ! You can ignore the code above this line

const int N = 100005;
// vector<int> adj[N];
vector<vector<pair<int, int>>> adj(N);  // adj list with both the nodes and the weights

class Compare {
   public:
    bool operator()(pii a, pii b) {
        return a.sc > b.sc;
    }
};
priority_queue<pii, vector<pii>, Compare> q;

int djikstra(int source, int target) {
    bool visited[N + 1];
    int distance[N + 1];
    for (auto &x : distance) x = imax;
    visited[source] = true;                // mark as visited
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
                visited[x.fi] = true;
                q.push(x);
            }
        }
    }
    return distance[target];
}
ifstream fin("test.in");
ofstream fout("test.out");

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

    int a, b, w;
    int t;
    fin >> t;
    while (t--) {
        fin >> a >> b >> w;
        adj[a].pb(mk(b, w));
        // adj[b].pb(mk(a,w));
    }
    auto start = chrono::high_resolution_clock::now();
    const int ans = djikstra(source, target);
    auto end = chrono::high_resolution_clock::now();

    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "========================" << endl;
    cout << "distance from " << source << " to " << target << " = " << ans << endl;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    fout << "distance from " << source << " to " << target << " = " << ans << endl;
    return (0);
}
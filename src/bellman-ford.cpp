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

const int N = 126;

vector<tuple<int, int, int>> edges;
int bellman_ford(int source, int target) {
    int distance[N + 1];
    for (auto &x : distance) x = imax;
    distance[source] = 0;  // distance from source

    for (int i = 0; i < N - 1; i++) {
        for (auto &edge : edges) {
            int a, b, w;
            tie(a, b, w) = edge;
            distance[b] = min(distance[b], distance[a] + w);
        }
    }
    return distance[target];
}
ifstream fin("test.in");
ofstream fout("test.out");

// cout << "Case #" << t << ": ";
int main() {
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
        edges.pb(make_tuple(a, b, w));
        // edges.pb(make_tuple(b, a, w)); // uncomment this line for undirected graphs 
    }
    auto start = chrono::high_resolution_clock::now();
    const int ans = bellman_ford(source, target);
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
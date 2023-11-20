#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <set>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& v) {
    for (auto& x : v) os << x << " ";
    os << endl;
    return os;
}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

// random device singleton
random_device dev;
mt19937 rng(dev());
int generateRandomInt(const int LOWER_BOUND, const int UPPER_BOUND) {
    uniform_int_distribution<mt19937::result_type> random(LOWER_BOUND, UPPER_BOUND);
    return random(rng);
}

vector<tuple<int, int, int>> generateRandomEdges(const int edges,const int vertices, ofstream& fout) {
    vector<tuple<int, int, int>> edgesVector;

    set<pair<int, int>> edgesSet;
    int loopBound = edges;
    for (int i = 0; i < loopBound; i++) {
        int firstEdge = generateRandomInt(1, vertices);
        int secondEdge = generateRandomInt(1, vertices);
        while (firstEdge == secondEdge) {
            secondEdge = generateRandomInt(1, vertices);
        }
        if (edgesSet.find(make_pair(firstEdge, secondEdge)) != edgesSet.end()) {
            // repeat the loop if pair is already in the set
            loopBound++;
            continue;
        }
        const int weight = generateRandomInt(1, 100);

        // fout << firstEdge << " " << secondEdge << " " << weight << endl;
        edgesSet.insert(make_pair(firstEdge, secondEdge));
        edgesVector.push_back(make_tuple(firstEdge, secondEdge, weight));
    }

    return edgesVector;
}

void writeEdgesToFile(const int edges, const int vertices, ofstream& fout) {
    vector<tuple<int, int, int>> edgesVector = generateRandomEdges(edges, vertices, fout);
    fout << edges << endl;
    for (auto& edge : edgesVector) {
        int a, b, w;
        tie(a, b, w) = edge;
        fout << a << " " << b << " " << w << endl;
    }
}

int main(void) {
    cout << "Random number generator" << endl;
    cout << "=======================" << endl;
    cout << "Choose a number between [1...5]" << endl;
    int x;
    cin >> x;

    if (x < 1 || x > 5)
        throw std::invalid_argument("x must be between [1...5]");

    // constraints
    // number of vertices, ill be testing with 5^x, where x in [1...5]
    const int V = pow(5, x);
    cout << "n of vertices = " << V << endl;

    // lower bound and upper bound for the number of edges
    const int LOWER_BOUND = (V - 1);
    const int UPPER_BOUND = (V * (V - 1) / 2);

    const int edges = generateRandomInt(LOWER_BOUND, UPPER_BOUND);

    cout << "n of edges = " << edges << endl;

    setIO("");
    ofstream fout("test" + to_string(x) + ".in");

    writeEdgesToFile(edges, V, fout);

    return 0;
}
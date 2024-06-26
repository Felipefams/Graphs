#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <unordered_set>

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

vector<tuple<int, int, int>> generateRandomEdges(const int edges, const int vertices, ofstream& fout) {
    vector<tuple<int, int, int>> edgesVector;
    for(int i = 0; i < vertices - 1; i++) {
        const int weight = generateRandomInt(1, 100);
        edgesVector.push_back(make_tuple(i + 1, i + 2, weight));
    }

    set<pair<int, int>> edgesSet;
    int loopBound = edges - (vertices - 1);
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
        edgesSet.insert(make_pair(secondEdge, firstEdge));
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

const vector<int> generateTestRange(const int LOWER_BOUND = 4, const int UPPER_BOUND = 10) {
    vector<int> v;
    for (int i = 0; i < 5; i++) {
        v.push_back(
            LOWER_BOUND + (i * (UPPER_BOUND - LOWER_BOUND) / 4));
    }
    return v;
}

//todo gurantee that the graph is connected
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

    vector<int> testEdges = generateTestRange(LOWER_BOUND, UPPER_BOUND);

    setIO("");

    cout << "test edges = ";
    for(auto&x : testEdges) cout << x << " ";
    for (int i = 1; i <= testEdges.size(); i++) {

        const string fileName = "test" + to_string(x) + "." + to_string(i) + ".in";
        cout << "writing to file " << fileName << endl;
        ofstream fout(fileName);

        writeEdgesToFile(testEdges[i - 1], V, fout);
    }

    return 0;
}

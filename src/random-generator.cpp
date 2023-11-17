#include <random>
#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
std::ostream & operator << (std::ostream &os ,std::vector<T> &v){
	for(auto& x : v) os << x << " ";	
	os << endl;
	return os;
}


void setIO(string name = ""){
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
int generateRandomInt(const int LOWER_BOUND, const int UPPER_BOUND){
    uniform_int_distribution<mt19937::result_type> random(LOWER_BOUND, UPPER_BOUND); 
    return random(rng); 
}

void writeEdgesToFile(const int edges, const int vertices, ofstream& fout){
    int firstEdge = generateRandomInt(1, vertices);
    int secondEdge = generateRandomInt(1, vertices);
    while(firstEdge == secondEdge){
        secondEdge = generateRandomInt(1, vertices);
    }
    const int weight = generateRandomInt(1, 1000);

    fout << firstEdge << " " << secondEdge << " " << weight << endl;
}

int main(void){ 

    cout << "Random number generator" << endl;
    cout << "=======================" << endl;
    cout << "Choose a number between [1...5]" << endl;  
    int x; cin >> x; 

    if(x < 1 || x > 5) 
        throw std::invalid_argument("x must be between [1...5]");

    // constraints
    //number of vertices, ill be testing with 5^x, where x in [1...5]
    const int V = pow(5, x);
    cout << "n of vertices = " << V << endl;

    //lower bound and upper bound for the number of edges
    const int LOWER_BOUND = (V - 1);
    const int UPPER_BOUND = (V * (V - 1) / 2);

    const int edges = generateRandomInt(LOWER_BOUND, UPPER_BOUND);

    cout << "n of edges = " << edges << endl;

    setIO("test");

    ofstream fout ("test.in");	

    fout << edges << endl;
    for(int i = 0; i < edges; i++){
        writeEdgesToFile(edges, V, fout);
    }

    return 0;
}
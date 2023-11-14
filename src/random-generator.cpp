#include <random>
#include <iostream>
using namespace std;

int generateRandomInt(const int LOWER_BOUND, const int UPPER_BOUND){
    random_device dev;
    mt19937 rng(dev());

    // distribution in range [LOWER_BOUND, UPPER_BOUND]
    uniform_int_distribution<mt19937::result_type> random(LOWER_BOUND, UPPER_BOUND); 

    return random(rng); 
}

int main(void)
{ 

    cout << "Random number generator" << endl;
    cout << "=======================" << endl;
    cout << "Choose a number between [1...7]" << endl;  
    int x; cin >> x; 

    if(x < 1 || x > 7) 
        throw std::invalid_argument("x must be between [1...7]");

    // constraints
    //number of vertices, ill be testing with 5^x, where x in [1...7]
    const int V = pow(5, x);
    cout << "n of vertices = " << V << endl;

    //lower bound and upper bound for the number of edges
    const int LOWER_BOUND = (V - 1);
    const int UPPER_BOUND = (V * (V - 1) / 2);


    const int edges = generateRandomInt(LOWER_BOUND, UPPER_BOUND);

    cout << "n of edges = " << edges << endl;
}
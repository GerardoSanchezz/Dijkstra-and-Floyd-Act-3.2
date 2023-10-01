#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include "graph.h"
#include <stdexcept> 

// Authors:
// Gerardo Ulises Sanchez Felix - A01641788
// Alan Antonio Ruelas Robles - A01641426

// Compile it with: g++ main.cpp Graph.cpp -o main.exe
// Run it with: ./main.exe < ../src/inputFiles/test.txt (or whatever input file you want)

using namespace std;

float** createEmptyMatrix(int);
void printMatrix(float**, int);
float** floydWarshall(Graph);
float** getCopyOfMatrix(float**, int);
float** dijkstraForAllNodes(Graph);
float* dijkstra(Graph, int);
void floydWarshallToFile(float**, int, string);
void dijkstraToFile(float**, int, string);
void releaseMatrix(float**, int);

/* 
DIJKSTRA'S ALGORITHM:
The complexity of this implementation of the Dijkstra's algorithm is O((V + E) * log(V)).
Where:
- V represents the number of nodes in the graph.
- E represents the number of edges.

The space complexity is O(V^2).
Where:
- V represents the number of nodes in the graph.

 The dominant factor here is the weightMatrix, which has a quadratic relationship with the number of nodes.

We decided to use a priority queue to store the nodes that are adjacent to the current node because
is more efficient than using a vector and sorting it every time we add a new node to it.
*/

/*
FLOYD-WARSHALL ALGORITHM:
The complexity of this implementation of the Floyd-Warshall algorithm is O(V^3).
Where:
- V represents the number of nodes in the graph.
This is because we have three nested loops, each one of them iterating over all the nodes in the graph.

About the space complexity, we have to store the weight matrix of the graph and the previous matrix.
The weight matrix is a matrix of size VxV, and the previous matrix is a matrix of size VxV.
So, the space complexity is O(V^2).
*/

/*
ABOUT TEST CASES:
test1: We decided to include this case because we already knew the answer.
test2: We decided to include this case because it has a negative weights.
test3: In this case, a disconnected graph is created with two separate components
test4: This is a graph with only one node. 
*/

int main() {

    int numNodes = 0;
    int numEdges = 0;
    cout << "Number of nodes: ";
    cin >> numNodes;
    cout << "Number of edges: ";
    cin >> numEdges;

    if (numNodes <= 0 || numEdges <= 0) {
        cout << endl;
        throw invalid_argument("Number of nodes and edges must be positive.");
    }

    Graph graph = Graph(numNodes, numEdges);
    graph.fillMatrix();
    // printMatrix(graph.getWeightMatrix(), numNodes);

    float** allPairs = floydWarshall(graph);
    // printMatrix(allPairs, numNodes);
    floydWarshallToFile(allPairs, numNodes, "Floyd-Warshall.txt");

    releaseMatrix(allPairs, numNodes);

    float** dijk = dijkstraForAllNodes(graph);
    // printMatrix(dijk, numNodes);
    dijkstraToFile(dijk, numNodes, "Dijkstra.txt");
    releaseMatrix(dijk, numNodes);
     
    return 0;
}

float** createEmptyMatrix(int numNodes) {
    float** matrix = new float*[numNodes];
    for(int i = 0; i < numNodes; i++) {
        matrix[i] = new float[numNodes];
    }
    return matrix;
}

void printMatrix(float** matrix, int numNodes) {
    cout << endl;
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

float** floydWarshall(Graph graph) {
    float** previous;
    int n = graph.getNumNodes();
    float** current = graph.getWeightMatrix();
    for(int k = 0; k < n; k++) {
        previous = getCopyOfMatrix(current, n);
        current = createEmptyMatrix(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                current[i][j] = min(previous[i][j], previous[i][k] + previous[k][j]);
            }
        }
        releaseMatrix(previous, n);
    }
    return current;
}

float** getCopyOfMatrix(float** matrix, int numNodes) {
    float** copyMatrix = createEmptyMatrix(numNodes);
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            copyMatrix[i][j] = matrix[i][j];
        }
    }
    return copyMatrix;
}

float** dijkstraForAllNodes(Graph graph) {
    int n = graph.getNumNodes();
    float** shortestDistances = createEmptyMatrix(n);
    for(int source = 0; source < n; source++) {
        shortestDistances[source] = dijkstra(graph, source);
    }
    return shortestDistances;
}

float* dijkstra(Graph graph, int source) {
    int n = graph.getNumNodes();
    float Inf = numeric_limits<float>::infinity();  
    float** weightMatrix = graph.getWeightMatrix();
    
    float* distances = new float[n];
    for(int i = 0; i < n; i++) {
        distances[i] = Inf;
    }
    distances[source] = 0; 

    int* previous = new int[n];
    for(int i = 0; i < n; i++) {
        previous[i] = -1;
    }

    vector<int> S;

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

    pq.push(make_pair(0, source));


    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        S.push_back(u);
        for (int v = 0; v < n; v++) {
            bool isAdjacent = weightMatrix[u][v] != Inf;
            if (isAdjacent) {
                if (distances[v] > distances[u] + weightMatrix[u][v]) {
                    distances[v] = distances[u] + weightMatrix[u][v];
                    previous[v] = u;
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
    }
    
    return distances;
}

void floydWarshallToFile(float** matrix, int numNodes, string fileName) {
    fileName = "../src/outputFiles/" + fileName;
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo " << fileName << endl;
        return;
    }

    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            outputFile << matrix[i][j] <<  '\t';
        }
        outputFile << endl;
    }

    outputFile.close();
}

void dijkstraToFile(float** matrix, int numNodes, string fileName) {
    fileName = "../src/outputFiles/" + fileName;
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo " << fileName << endl;
        return;
    }

    for (int source = 0; source < numNodes; source++) {
        for (int destination = 0; destination < numNodes; destination++) {
            if (destination != source) {
                outputFile << "node " << (source + 1) << " to node " << (destination + 1) << " : " << matrix[source][destination]  << endl;
            }
        }
        outputFile << endl;
    }

    outputFile.close();
}

void releaseMatrix(float** matrix, int n) {
    for(int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include "graph.h"

// Comand to run it: g++ main.cpp Graph.cpp -o main.exe
// ./main.exe < ../src/inputFiles/test.txt

using namespace std;

float** createEmptyMatrix(int);
void printMatrix(float**, int);
float** floydWarshall(Graph);
float** getCopyOfMatrix(float**, int);
float** dijkstraForAllNodes(Graph);
float* dijkstra(Graph, int);
void floydWarshallToFile(float**, int, string);
void dijkstraToFile(float**, int, string);

int main() {

    int numNodes = 0;
    int numEdges = 0;
    cout << "Number of nodes: ";
    cin >> numNodes;
    cout << "Number of edges: ";
    cin >> numEdges;

    Graph graph = Graph(numNodes, numEdges);
    graph.fillMatrix();
    printMatrix(graph.getWeightMatrix(), numNodes);

    float** allPairs = floydWarshall(graph);
    printMatrix(allPairs, numNodes);
    floydWarshallToFile(allPairs, numNodes, "Floyd-Warshall.txt");

    float** dijk = dijkstraForAllNodes(graph);
    printMatrix(dijk, numNodes);
    dijkstraToFile(dijk, numNodes, "Dijkstra.txt");
     
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

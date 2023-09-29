#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include "graph.h"
#include <fstream>

// Comand to run it: g++ main.cpp Graph.cpp -o main.exe
// ./main.exe < ../src/inputFiles/test.txt

using namespace std;

float** createEmptyMatrix(int);
void printMatrix(float**, int);
float** floydWarshall(Graph);
float** getCopyOfMatrix(float**, int);
void dijkstra(Graph);
void matrixToFile(float**, int, string);
void dijkstraWrapper(const Graph&);

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

    // cout << "Dijkstra:" << endl;
    // dijkstra(graph);
    matrixToFile(allPairs, numNodes, "Floyd-Warshall.txt");
     
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

void dijkstra(Graph graph) {
    int n = graph.getNumNodes();
    float** weightMatrix = graph.getWeightMatrix();

    for (int source = 0; source < n; ++source) {
        vector<float> distance(n, numeric_limits<float>::infinity());
        vector<int> previous(n, -1);
        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

        distance[source] = 0;
        pq.push(make_pair(0, source));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < n; ++v) {
                if (weightMatrix[u][v] > 0) {
                    float newDistance = distance[u] + weightMatrix[u][v];
                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        previous[v] = u;
                        pq.push(make_pair(distance[v], v));
                    }
                }
            }
        }

        for (int destination = 0; destination < n; ++destination) {
            if (destination != source) {
                cout << "node " << (source + 1) << " to node " << (destination + 1) << " : " << distance[destination] << endl;
            }
        }
    }
}

void dijkstraWrapper(const Graph& graph) {
    dijkstra(graph);
}

int outputToFile(const Graph& graph, const char* outputFileName, void (*algorithmFunction)(const Graph&)) {
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "Error al abrir el archivo " << outputFileName << endl;
        return 1;
    }

    
    streambuf* originalCoutStream = cout.rdbuf(); 
    cout.rdbuf(outputFile.rdbuf()); 

    
    algorithmFunction(graph);

    cout.rdbuf(originalCoutStream); 

    outputFile.close(); 

    return 0;
}

void matrixToFile(float** matrix, int numNodes, string fileName) {
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

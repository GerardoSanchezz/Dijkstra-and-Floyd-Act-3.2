#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include "Graph.h"

using namespace std;

float** createEmptyMatrix(int);
void printMatrix(float**, int);
float** floydWarshall(Graph);
float** getCopyOfMatrix(float**, int);

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
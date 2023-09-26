#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"

using namespace std;

float** createGraph(int, int);
float** createMatrix(int);
void fillMatrix(float**&, int, int);
void setMatrixToDefault(float**&, int);
void printMatrix(float**, int, int);
float** floydWarshall(float**, int);

int main() {

    int numNodes = 0;
    int numEdges = 0;
    cout << "Number of nodes: ";
    cin >> numNodes;
    cout << "Number of edges: ";
    cin >> numEdges;

    float** adjMatrix = createGraph(numNodes, numEdges);
    printMatrix(adjMatrix, numNodes, numNodes);
    float** allPairs = floydWarshall(adjMatrix, numNodes);
    printMatrix(allPairs, numNodes, numNodes);
        
    return 0;
}

float** createGraph(int numNodes, int numEdges) {
    float** adjMatrix = createMatrix(numNodes);
    fillMatrix(adjMatrix, numNodes, numEdges);
    return adjMatrix;
}

float** createMatrix(int numNodes) {
    float** matrix = new float*[numNodes];
    for(int i = 0; i < numNodes; i++) {
        matrix[i] = new float[numNodes];
    }
    return matrix;
}

void fillMatrix(float** &adjMatrix, int numNodes, int numEdges) {
    setMatrixToDefault(adjMatrix, numNodes);
    int i = 0;
    int j = 0;
    float weight = 0;
    for(int k = 0; k < numEdges; k++) {
        cin >> i >> j >> weight;
        adjMatrix[i-1][j-1] = weight;
    }
}

void setMatrixToDefault(float** &adjMatrix, int numNodes) {
    float Inf = numeric_limits<float>::infinity();  
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            adjMatrix[i][j] = Inf;
        }
        adjMatrix[i][i] = 0;
    }
}

void printMatrix(float** matrix, int rows, int columns) {
    cout << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

float** floydWarshall(float** weightMatrix, int numNodes) {
    float*** D = new float**[numNodes+1];
    D[0] = weightMatrix;
    for(int k = 1; k < numNodes+1; k++) {
        D[k] = createMatrix(numNodes);
        for(int i = 0; i < numNodes; i++) {
            for(int j = 0; j < numNodes; j++) {
                D[k][i][j] = min(D[k-1][i][j], D[k-1][i][k] + D[k-1][k][j]);
            }
        }
    }
    return D[numNodes];
}
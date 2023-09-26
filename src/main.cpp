#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float** createGraph(int, int);
void fillGraph(float**&, int);
void printMatrix(float**, int, int);

int main() {

    int numNodes = 0;
    int numEdges = 0;
    cout << "Number of nodes: ";
    cin >> numNodes;
    cout << "Number of edges: ";
    cin >> numEdges;

    float** adjMatrix = createGraph(numNodes, numEdges);
        
    return 0;
}

float** createGraph(int numNodes, int numEdges) {
    float** adjMatrix = new float*[numNodes];
    for(int i = 0; i < numNodes; i++) {
        adjMatrix[i] = new float[numNodes];
    }
    fillGraph(adjMatrix, numEdges);
    return adjMatrix;
}

void fillGraph(float** &adjMatrix, int numEdges) {
    int i = 0;
    int j = 0;
    float weight = 0;
    for(int k = 0; k < numEdges; k++) {
        cin >> i >> j >> weight;
        adjMatrix[i][j] = weight;
    }
}

void printMatrix(float** matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}
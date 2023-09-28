#include "graph.h"
#include <iostream>
#include <limits>

using namespace std;

Graph::Graph(int numNodes, int numEdges) {
    this->numNodes = numNodes;
    this->numEdges = numEdges;
    createMatrix();
    setMatrixToDefault();
}

int Graph::getNumNodes() {
    return this->numNodes;
}

int Graph::getNumEdges() {
    return this->numEdges;
}

float** Graph::getWeightMatrix() {
    return this->weightMatrix;
}
       
void Graph::createMatrix() {
    this->weightMatrix = new float*[this->numNodes];
    for(int i = 0; i < this->numNodes; i++) {
        this->weightMatrix[i] = new float[this->numNodes];
    }
}
       
void Graph::setMatrixToDefault() {
    float Inf = numeric_limits<float>::infinity();  
    for(int i = 0; i < this->numNodes; i++) {
        for(int j = 0; j < this->numNodes; j++) {
            this->weightMatrix[i][j] = Inf;
        }
        this->weightMatrix[i][i] = 0;
    }
}

void Graph::fillMatrix() {
    int i = 0;
    int j = 0;
    float weight = 0;
    for(int k = 0; k < this->numEdges; k++) {
        cin >> i >> j >> weight;
        this->weightMatrix[i][j] = weight;
    }
}
#include <iostream>
using namespace std;
#include "graph.h"
#include <climits>

// Dijkstra's algorithm 
// Complexity: O(n^2)

Graph::Graph(int n) : numNodes(n) {
    adjacencyMatrix.resize(n, std::vector<int>(n, -1));
}

int main() {
    int n;
    cout << "Num of nodes: ";
    cin >> n;

    Graph graph(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            cin >> weight;
            graph.addArc(i, j, weight);
        }
    }

    for (int i = 0; i < n; ++i) {
        graph.dijkstra(i); // Llama a dijkstra en el contexto del objeto graph
    }

    return 0;
}


// Función para encontrar el vértice con la distancia mínima no incluido en el conjunto S
int findMinDistance(vector<int>& distance, vector<bool>& visited, int n) {
    int minDist = INT_MAX;
    int minIndex = -1;
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && distance[i] < minDist) {
            minDist = distance[i];
            minIndex = i;
        }
    }
    
    return minIndex;
}

// Función para imprimir el resultado en el formato deseado
void printDijkstra(vector<int>& distance, int n, int startNode) {
    
    for (int i = 0; i < n; ++i) {
        if (i != startNode) {
            cout << "node " << startNode + 1 << " to node " << i + 1 << " : " << distance[i] << endl;
        }
    }
}

// Función para implementar el algoritmo de Dijkstra
void Graph::dijkstra(int startNode) { // Cambia el tipo del parámetro
    int n = numNodes;
    vector<int> distance(n, INT_MAX);
    vector<bool> visited(n, false);
    
    distance[startNode] = 0;
    
    for (int count = 0; count < n - 1; ++count) {
        int u = findMinDistance(distance, visited, n);
        visited[u] = true;
        
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && adjacencyMatrix[u][v] != -1 && distance[u] != INT_MAX && (distance[u] + adjacencyMatrix[u][v] < distance[v])) {
                distance[v] = distance[u] + adjacencyMatrix[u][v];
            }
        }
    }
    
    printDijkstra(distance, n, startNode);
}


void Graph::addArc(int nodoOrigen, int nodoDestino, int weight) {
    if (nodoOrigen >= 0 && nodoOrigen < numNodes && nodoDestino >= 0 && nodoDestino < numNodes) {
        adjacencyMatrix[nodoOrigen][nodoDestino] = weight;
    }
}



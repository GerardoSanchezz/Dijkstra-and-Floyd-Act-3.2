#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Graph {
    int numNodes;
    std::vector<std::vector<int>> adjacencyMatrix;

    Graph(int n);

    void dijkstra(int startNode); // Cambia el tipo del parámetro

    void addArc(int nodoOrigen, int nodoDestino, int weight); // Cambia el nombre del parámetro

    void printDijkstra(vector<int>& distance, int n, int startNode);

};

#endif 

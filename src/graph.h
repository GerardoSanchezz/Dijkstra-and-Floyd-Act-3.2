#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Node {
    int vertex;
    int distance;

    Node(int v, int d) : vertex(v), distance(d) {}

    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

void printDijkstra(std::vector<int>& distance, int n, int startNode);
void dijkstra(std::vector<std::vector<int>>& graph, int startNode);

#endif

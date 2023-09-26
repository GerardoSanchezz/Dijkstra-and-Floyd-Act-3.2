#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"

using namespace std;

// Gerardo Ulises Sanchez Felix - A01641788
// Alan Antonio Ruelas Robles - A01641426


void readData(vector<vector<int>>& graph);

/*
 The time complexity of Dijkstra's algorithm using a priority queue (min-heap) is O(E + V log V), where:
 ---- E is the number of edges in the graph.
 ---- V is the number of vertices (nodes) in the graph.

 The space complexity is O(V + E) because we need to store the graph
  in an adjacency list or matrix O(V + E), and we also use additional 
 data structures for distance and priority queue O(V).
*/
void dijkstraResult(vector<vector<int>>& graph);

int main() {

    vector<vector<int>> graph; 

    readData(graph);

    cout << endl;

    cout << "Dijkstra:" << endl;

    dijkstraResult(graph);

    return 0;
}

void readData(vector<vector<int>>& graph) {
    int n;
    cin >> n;  

    graph.resize(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j){
            cin >> graph[i][j];
        }
    }
}


void printDijkstra(vector<int>& distance, int n, int startNode) {

    for (int i = 0; i < n; ++i) {
        if (i != startNode) {
            cout << "node " << startNode + 1 << " to node " << i + 1 << " : " << distance[i] << endl;
        }
    }
}

void dijkstra(vector<vector<int>>& graph, int startNode) {
    int n = graph.size();
    vector<int> distance(n, INT_MAX);
    vector<bool> visited(n, false);

    distance[startNode] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(startNode, 0));

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] != -1 && (distance[u] + graph[u][v] < distance[v])) {
                distance[v] = distance[u] + graph[u][v];
                pq.push(Node(v, distance[v]));
            }
        }
    }

    printDijkstra(distance, n, startNode);
}



void dijkstraResult(vector<vector<int>>& graph){
    for (int i = 0; i < graph.size(); ++i) {
        dijkstra(graph, i);
    }
}
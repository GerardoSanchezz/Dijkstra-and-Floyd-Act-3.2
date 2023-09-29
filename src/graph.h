#ifndef GRAPH_H
#define GRAPH_H
class Graph {
    private:
        int numNodes;
        int numEdges;
        float** weightMatrix;

    public:
        Graph(int, int);
        int getNumNodes();
        int getNumEdges();
        float** getWeightMatrix();
        void createMatrix();
        void setMatrixToDefault();
        void fillMatrix();

};

#endif

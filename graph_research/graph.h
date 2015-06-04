#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

class Graph
{
public:
    Graph();

    void addNode(Node node);
    void setNodes(QMap<int, Node> nodes);
    void exportNodes(QStringList lines);
    void exportEdges(QStringList lines);
    void algorithm();
    double computeWeight(Node node, double curWeight, int k);

    Node getNode(int id);
    QMap<int, Node> getNodes();
    int getNodesCount();

private:
    QMap<int, Node> nodes;
    int nodesCount;
    int depth;
};

#endif // GRAPH_H

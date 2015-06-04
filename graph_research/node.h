#ifndef NODE_H
#define NODE_H

#include <QMap>
#include "edge.h"

class Node
{
public:
    Node();
    Node(int id, QString label);

    void addEdge(Edge edge);
    void setWeight(double weight);

    int getId();
    QString getLabel();
    Edge getEdge(int id);
    QMap<int, Edge> getEdges();
    double getWeight();
    void computeEdgesWeight();
    double getEdgesWeight();

private:
    int id;
    QString label;
    double weight;
    QMap<int, Edge> edges;
    double edgesWeight;
};

#endif // NODE_H

#include "node.h"


Node::Node()
{

}

Node::Node(int id, QString label)
{
    this->id = id;
    this->label = label;
    weight = 0;
    edgesWeight = 0;
}

int Node::getId()
{
    return id;
}

QString Node::getLabel()
{
    return label;
}

Edge Node::getEdge(int id)
{
    return edges[id];
}

QMap<int, Edge> Node::getEdges()
{
    return edges;
}


double Node::getWeight()
{
    return weight;
}

void Node::addEdge(Edge edge)
{
    edges[edge.getId()] = edge;
}

void Node::setWeight(double weight)
{
    this->weight = weight;
}

void Node::computeEdgesWeight()
{
    QMap<int, Edge> edges = getEdges();
    QMap<int, Edge>::iterator i;
    for(i = edges.begin(); i != edges.end(); i++)
    {
        edgesWeight += i.value().getWeight();
    }
}

double Node::getEdgesWeight()
{
    return edgesWeight;
}

#include "graph.h"
#include <QStringList>

Graph::Graph()
{
    depth = 3;
}

void Graph::exportNodes(QStringList lines)
{
    int id;
    QString label;

    if(lines.size() <= 1)
        return;

    for(int i = 1; i < lines.size(); i++)
    {
        // parse line
        QStringList line = lines[i].split(",");
        bool ok;
        id = line[0].toInt(&ok, 10);
        label = line[1];
        nodes.insert(id, Node(id, label));
        nodes[id].computeEdgesWeight();
    }
}

void Graph::exportEdges(QStringList lines)
{
    int id, sourceId, targetId;
    QString source, target;
    double weight;

    if(lines.size() <= 1)
        return;

    for(int i = 1; i < lines.size(); i++)
    {
        // parse line
        QStringList line = lines[i].split(",");
        bool ok;
        sourceId = line[0].toInt(&ok, 10);
        targetId = line[1].toInt(&ok, 10);
        id = line[3].toInt(&ok, 10);
        source = nodes[sourceId].getLabel();
        target = nodes[targetId].getLabel();
        weight = line[5].toDouble(&ok);
        // add edge to node
        Edge edge = Edge(id, sourceId, targetId, weight);
        edge.setSource(source);
        edge.setTarget(target);
        nodes[sourceId].addEdge(edge);
    }
}

void Graph::algorithm()
{
    QMap<int, Node>::iterator i;
    for(i = nodes.begin(); i != nodes.end(); i++)
    {
        computeWeight(i.value(), 0, 1);
    }
}

double Graph::computeWeight(Node node, double curWeight, int k)
{
    QMap<int, Edge>::iterator i;

    return 1.0;
}

void Graph::addNode(Node node)
{
    nodes[node.getId()] = node;
}

void Graph::setNodes(QMap<int, Node> nodes)
{
    this->nodes = nodes;
}

Node Graph::getNode(int id)
{
    return nodes[id];
}

int Graph::getNodesCount()
{
    return nodes.size();
}

QMap<int, Node> Graph::getNodes()
{
    return nodes;
}

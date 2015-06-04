#ifndef EDGE_H
#define EDGE_H

#include <QString>

class Edge
{
public:
    Edge();
    Edge(int id, int sourceId, int targetId, int weight);

    int getId();
    int getSourceId();
    int getTargetId();
    QString getSource();
    QString getTarget();
    int getWeight();

    void setSource(QString source);
    void setTarget(QString target);

private:
    int id;
    int sourceId;
    int targetId;
    QString source;
    QString target;
    int weight;
};

#endif // EDGE_H

#include "edge.h"

Edge::Edge()
{

}

Edge::Edge(int id, int sourceId, int targetId, int weight)
{
    this->id = id;
    this->sourceId = sourceId;
    this->targetId = targetId;
    this->weight = weight;
}

int Edge::getId()
{
    return this->id;
}

int Edge::getSourceId()
{
    return this->sourceId;
}

int Edge::getTargetId()
{
    return this->targetId;
}

QString Edge::getSource()
{
    return this->source;
}

QString Edge::getTarget()
{
    return this->target;
}

int Edge::getWeight()
{
    return this->weight;
}

void Edge::setSource(QString source)
{
    this->source = source;
}

void Edge::setTarget(QString target)
{
    this->target = target;
}

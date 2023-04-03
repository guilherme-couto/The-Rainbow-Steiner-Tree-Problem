#include "Edge.hpp"


Edge::Edge(int target_id, int target_position)
{
    this->_target_id = target_id;
    this->_weight = 0;
    this->_color = -1;
    this->_next_edge = nullptr;
    this->_target_position = target_position;
}

Edge::~Edge()
{
    // delete automático
}

int Edge::target_id()
{
    return this->_target_id;
}

int Edge::target_position()
{
    return this->_target_position;
}

int Edge::weight()
{
    return this->_weight;
}

int Edge::color()
{
    return this->_color;
}

std::shared_ptr<Edge> Edge::next_edge()
{
    return this->_next_edge;
}

void Edge::set_next_edge(std::shared_ptr<Edge> edge)
{
    this->_next_edge = edge;
}

void Edge::set_weight(int weight)
{
    this->_weight = weight;
}

void Edge::set_color(int color)
{
    this->_color = color;
}

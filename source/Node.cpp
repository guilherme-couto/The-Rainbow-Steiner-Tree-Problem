#include "Node.hpp"


Node::Node(int id)
{
    this->_first_edge = nullptr;
    this->_last_edge = nullptr;
    this->_next_node = nullptr;

    this->_id = id;
    this->_position = 0;
    this->_in_degree = 0;
    this->_out_degree = 0;
    this->_degree = 0;
    this->_visited = false;
    this->_terminal = false;
}

Node::~Node()
{
    // delete automático agora
}

std::shared_ptr<Edge> Node::first_edge()
{
    return this->_first_edge;
}

std::shared_ptr<Edge> Node::last_edge()
{
    return this->_last_edge;
}

std::shared_ptr<Node> Node::next_node()
{
    return this->_next_node;
}

std::shared_ptr<Edge> Node::edge_for(int target_id)
{
    if(this->_first_edge != nullptr)
    {
        for(std::shared_ptr<Edge> aux_edge = this->first_edge(); aux_edge != nullptr; aux_edge = aux_edge->next_edge())
        {
            if(aux_edge->target_id() == target_id)
            {
                return aux_edge;
            }
        }
    }
    return nullptr;
}

int Node::id()
{
    return this->_id;
}

int Node::in_degree()
{
    return this->_in_degree;
}

int Node::out_degree()
{
    return this->_out_degree;
}

int Node::degree()
{
    this->_degree = this->_in_degree + this->_out_degree;

    return this->_degree;
}

bool Node::terminal()
{
    return this->_terminal;
}

int Node::remove_edge(int id, bool directed, std::shared_ptr<Node> target_node)
{
    return -1;
}

int Node::position()
{
    return this->_position;
}

bool Node::has_edge_for(int target_id)
{
    if(this->_first_edge != nullptr)
    {
        for(std::shared_ptr<Edge> aux_edge = this->first_edge(); aux_edge != nullptr; aux_edge = aux_edge->next_edge())
        {
            if(aux_edge->target_id() == target_id)
            {
                return true;
            }
        }
    }
    return false;
}

void Node::set_next_node(std::shared_ptr<Node> node)
{
    this->_next_node = node;
}

void Node::insert_edge(int target_id, int target_position, int weight, int color)
{
    std::shared_ptr<Edge> edge(new Edge(target_id, target_position));
    edge->set_weight(weight);
    edge->set_color(color);
    if(this->first_edge() != nullptr)
    {
        this->_last_edge->set_next_edge(edge);
        this->_last_edge = edge;
    }
    else
    {
        this->_first_edge = edge;
        this->_last_edge = this->_first_edge;
    }

    this->_degree++;
}

void Node::cleanse()
{
    
}

void Node::increase_out_degree()
{
    this->_out_degree += 1;
}

void Node::increase_in_degree()
{
    this->_in_degree += 1;
}

void Node::decrease_out_degree()
{
    this->_out_degree -= 1;
}

void Node::decrease_in_degree()
{
    this->_in_degree -= 1;
}

void Node::set_position(int position)
{
    this->_position = position;
}

void Node::set_visited(bool visited)
{
    this->_visited = visited;
}

void Node::is_terminal(bool terminal)
{
    this->_terminal = terminal;
}
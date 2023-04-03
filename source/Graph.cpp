#include "Graph.hpp"
#include "random/Xoshiro256plus.h"

Graph::Graph()
{
    this->_order = 0;
    this->position = 0;
    this->_number_of_edges = 0;
    this->_number_of_terminals = 0;
    this->_first_node = nullptr;
    this->_last_node = nullptr;
}

Graph::~Graph()
{
    // delete automático
    // a não ser que aloquemos alguma outra coisa na construção
}

int Graph::order()
{
    return this->_order;
}

int Graph::number_of_edges()
{
    return this->_number_of_edges;
}

int Graph::number_of_terminals()
{
    return this->_number_of_terminals;
}

std::shared_ptr<Node> Graph::first_node()
{
    return this->_first_node;
}

std::shared_ptr<Node> Graph::last_node()
{
    return this->_last_node;
}

void Graph::insert_node(int id)
{
    if (this->first_node() == nullptr)
    {
        std::shared_ptr<Node> node(new Node(id));
        this->_first_node = this->_last_node = node;
        node->set_position(this->position);
    }
    else
    {
        if (!this->search_node(id))
        {
            std::shared_ptr<Node> node(new Node(id));
            this->last_node()->set_next_node(node);
            this->_last_node = node;
            node->set_position(this->position);
        }
        else
        {
            return;
        }
    }
    this->position += 1;
    this->increment_graph_order();
}

void Graph::insert_edge(int id, int target_id, int weight, int color)
{
    std::shared_ptr<Node> node, taget_node;

    node = this->node(id);
    taget_node = this->node(target_id);

    // Check if nodes already exist. If they don't, then insert
    // if (node == nullptr)
    //     this->insert_node(id);

    // if (taget_node == nullptr)
    //     this->insert_node(target_id);

    // If edge doesn't exist, insert
    if (!node->has_edge_for(target_id))
    {
        this->_number_of_edges++;

        node->insert_edge(target_id, taget_node->position(), weight, color);
        taget_node->insert_edge(id, node->position(), weight, color);

        node->increase_in_degree();
        node->increase_out_degree();
        taget_node->increase_in_degree();
        taget_node->increase_out_degree();

        bool tag = false;
        vector<int>::iterator it;

        it = find(this->_used_colors.begin(), this->_used_colors.end(), color);

        // if color isnt in the vector, count it
        if (it == this->_used_colors.end())
        {
            this->_diff_colors.push_back(color);
            tag = true;
        }
        if (tag)
        {
            this->num_diff_colors++;
        }

        this->_used_colors.push_back(color);
    }
}

bool Graph::search_node(int id)
{
    std::shared_ptr<Node> node = this->node(id);

    if (node == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::shared_ptr<Node> Graph::node(int id)
{
    std::shared_ptr<Node> helper = this->_first_node;

    while (helper != nullptr)
    {
        if (helper->id() == id)
        {
            return helper;
        }
        else
        {
            helper = helper->next_node();
        }
    }

    return nullptr;
}

std::shared_ptr<Node> Graph::node_pos(int pos)
{
    std::shared_ptr<Node> helper = this->_first_node;

    while (helper != nullptr)
    {
        if (helper->position() == pos)
        {
            return helper;
        }
        else
        {
            helper = helper->next_node();
        }
    }

    return nullptr;
}

void Graph::set_terminal(int id)
{
    std::shared_ptr<Node> node = this->node(id);
    node->is_terminal(true);
    this->_number_of_terminals++;
}

void Graph::increment_graph_order()
{
    this->_order += 1;
}

void Graph::greedy()
{
    //cout << "Prim's original solution" << endl;
    std::shared_ptr<Solution> sol = this->prim(this->graph_matrix);
    //sol->print();
    this->c_solution = sol;
    // this->best_solution = sol;

    shared_ptr<Solution> penalized_sol = this->penalty(sol, this->graph_matrix);
    /* cout << "\nBest penalized solution" << endl;
    penalized_sol->print(); */

    if (penalized_sol->getNumColors() <= sol->getNumColors())
    {
        if (penalized_sol->getNumColors() == sol->getNumColors())
        {
            if (penalized_sol->getCost() < sol->getCost())
            {
                this->c_solution = penalized_sol;
            }
        }
        else
        {
            this->c_solution = penalized_sol;
        }
    }
}

std::shared_ptr<Solution> Graph::prim(std::vector<std::vector<long int>> matrix)
{
    std::vector<long int> key;
    std::vector<bool> mstSet;
    std::vector<int> inserted_colors;

    int parent[this->_order];

    key.reserve(this->_order);
    mstSet.reserve(this->_order);

    for (size_t i = 0; i < this->_order; i++)
    {
        key.push_back(INT16_MAX);
        mstSet.push_back(false);
    }

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key.at(0) = 0;
    parent[0] = -1;

    // The MST will have V vertices
    for (size_t i = 0; i < this->_order - 1; i++)
    {
        int u = this->minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST

        for (size_t j = 0; j < this->_order; j++)
        {
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]

            if (matrix[u][j] != 0 && mstSet[j] == false && matrix[u][j] < key[j])
            {
                parent[j] = u;
                key[j] = matrix[u][j];
            }
        }
    }

    /*
    std::cout<<"Edge \tWeight \tColor\n";

    for (size_t i = 1; i < this->order(); i++)
    {
        std::cout<<""<<parent[i] + 1<<" - "<<""<<i+1<<" \t"<<matrix[i][parent[i]]<<" \t"<<this->node_pos(parent[i])->edge_for(i+1)->color()<<"\n";
    }
    */

    vector<NodeEdgeNode> used_nodes = this->vector_to_NEN(parent);
    shared_ptr<Solution> sol(new Solution(used_nodes));
    return sol;
}

std::shared_ptr<Solution> Graph::penalty(std::shared_ptr<Solution> original_sol, std::vector<std::vector<long int>> original_matrix)
{
    Xoshiro256plus rand(time(NULL));
    vector<int> prob{1, 1, 1, 1, 1, 1, 1, 1, 0, 0}; // 80%

    std::shared_ptr<Solution> aux = original_sol;
    std::shared_ptr<Solution> best_penalized = aux;
    std::vector<std::vector<long int>> matrix = original_matrix;
    int count = 0;

    do
    {
        count++;

        int most_repeated_color = aux->getMostRepeatedColor();
        for (size_t i = 0; i < aux->solution().size(); i++)
        {
            if (aux->solution()[i].color == most_repeated_color)
            {
                int random_number = rand.next() % prob.size();
                if (prob[random_number] == 1)
                {
                    int source_pos = aux->solution()[i].id_source - 1;
                    int target_pos = aux->solution()[i].id_target - 1;
                    matrix[source_pos][target_pos] = matrix[source_pos][target_pos] * 2; // penalty
                    matrix[target_pos][source_pos] = matrix[target_pos][source_pos] * 2; // penalty
                }
            }
        }

        aux = this->prim(matrix);
        if (count == 1)
        {
            best_penalized = aux;
        }

        if (aux->getNumColors() < best_penalized->getNumColors())
        {
            best_penalized = aux;
        }
        // matrix = original_matrix;
    } while (count < 30);

    return best_penalized;
}

vector<NodeEdgeNode> Graph::vector_to_NEN(int *mst)
{
    vector<NodeEdgeNode> to_return;
    int nencounts = 0;

    for (size_t i = 1; i < this->order(); i++)
    {
        std::shared_ptr<Edge> edge = this->node_pos(mst[i])->edge_for(i + 1);
        NodeEdgeNode nen;
        nen.id_source = mst[i] + 1; // ID
        nen.id_target = i + 1;      // ID
        nen.source_terminal = this->node_pos(mst[i])->terminal();
        nen.target_terminal = this->node_pos(i)->terminal();
        nen.edge = edge;
        nen.weight = edge->weight();
        nen.color = edge->color();

        nencounts++;
        to_return.push_back(nen);
    }
    return to_return;
}

void Graph::create_adjacency_matrix()
{
    std::vector<std::vector<long int>> matrix(this->_order, std::vector<long int>(this->_order));

    this->graph_matrix = matrix;

    for (size_t i = 0; i < this->_order; i++)
    {
        // inicializar a matrix representativa do grafo com G[i][j] = peso
        for (size_t j = 0; j < this->_order; j++)
        {
            if (j == i)
            {
                this->graph_matrix.at(i).at(j) = 0;
            }
            else
            {
                long int cost;
                if (this->node_pos(i)->edge_for(j + 1) != nullptr)
                {
                    cost = this->node_pos(i)->edge_for(j + 1)->weight();
                }
                else
                {
                    cost = 0;
                }

                this->graph_matrix.at(i).at(j) = cost;
            }
        }
    }

    this->create_color_matrix();
}

void Graph::print_adjacency_matrix()
{
    for (size_t i = 0; i < this->_order; i++)
    {
        // inicializar a matrix representativa do grafo com G[i][j] = peso
        std::cout << "Line " << i << ": ";
        for (size_t j = 0; j < this->_order; j++)
        {
            if (this->graph_matrix.at(i).at(j) != 0)
                std::cout << this->graph_matrix.at(i).at(j) << " ";
            else
                std::cout << "-"
                          << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::create_color_matrix()
{
    std::vector<std::vector<int>> sss(this->_order, std::vector<int>(this->_order));

    this->colors_matrix = sss;

    for (size_t i = 0; i < this->_order; i++)
    {
        // inicializar a matrix representativa do grafo com G[i][j] = peso
        for (size_t j = 0; j < this->_order; j++)
        {
            if (j == i)
            {
                this->colors_matrix.at(i).at(j) = 0;
            }
            else
            {
                int color;
                if (this->node_pos(i)->edge_for(j + 1) != nullptr)
                {
                    color = this->node_pos(i)->edge_for(j + 1)->color();
                }
                else
                {
                    color = 0;
                }

                this->colors_matrix.at(i).at(j) = color;
            }
        }
    }
}

void Graph::print_color_matrix()
{
    for (size_t i = 0; i < this->_order; i++)
    {
        // inicializar a matrix representativa do grafo com G[i][j] = peso
        std::cout << "Line " << i << ": ";
        for (size_t j = 0; j < this->_order; j++)
        {
            if (colors_matrix.at(i).at(j) != 0)
                std::cout << this->colors_matrix.at(i).at(j) << " ";
            else
                std::cout << "-"
                          << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<long int>> Graph::get_graph_matrix()
{
    return this->graph_matrix;
}

int Graph::minKey(std::vector<long int> key, std::vector<bool> mstSet)
{
    // Initialize min value
    int min = INT16_MAX, min_index;

    for (int v = 0; v < this->_order; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

std::vector<int> Graph::used_colors()
{
    return this->_used_colors;
}

std::vector<int> Graph::diff_colors()
{
    return this->_diff_colors;
}
std::vector<int> Graph::colors_freq()
{
    return this->_colors_freq;
}

void Graph::calculate_colors_freq()
{
    // each different color will be associated with its frequency by its index in _diff_colors
    for (size_t i = 0; i < this->_diff_colors.size(); i++)
    {
        int color = this->_diff_colors[i];
        int frequency = count(this->_used_colors.begin(), this->_used_colors.end(), color);
        this->_colors_freq.push_back(frequency);
    }
    int most_repeated_color_index = max_element(this->_colors_freq.begin(), this->_colors_freq.end()) - this->_colors_freq.begin();
    this->most_repeated_color = this->_diff_colors[most_repeated_color_index];
}

int Graph::getMostRepeatedColor()
{
    return this->most_repeated_color;
}

int Graph::getNumColors()
{
    return this->num_diff_colors;
}

void Graph::destructor_constructor()
{
    this->best_solution = this->c_solution;
    int current_size = this->c_solution->solution().size();

    shared_ptr<Solution> temp = this->c_solution;
    int c = 0;
    do
    {

        this->c_solution->nonTerminalsPruning();
        if (this->c_solution->solution().size() < current_size)
        {
            current_size = this->c_solution->solution().size();
            c++;
        }
    } while (this->c_solution->solution().size() < current_size);

    int d = 0;
    this->best_solution = this->c_solution;
    std::shared_ptr<Solution> sol_temp = this->c_solution;

    while (this->c_solution->getNumColorsRepeated() != 0)
    {   
        d++;

        this->c_solution->colorPruning();
        this->c_solution->benefactorMatrix(this->graph_matrix, this->colors_matrix);
        this->c_solution->reconnect(this->graph_matrix, this->colors_matrix);
    }
    
    cout << "\nSolution after reconnection" << endl;
    this->c_solution->print();
    this->best_solution = this->c_solution;
    std::cout<<"Number of iterations: "<<d<<std::endl;
}

std::shared_ptr<Solution> Graph::get_best_solution()
{
    return this->best_solution;
}
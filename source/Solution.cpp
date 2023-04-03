#include "Solution.hpp"
#include <set>
#include "helpers.hpp"
#include "random/Xoshiro256plus.h"

using namespace std;

Solution::Solution(vector<NodeEdgeNode> used)
{
    this->_solution = used;
    this->num_diff_colors = this->cost = this->_num_of_colors_repeated = 0;
    this->original_size = used.size();
    /* this->calculate_diff_colors();
    this->calculate_cost();
    this->calculate_colors_freq(); */

    for (size_t i = 0; i < this->_solution.size() + 1; i++)
    {
        this->_nodes_degree.push_back(0); // initialize each node degree with 0
    }

    this->calculate_all_params();
}

unsigned Solution::getNumColors()
{
    return this->num_diff_colors;
}

unsigned Solution::getCost()
{
    return this->cost;
}

int Solution::getMostRepeatedColor()
{
    return this->most_repeated_color;
}

std::vector<int> Solution::used_colors()
{
    return this->_used_colors;
}

std::vector<int> Solution::diff_colors()
{
    return this->_diff_colors;
}

std::vector<int> Solution::colors_freq()
{
    return this->_colors_freq;
}

std::vector<NodeEdgeNode> Solution::solution()
{
    return this->_solution;
}

void Solution::print()
{
    cout << "\nSolution:\n"
         << endl;
    std::cout << "\t\tSource\t\tTarget\t\tWeight\t\tColor" << std::endl;
    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        std::cout << "\t\t" << this->_solution.at(i).id_source << "\t\t" << this->_solution.at(i).id_target << "\t\t" << this->_solution.at(i).weight
                  << "\t\t" << this->_solution.at(i).color << std::endl;
    }

    std::cout << "\nSolution cost: " << this->cost << std::endl;
    std::cout << "Number of different colors: " << this->num_diff_colors << std::endl;
    cout << "Number of colors repeated: " << this->_num_of_colors_repeated << endl;

    /* for (size_t i = 0; i < this->_nodes_degree.size(); i++)
    {
        cout << "Node " << i+1 << " has degree " << this->_nodes_degree[i] << endl;
    } */
}

void Solution::calculate_diff_colors()
{
    int count = 0;
    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        int color = this->_solution.at(i).color;
        vector<int>::iterator it;

        it = find(this->_used_colors.begin(), this->_used_colors.end(), color);

        // if color isnt in the vector, count it
        if (it == this->_used_colors.end())
        {
            count++;
            this->_diff_colors.push_back(color);
        }
        this->_used_colors.push_back(color);
    }
    this->num_diff_colors = count;
}

void Solution::calculate_cost()
{
    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        this->cost += this->_solution.at(i).weight;
    }
}

void Solution::calculate_colors_freq()
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

    /* cout << "colors freq: ";
    for (size_t i = 0; i < this->_colors_freq.size(); i++)
    {
        cout << _colors_freq[i] << "   ";
    }
    cout << "\nmax element: " << *max_element(this->_colors_freq.begin(), this->_colors_freq.end()) << endl;
    cout << "max element index: " << max_element(this->_colors_freq.begin(), this->_colors_freq.end()) - this->_colors_freq.begin() << endl; */
}

void Solution::erase_duplicated_edges()
{
    std::vector<int> duplicated;
    std::vector<NodeEdgeNode> temp;

    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        for (size_t j = i + 1; j < this->_solution.size(); j++)
        {
            // if((this->_solution.at(i).color == this->_solution.at(j).color) && (this->_solution.at(i).source_terminal == this->_solution.at(j).target_terminal) &&
            //(this->_solution.at(i).target_terminal == this->_solution.at(j).source_terminal))
            if ((this->_solution[i].id_source == this->_solution[j].id_source && this->_solution[i].id_target == this->_solution[j].id_target) || (this->_solution[i].id_source == this->_solution[j].id_target && this->_solution[i].id_target == this->_solution[j].id_source))
            {
                // cout << "Linha 144" << endl;
                duplicated.push_back(j);
            }
        }
    }

    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        if (is_duplicated(i, duplicated) == true)
        {
            continue;
        }
        else
        { // cout << "Linha 157" << endl;
            temp.push_back(this->_solution.at(i));
        }
    }

    this->_solution.clear();
    this->_solution = temp;
    // temp.clear();
}

vector<int> Solution::nodes_degree()
{
    return this->_nodes_degree;
}

void Solution::calculate_all_params()
{
    this->num_diff_colors = this->cost = this->_num_of_colors_repeated = 0;
    this->_used_colors.clear();
    this->_diff_colors.clear();
    this->_nodes_degree.clear();
    this->_colors_freq.clear();
    this->erase_duplicated_edges();

    for (size_t i = 0; i < this->original_size + 1; i++)
    {
        this->_nodes_degree.push_back(0); // initialize each node degree with 0
    }

    int c = 0;
    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        // calculate cost
        this->cost += this->_solution.at(i).weight;

        // calculate diff_color
        int color = this->_solution.at(i).color;
        vector<int>::iterator it;
        it = find(this->_used_colors.begin(), this->_used_colors.end(), color);

        // if color isnt in the vector, count it
        if (it == this->_used_colors.end())
        {
            c++;
            this->_diff_colors.push_back(color);
        }
        this->_used_colors.push_back(color);

        // calculate nodes_degree
        int source_pos = this->_solution.at(i).id_source - 1;
        int target_pos = this->_solution.at(i).id_target - 1;
        this->_nodes_degree.at(source_pos)++;
        this->_nodes_degree.at(target_pos)++;
    }
    this->num_diff_colors = c;

    // calculate color_frequency
    // each different color will be associated with its frequency by its index in _diff_colors
    for (size_t i = 0; i < this->_diff_colors.size(); i++)
    {
        int color = this->_diff_colors[i];
        int frequency = count(this->_used_colors.begin(), this->_used_colors.end(), color);
        this->_colors_freq.push_back(frequency);
        if (frequency > 1)
        {
            this->_num_of_colors_repeated++; // count number of colors that repeat
        }
    }
    int most_repeated_color_index = max_element(this->_colors_freq.begin(), this->_colors_freq.end()) - this->_colors_freq.begin();
    this->most_repeated_color = this->_diff_colors[most_repeated_color_index];
    /* cout << "diff colors: ";
    for (size_t i = 0; i < this->_diff_colors.size(); i++)
    {
        cout << _diff_colors[i] << "   ";
    }
    cout << "\n\ncolors freq: ";
    for (size_t i = 0; i < this->_colors_freq.size(); i++)
    {
        cout << _colors_freq[i] << "   ";
    }
    cout << "\nmax element: " << *max_element(this->_colors_freq.begin(), this->_colors_freq.end()) << endl;
    cout << "max element index: " << max_element(this->_colors_freq.begin(), this->_colors_freq.end()) - this->_colors_freq.begin() << endl; */
}

void Solution::nonTerminalsPruning()
{
    vector<NodeEdgeNode>::iterator it = this->_solution.begin();

    /* cout << "\nSolution size before pruning: " << this->_solution.size() << endl;
    cout << "(id - grau)" << endl;
    for (size_t i = 0; i < this->_nodes_degree.size(); i++)
    {
        cout << "(" << i + 1 << " - " << this->_nodes_degree[i] << ")  ";
    } */

    while (it != this->_solution.end())
    {
        if ((*it).source_terminal == false || (*it).target_terminal == false)
        {
            if ((*it).source_terminal == false)
            {
                int source_pos = (*it).id_source - 1;
                int target_pos = (*it).id_target - 1;
                if (this->_nodes_degree.at(source_pos) == 1) // if source is a leaf
                {
                    this->_solution.erase(it);
                    this->_nodes_degree.at(source_pos)--;
                    this->_nodes_degree.at(target_pos)--;
                    it = this->_solution.begin(); // back to begin because size changed
                }
                else if (this->_nodes_degree.at(target_pos) == 1 && (*it).target_terminal == false) // if target is a leaf
                {
                    this->_solution.erase(it);
                    this->_nodes_degree.at(source_pos)--;
                    this->_nodes_degree.at(target_pos)--;
                    it = this->_solution.begin(); // back to begin because size changed
                }
                else
                {
                    it++;
                }
            }
            else
            {
                int source_pos = (*it).id_source - 1;
                int target_pos = (*it).id_target - 1;
                if (this->_nodes_degree.at(target_pos) == 1) // if target is a leaf
                {
                    this->_solution.erase(it);
                    this->_nodes_degree.at(source_pos)--;
                    this->_nodes_degree.at(target_pos)--;
                    it = this->_solution.begin(); // back to begin because size changed
                }
                else if (this->_nodes_degree.at(source_pos) == 1 && (*it).source_terminal == false) // if source is a leaf
                {
                    this->_solution.erase(it);
                    this->_nodes_degree.at(source_pos)--;
                    this->_nodes_degree.at(target_pos)--;
                    it = this->_solution.begin(); // back to begin because size changed
                }
                else
                {
                    it++;
                }
            }
        }
        else
        {
            it++;
        }
    }
    //cout << "\n\nSolution size after pruning: " << this->_solution.size() << endl;
    this->calculate_all_params();
}

int Solution::getNumColorsRepeated()
{
    return this->_num_of_colors_repeated;
}

void Solution::colorPruning()
{
    int mrc = this->most_repeated_color;
    this->make_all_in_forest_false();
    this->forest1.clear();
    this->forest2.clear();
    this->erase_duplicated_edges();


    vector<int> indexes_to_cut;
    //cout << "MOST RPT COLOR: " << most_repeated_color << endl;
    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        if (this->_solution[i].color == this->most_repeated_color)
        {
            indexes_to_cut.push_back(i);
        }
    }

    

    //for (size_t i = 0; i < this->_solution.size(); i++)
    //{
        //if (this->_solution[i].color == this->most_repeated_color)
        //{
            // PEGA ARESTA ALEATORIA DENTRE AS REPETIDAS DA COR MAIS REPETIDA
            Xoshiro256plus rand(time(NULL));
            int random_num = rand.next() % indexes_to_cut.size();
            int index2cut = indexes_to_cut[random_num];

            //PEGAR A ARESTA MAIS PESADA DENTRE AS REPETIDAS DA COR MAIS REPETIDA
            /* int max_weight = this->_solution[indexes_to_cut[0]].weight;
            int index2cut = indexes_to_cut[0];
            for (size_t a = 1; a < indexes_to_cut.size(); a++)
            {
                if (this->_solution[indexes_to_cut[a]].weight > max_weight)
                {
                    max_weight = this->_solution[indexes_to_cut[a]].weight;
                    index2cut = a;
                }
            } */
            

            int node1_id = this->_solution[index2cut].id_source;
            int node2_id = this->_solution[index2cut].id_target;
            this->_solution[index2cut].in_forest = true;
            this->edge2cut = this->_solution.begin() + index2cut;

            for (size_t j = 0; j < this->_solution.size(); j++)
            {
                int src_id = this->_solution[j].id_source;
                int trgt_id = this->_solution[j].id_target;
                if ((src_id == node1_id || trgt_id == node1_id) && !(src_id == node2_id || trgt_id == node2_id))
                {
                    this->forest1.push_back(this->_solution[j]);
                    this->_solution[j].in_forest = true;
                }
                else if ((src_id == node2_id || trgt_id == node2_id) && !(src_id == node1_id || trgt_id == node1_id))
                {
                    this->forest2.push_back(this->_solution[j]);
                    this->_solution[j].in_forest = true;
                }
            }
            if (this->forest1.size() == 0)
            {
                NodeEdgeNode nen;
                nen.id_source = -1;
                nen.id_target = node1_id;
                nen.target_terminal = this->_solution[index2cut].target_terminal;
                nen.weight = INFINITY;
                nen.color = INFINITY;
                this->forest1.push_back(nen);
            }
            if (this->forest2.size() == 0)
            {
                NodeEdgeNode nen;
                nen.id_source = -1;
                nen.id_target = node2_id;
                nen.target_terminal = this->_solution[index2cut].target_terminal;
                nen.weight = INFINITY;
                nen.color = INFINITY;
                this->forest2.push_back(nen);
            }
            //break;
        //}
    //}

    bool tag = true;
    do
    {
        for (int i = 0; i < this->_solution.size(); i++)
        {
            if (this->_solution[i].in_forest == false)
            {
                bool belong2forest1 = false;
                for (int j = 0; j < this->forest1.size(); j++)
                {
                    if (this->_solution[i].id_source == this->forest1[j].id_source || this->_solution[i].id_source == this->forest1[j].id_target || this->_solution[i].id_target == this->forest1[j].id_source || this->_solution[i].id_target == this->forest1[j].id_target)
                    {
                        this->forest1.push_back(this->_solution[i]);
                        this->_solution[i].in_forest = true;
                        belong2forest1 = true;
                        break;
                    }
                }
                if (belong2forest1 == false)
                {
                    for (int j = 0; j < this->forest2.size(); j++)
                    {
                        if (this->_solution[i].id_source == this->forest2[j].id_source || this->_solution[i].id_source == this->forest2[j].id_target || this->_solution[i].id_target == this->forest2[j].id_source || this->_solution[i].id_target == this->forest2[j].id_target)
                        {
                            this->forest2.push_back(this->_solution[i]);
                            this->_solution[i].in_forest = true;
                            break;
                        }
                    }
                }
            }
        }
        tag = false;
        for (size_t i = 0; i < this->_solution.size(); i++)
        {
            if (this->_solution[i].in_forest == false)
            {
                tag = true;
                break;
            }
        }

    } while (tag);

    // cout << "\n\n\n" << endl;
    // this->print();
    /* cout << "\n\nForest1:" << endl;
    std::cout << "\t\tSource\t\tTarget\t\tWeight\t\tColor" << std::endl;
    for (size_t i = 0; i < this->forest1.size(); i++)
    {
        std::cout << "\t\t" << this->forest1.at(i).id_source << "\t\t" << this->forest1.at(i).id_target << "\t\t" << this->forest1.at(i).weight
                  << "\t\t" << this->forest1.at(i).color << std::endl;
    }
    cout << "\n\n\nForest2:" << endl;
    std::cout << "\t\tSource\t\tTarget\t\tWeight\t\tColor" << std::endl;
    for (size_t i = 0; i < this->forest2.size(); i++)
    {
        std::cout << "\t\t" << this->forest2.at(i).id_source << "\t\t" << this->forest2.at(i).id_target << "\t\t" << this->forest2.at(i).weight
                  << "\t\t" << this->forest2.at(i).color << std::endl;
    } */
}

void Solution::benefactorMatrix(std::vector<std::vector<long int>> graph_matrix, std::vector<std::vector<int>> colors_matrix)
{
    std::vector<std::vector<long int>> matrix = graph_matrix;
    int count = graph_matrix[0].size();
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            int color = colors_matrix[i][j];
            if (color != 0)
            {
                vector<int>::iterator it;
                it = find(this->_diff_colors.begin(), this->_diff_colors.end(), color);
                if (it == this->_diff_colors.end()) // color is not in solution
                {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                }
            }
        }
    }
    this->_benefactorMatrix = matrix;
    /* cout << "\n\nmatriz\n"
         << endl;
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    } */
}

// Dijkstra Adaptation
vector<NodeEdgeNode> Solution::shortestRainbowPath(std::vector<std::vector<long int>> graph_matrix, std::vector<std::vector<int>> colors_matrix, int src_pos, int trgt_pos)
{
    //std::cout << "Linha 420" << std::endl;
    int n = this->_benefactorMatrix[0].size();
    vector<NodeEdgeNode> expanded_paths;
    expanded_paths.clear();
    vector<int> colors_in_sp;
    //std::cout << "Linha 424" << std::endl;
    int dist[n]; // The output array.  dist[i] will hold the shortest distance from src to trgt

    bool sptSet[n];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++)
    {
        dist[i] = INFINITY;
        sptSet[i] = false;
    }
    //std::cout << "Linha 435" << std::endl;
    // Distance of source vertex from itself is always 0
    dist[src_pos] = 0;
    //std::cout << "Linha 438" << std::endl;
    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++)
    {
        // Initialize min value
        int min = INFINITY;
        int min_index = -1;

        for (int v = 0; v < n; v++)
        {
            if (sptSet[v] == false && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }
        }

        int u = min_index;
        if (u == trgt_pos)
        {
            break;
        }

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < n; v++)
        {
            if (!sptSet[v] && this->_benefactorMatrix[u][v] && dist[u] != INFINITY && dist[u] + this->_benefactorMatrix[u][v] < dist[v])
            {
                vector<int>::iterator it;
                int color = colors_matrix[u][v];
                it = find(colors_in_sp.begin(), colors_in_sp.end(), color);

                if (it == colors_in_sp.end())
                {
                    dist[v] = dist[u] + this->_benefactorMatrix[u][v];
                    colors_in_sp.push_back(color);

                    NodeEdgeNode nen;
                    nen.id_source = u + 1;
                    nen.id_target = v + 1;
                    nen.weight = graph_matrix[u][v];
                    nen.color = color;
                    expanded_paths.push_back(nen);
                }
            }
        }
    }
    /* std::cout << "Linha 488" << std::endl;
    cout << "\n\nExpanded path\n";
    cout << "target id: " << trgt_pos + 1 << endl;
    for (size_t i = 0; i < expanded_paths.size(); i++)
    {
        cout << "(" << expanded_paths[i].id_source << ", " << expanded_paths[i].id_target << ") ";
    }
    cout << "\n\n"; */

    int trgt_index_in_exp_paths = -1;
    for (int i = expanded_paths.size() - 1; i >= 0; i--)
    {
        if (expanded_paths[i].id_target == trgt_pos + 1)
        {
            trgt_index_in_exp_paths = i;
            break;
        }
    }

    // o problema está dando no trgt index in exp paths, pois, em alguns momentos, ele não é atualizado. isso indica que não foi encontrado nenhum caminho arco-iris até ele partindo do nó source. A ideia é agora conseguir escolher outros valores, para encontrar um caminho viavel
    if (trgt_index_in_exp_paths == -1)
    {
        //cout << "Returning error" << endl;
        NodeEdgeNode error;
        error.color = -1;
        vector<NodeEdgeNode> error_vector;
        error_vector.push_back(error);
        return error_vector;
    }


    /* std::cout << "Linha 504" << std::endl;
    cout << "expanded paths size: " << expanded_paths.size() << endl;
    cout << "trgt index in exp paths: " << trgt_index_in_exp_paths << endl; */
    vector<NodeEdgeNode> shortest_path;
    shortest_path.push_back(expanded_paths[trgt_index_in_exp_paths]);
    //std::cout << "Linha 507" << std::endl;
    int looking_for_id = shortest_path[0].id_source;
    //std::cout << "Linha 509" << std::endl;
    for (int i = trgt_index_in_exp_paths - 1; i >= 0; i--)
    {
        if (expanded_paths[i].id_target == looking_for_id)
        {
            shortest_path.push_back(expanded_paths[i]);
            looking_for_id = expanded_paths[i].id_source;
        }
    }
    //std::cout << "Linha 518" << std::endl;
    /* cout << "\n\nShortest path\n";
    for (size_t i = 0; i < shortest_path.size(); i++)
    {
        cout << "(" << shortest_path[i].id_source << ", " << shortest_path[i].id_target << ") ";
    }
    cout << "\n\n"; */
    return shortest_path;
}

void Solution::reconnect(std::vector<std::vector<long int>> graph_matrix, std::vector<std::vector<int>> colors_matrix)
{
    //cout << "/ / / / / /  reconnect / / / / / " << endl;
    Xoshiro256plus rand(time(NULL)); // lembrar de pegar o valor para poder repetir experimento

    vector<vector<NodeEdgeNode>> paths;
    paths.clear();

    //cout << "535" << endl;
    int c = 0;
    int k = 0;
    //cout << "536" << endl;
    // do
    while (c == 0 || c < 20)
    {
        int from_id, to_id;
        bool from_f1 = false;
        //cout << "Linha 545" << endl;

        vector<NodeEdgeNode> srp;
        do
        {   
            if (k > 100)
            {
                //cout << "\n-------------------------// /-----------------------//---------------------//-----------------------------------\n" << endl;
                this->colorPruning();
                this->benefactorMatrix(graph_matrix, colors_matrix);
                
                paths.clear();
                c = 0;
                k = 0;
            }
            //cout << "fudeu1  ";
            //cout << "linha 606" << endl; cout << "forest1 size: " << this->forest1.size() << "   forest2 size: " << this->forest2.size() << endl;
            int random_number = rand.next() % this->forest1.size(); // std::cout<<"Linha 547"<<std::endl;
            //cout << "random number1: " << random_number << endl;
            from_id = this->forest1[random_number].id_target;
            //std::cout<<"Linha 610"<<std::endl;
            random_number = rand.next() % this->forest2.size();
            //cout << "random number2: " << random_number << endl;
            to_id = this->forest2[random_number].id_target;
            // std::cout<<"Linha 554"<<std::endl;
    
            //cout << "from_id: " << from_id << "   to_id: " << to_id << endl;
            
            srp = this->shortestRainbowPath(graph_matrix, colors_matrix, from_id - 1, to_id - 1);
            k++;
            //cout << "fudeu2   "<< endl;
        } while (srp[0].color == -1);

        paths.push_back(srp);
        //std::cout << "Linha 557" << std::endl;
        //cout << c << " " << endl;
        c++;

    } // while (c < 5); // 5 abitrario
    //cout << "Linha 626" << endl;
    this->erase_solo_nodes_from_forests();

    int min_path_real_weight = INFINITY;
    int min_path_index = -1;
    int min_path_size = -1;
    int min_num_colors_already_in_sol = INFINITY;

    for (size_t i = 0; i < paths.size(); i++)
    {
        int sum = 0;
        int num = 0;

        for (size_t j = 0; j < paths[i].size(); j++)
        {
            sum += paths[i][j].weight;
            if (find(this->_diff_colors.begin(), this->_diff_colors.end(), paths[i][j].color) != this->_diff_colors.end())
            {
                num++;
            }
        }
        if (num < min_num_colors_already_in_sol)
        {
            min_path_real_weight = sum;
            min_num_colors_already_in_sol = num;
            min_path_index = i;
            min_path_size = paths[i].size();
        }
        else if (num == min_num_colors_already_in_sol)
        {
            if (paths[i].size() < min_path_size)
            {
                min_path_real_weight = sum;
                min_path_index = i;
                min_path_size = paths[i].size();
            }
            else if (paths[i].size() == min_path_size)
            {
                if (sum < min_path_real_weight)
                {
                    min_path_index = i;
                    min_path_real_weight = sum;
                }
            }
        }
    }
    this->reconn_path = paths[min_path_index];

    /* cout << "\n\nReconnection path\n";
    for (size_t i = 0; i < paths[min_path_index].size(); i++)
    {
        cout << "(" << paths[min_path_index][i].id_source << ", " << paths[min_path_index][i].id_target << " - " << paths[min_path_index][i].color << ") ";
    }
    cout << "\n\n"; */

    // cout << "sol size before erase: " << this->_solution.size() << endl;
    this->_solution.erase(this->edge2cut); // remove the edge
    // cout << "sol size after erase: " << this->_solution.size() << endl;
    this->_solution.insert(this->_solution.begin(), this->reconn_path.begin(), this->reconn_path.end()); // insert the reconnection path
    // cout << "sol size after insert: " << this->_solution.size() << endl;
    this->calculate_all_params();
}

void Solution::make_all_in_forest_false()
{
    for (size_t i = 0; i < this->_solution.size(); i++)
    {
        this->_solution[i].in_forest = false;
    }
}

void Solution::erase_solo_nodes_from_forests()
{
    for (vector<NodeEdgeNode>::iterator it = this->forest1.begin(); it != this->forest1.end(); it++)
    {
        if ((*it).id_source == -1)
        {
            this->forest1.erase(it);
            return;
        }
    }
    for (vector<NodeEdgeNode>::iterator it = this->forest2.begin(); it != this->forest2.end(); it++)
    {
        if ((*it).id_source == -1)
        {
            this->forest2.erase(it);
            return;
        }
    }
}
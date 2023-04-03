#ifndef AA94EE4B_7DAF_4D0F_8C20_565E49C259D6
#define AA94EE4B_7DAF_4D0F_8C20_565E49C259D6

#include "Graph.hpp"
#include "defines.hpp"

std::shared_ptr<Graph> read_instances_trstp(std::string input_file)
{
    std::shared_ptr<Graph> graph_to_return;
    std::ifstream instance_file;
    instance_file.open(input_file, std::ios::in);

    std::string line, garbage;
    std::stringstream oss;
    std::string temp;

    int cont = 0;
    int number_of_edges;
    int number_of_nodes;
    int number_of_terminals;

    std::string source; 
    std::string target;
    std::string weight;
    std::string color;
    std::string id_terminal;
    std::string garb;

    int j = 0;
    for (size_t i = 0; i < 9; i++)
    {
        std::getline(instance_file, garbage);
        j++;
    }

    std::getline(instance_file, line);
    oss << line;

    std::getline(oss, garbage);
    
    int pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_nodes = stoi(temp);

    graph_to_return = std::make_shared<Graph> ();

    for (size_t i = 0; i < number_of_nodes; i++)
    {
        graph_to_return->insert_node(i+1);
    }

    std::getline(instance_file, garbage);

    pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_edges = stoi(temp);

    cont = 0;
    while(cont != number_of_edges)
    {
        instance_file >> garb;
        instance_file >> source;
        instance_file >> target;
        instance_file >> weight;
        instance_file >> color;

        graph_to_return->insert_edge(stoi(source), stoi(target), stoi(weight), stoi(color));

        cont++;
    }

    std::getline(instance_file, garbage);
    std::getline(instance_file, garbage);
    std::getline(instance_file, garbage);
    std::getline(instance_file, garbage);

    std::getline(instance_file, garbage);

    pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_terminals = stoi(temp);

    cont = 0;

    while (cont != number_of_terminals)
    {
        instance_file >> garb;
        instance_file >> id_terminal;
        graph_to_return->node(stoi(id_terminal))->is_terminal(true);
        cont++;
    }

    return graph_to_return;
}

void write_results(std::string path_to_results, std::string path_to_instance, int lower_bound, int upper_bound, float average)
{
    std::string instance_name(path_to_instance);
    instance_name = instance_name.substr(instance_name.find_last_of("/") + 1);

    std::fstream results_file;
    results_file.open(path_to_results, std::ios::out|ios::app);

    results_file << instance_name << "," << lower_bound << "," << upper_bound << "," << average << "\n";

    results_file.close();
}

bool test_module(std::string path_to_instance, std::string path_to_results, int number_of_tests)
{
    std::shared_ptr<Graph> g;
    g = read_instances_trstp(path_to_instance);

    std::vector<int> results;
    int lower_bound = INFINITY;
    int upper_bound = -INFINITY;
    float average = 0;

    if(g != nullptr)
    {
        for (size_t i = 0; i < number_of_tests; i++)
        {
            g->create_adjacency_matrix();
            g->calculate_colors_freq(); 
            g->greedy();
            g->tabuSearch();
            /* push-back aqui dos resultados */
        }
    }
    else
    {
        return false;
    }
    if(!results.empty())
    {
        long int sum = 0;
        for (size_t i = 0; i < results.size(); i++)
        {
            sum += results.at(i);
            if(results.at(i) < lower_bound)
            {
                lower_bound = results.at(i);
            }
            if(results.at(i) > upper_bound)
            {
                upper_bound = results.at(i);
            }
        }
        average = sum/results.size();
    }
    else
    {
        return false;
    }

    return true;
}

#endif /* AA94EE4B_7DAF_4D0F_8C20_565E49C259D6 */

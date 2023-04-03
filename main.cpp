#include "defines.hpp"
#include "Graph.hpp"
#include "read.hpp"
//#include "TestModule.hpp"

using namespace std;

std::shared_ptr<Graph> read_instances_trstp(string input_file)
{
    std::shared_ptr<Graph> graph_to_return;
    ifstream instance_file;
    instance_file.open(input_file, ios::in);

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

    graph_to_return = std::make_shared<Graph>();

    for (size_t i = 0; i < number_of_nodes; i++)
    {
        graph_to_return->insert_node(i + 1);
    }

    std::getline(instance_file, garbage);

    pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_edges = stoi(temp);

    cont = 0;
    while (cont != number_of_edges)
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

int main(int argc, char const *argv[])
{
    // Check command line
    if (argc != 2)
    {
        cout << "ERROR: Expected: ./<program_name> <input_file_address>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);
    // string path_to_results_file(argv[2]);
    // int number_of_tests = stoi(argv[3]);

    cout << "Running " << program_name << " with instance " << input_file_name << " ... " << endl;

    // bool test = test_module(input_file_name, path_to_results_file, number_of_tests);

    // std::cout<<"Tests were a total " << (test == true ? "success" : "failure") << "\n" <<std::endl;

    std::shared_ptr<Graph> g;
    g = read_instances_trstp(input_file_name);

    std::cout << (g == nullptr ? "yes" : "no") << std::endl;

    std::cout << "\n"
              << std::endl;

    g->create_adjacency_matrix();
    g->calculate_colors_freq();
    /* g->print_adjacency_matrix();

    std::cout<<"\n\n"<<std::endl;
    g->print_color_matrix();
    std::cout<<"\n\n"<<std::endl; */

    auto start = chrono::high_resolution_clock::now();

    g->greedy();
    g->destructor_constructor();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    
    cout << "\n\nBest solution after reconnection" << endl;
    g->get_best_solution()->print();
    cout << "\nDuration: " << duration.count() << " ms" << endl;

    std::cout << "\n"
              << std::endl;

    // std::cout<<"Graph informations: "<<std::endl;

    // std::cout<<"\t Number of nodes: "<<g->order()<<std::endl;
    // std::cout<<"\t Number of edges: "<<g->number_of_edges()<<std::endl;
    // std::cout<<"\t Is terminal: "<<boolalpha<<g->node_pos(47)->terminal()<<std::endl;
    // std::cout<<"\t Source "<<g->node_pos(49)->id()<<" and target "<<g->node_pos(12)->id()<<" has an edge with weight "
    //     <<g->node_pos(49)->edge_for(13)->weight()<<" and color "<<g->node_pos(49)->edge_for(13)->color()<<""<<std::endl;
    return 0;
}

// ./rstp <path_to_instance> <path_to_result_file> <number_of_tests>
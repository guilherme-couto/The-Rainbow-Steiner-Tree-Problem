#include "defines.hpp"
#include "Graph.hpp"
#include "read.hpp"

using namespace std;

/* void readInstance(shared_ptr<Graph> graph, string &input_file_name)
{
    // Open input file
    ifstream input_file;
    input_file.open(input_file_name, ios::in);

    cout << "\nReading input file..." << endl;

    string line;

    do
    {
        getline(input_file, line);
    } while (line != "SECTION Graph");

    int num_nodes, num_edges, num_terminals;
    std::cout<<"23"<<std::endl;
    getline(input_file, line);
    std::stringstream ss_line(line);
    string aux;
    vector<string> ss_line_infos;
    ss_line_infos.clear();

    std::cout<<"30"<<std::endl;

    while (getline(ss_line, aux, ' '))
        ss_line_infos.push_back(aux);
    std::cout<<"34"<<std::endl;
    num_nodes = stoi(ss_line_infos[1]); // expected nodes count
    std::cout<<"36"<<std::endl;
    getline(input_file, line);
    ss_line.str(std::string());
    ss_line<<line;
    ss_line_infos.clear();
    std::cout<<"41"<<std::endl;
    while (getline(ss_line, aux, ' '))
        ss_line_infos.push_back(aux);
    std::cout<<"44"<<std::endl;
    num_edges = stoi(ss_line_infos[1]); // expected edges count
    std::cout<<"46"<<std::endl;
    // Read edges
    getline(input_file, line);
    while (line != "END")
    {
        // Edges informations
        ss_line.str(std::string());
        ss_line<<line;
        vector<string> ss_edge_infos;
        ss_edge_infos.clear();
        while (getline(ss_line, aux, ' '))
            ss_edge_infos.push_back(aux);
        int source_id = stoi(ss_edge_infos[1]);
        int target_id = stoi(ss_edge_infos[2]);
        int edge_weight = stoi(ss_edge_infos[3]);
        int edge_color = stoi(ss_edge_infos[4]);
        std::cout<<"62"<<std::endl;
        graph->insert_edge(source_id, target_id, edge_weight, edge_color);
        std::cout<<"64"<<std::endl;
        getline(input_file, line); // Get next line
    }
    std::cout<<"67"<<std::endl;
    do
    {
        getline(input_file, line);
    } while (line != "SECTION Terminals");
    std::cout<<"72"<<std::endl;
    getline(input_file, line);
    ss_line.str(std::string());
    ss_line<<line;
    ss_line_infos.clear();
    std::cout<<"77"<<std::endl;
    while (getline(ss_line, aux, ' '))
        ss_line_infos.push_back(aux);
    std::cout<<"80"<<std::endl;
    num_terminals = stoi(ss_line_infos[1]); // expected terminals nodes count
    std::cout<<"82"<<std::endl;
    // Read terminals
    getline(input_file, line);
    while (line != "END")
    {
        // Terminals informations
        ss_line.str(std::string());
        ss_line<<line;
        vector<string> ss_terminal_infos;
        ss_terminal_infos.clear();
        while (getline(ss_line, aux, ' '))
            ss_terminal_infos.push_back(aux);
        int terminal_id = stoi(ss_terminal_infos[1]);

        graph->set_terminal(terminal_id);

        getline(input_file, line); // Get next line
    }
    std::cout<<"100"<<std::endl;
    // Check if reading is right
    if (graph->order() != num_nodes)
        cout << "Error on reading nodes" << endl;
    if (graph->number_of_edges() != num_edges)
        cout << "Error on reading edges" << endl;
    if (graph->number_of_terminals() != num_terminals)
        cout << "Error on reading terminals" << endl;
    std::cout<<"108"<<std::endl;
    // Fechando arquivo de entrada
    input_file.close();
} */


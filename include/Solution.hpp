#ifndef SOLUTION_HPP_INCLUDED
#define SOLUTION_HPP_INCLUDED

#include "defines.hpp"
#include "Edge.hpp"
#include "Structures.hpp"

using namespace std;

class Solution
{
public:
    Solution(vector<NodeEdgeNode> used);
    ~Solution(){};

    unsigned getNumColors();
    unsigned getCost();
    int getMostRepeatedColor();
    int getNumColorsRepeated();

    std::vector<int> used_colors();
    std::vector<int> diff_colors();
    std::vector<int> colors_freq();
    std::vector<NodeEdgeNode> solution();

    void print();
    void calculate_all_params(); // calculate diff_colors, cost, colors_freq and nodes_degree

    std::vector<int> nodes_degree();
    void nonTerminalsPruning();
    void colorPruning();
    void benefactorMatrix(std::vector<std::vector<long int>> graph_matrix, std::vector<std::vector<int>> colors_matrix);
    vector<NodeEdgeNode> shortestRainbowPath(std::vector<std::vector<long int>> graph_matrix, std::vector<std::vector<int>> colors_matrix, int src, int trgt);
    void reconnect(std::vector<std::vector<long int>> graph_matrix, std::vector<std::vector<int>> colors_matrix);
    
    void make_all_in_forest_false();
    void erase_solo_nodes_from_forests();

private:
    vector<NodeEdgeNode> _solution;
    unsigned num_diff_colors;
    unsigned cost;
    int original_size;
    int _num_of_colors_repeated;
    std::vector<std::vector<long int>> _benefactorMatrix;

    std::vector<int> _used_colors; // the color of each edge in solution

    std::vector<int> _diff_colors; // each different color in solution
    std::vector<int> _colors_freq;
    int most_repeated_color;

    std::vector<int> _nodes_degree; // by position

    void calculate_diff_colors();
    void calculate_cost();
    void calculate_colors_freq();
    void erase_duplicated_edges();

    vector<NodeEdgeNode> forest1;
    vector<NodeEdgeNode> forest2;

    vector<NodeEdgeNode> reconn_path;
    vector<NodeEdgeNode>::iterator edge2cut;
};

#endif /* SOLUTION_HPP_INCLUDED */
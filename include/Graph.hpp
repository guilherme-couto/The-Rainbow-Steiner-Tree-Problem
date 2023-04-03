#ifndef B68D9AA7_92EB_4893_93C0_ED994D2C57E0
#define B68D9AA7_92EB_4893_93C0_ED994D2C57E0

#include "defines.hpp"
#include "Node.hpp"
#include "Solution.hpp"
class Graph
{
public:
    Graph(); // grafo sempre vai ser não-direcionado e com peso em aresta e nó
    ~Graph();

    int order();
    int number_of_edges();
    int number_of_terminals();

    std::shared_ptr<Node> first_node();
    std::shared_ptr<Node> last_node();

    void insert_node(int id);
    void insert_edge(int id, int target_id, int weight, int color);

    bool search_node(int id);

    std::shared_ptr<Node> node(int id);
    std::shared_ptr<Node> node_pos(int pos);

    void set_terminal(int id);
    void greedy();
    std::shared_ptr<Solution> prim(std::vector<std::vector<long int>> matrix);

    void create_adjacency_matrix();
    void print_adjacency_matrix();

    void create_color_matrix();
    void print_color_matrix();

    std::vector<std::vector<long int>> get_graph_matrix();
    vector<NodeEdgeNode> vector_to_NEN(int *mst);
    std::shared_ptr<Solution> penalty(std::shared_ptr<Solution> original_sol, std::vector<std::vector<long int>> original_matrix);

    std::vector<int> used_colors();
    std::vector<int> diff_colors();
    std::vector<int> colors_freq();
    void calculate_colors_freq();

    int getMostRepeatedColor();
    int getNumColors();
    std::shared_ptr<Solution> get_best_solution();

    void destructor_constructor();

private:
    int _order;
    int position;
    int _number_of_edges;
    int _number_of_terminals;

    int minKey(std::vector<long int> key, std::vector<bool> mstSet);

    std::shared_ptr<Node> _first_node;
    std::shared_ptr<Node> _last_node;
    std::shared_ptr<Solution> c_solution;
    std::shared_ptr<Solution> best_solution;

    std::vector<std::vector<long int>> graph_matrix;
    std::vector<std::vector<int>> colors_matrix;

    void increment_graph_order();

    std::vector<int> _used_colors; // the color of each edge in solution
    std::vector<int> _diff_colors; // each different color in solution
    std::vector<int> _colors_freq;
    int num_diff_colors;
    int most_repeated_color;
};

#endif /* B68D9AA7_92EB_4893_93C0_ED994D2C57E0 */

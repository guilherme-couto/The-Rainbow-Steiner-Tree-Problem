#ifndef A5615F9F_8111_42E7_B333_CC558A52CCC7
#define A5615F9F_8111_42E7_B333_CC558A52CCC7

#include "defines.hpp"
#include "Edge.hpp"

class Node
{
    public:
        Node(int id);
        ~Node();

        std::shared_ptr<Edge> first_edge();
        std::shared_ptr<Edge> last_edge();
        std::shared_ptr<Node> next_node();
        std::shared_ptr<Edge> edge_for(int target_id);

        int id();
        int in_degree();
        int out_degree();
        int degree();
        bool visited();
        bool terminal();
        int remove_edge(int id, bool directed, std::shared_ptr<Node> target_node);
        int position();
        bool has_edge_for(int target_id);

        void set_next_node(std::shared_ptr<Node> node);
        void insert_edge(int target_id, int target_position, int weight, int color);
        void cleanse();
        void increase_out_degree();
        void increase_in_degree();
        void decrease_out_degree();
        void decrease_in_degree();
        void set_position(int position);
        void set_visited(bool visited);
        void is_terminal(bool terminal);

    private:
        std::shared_ptr<Edge> _first_edge;
        std::shared_ptr<Edge> _last_edge;
        std::shared_ptr<Node> _next_node;

        unsigned int _id;
        unsigned int _position;
        unsigned int _in_degree;
        unsigned int _out_degree;
        unsigned int _degree;
        bool _visited;
        bool _terminal;
};

#endif /* A5615F9F_8111_42E7_B333_CC558A52CCC7 */

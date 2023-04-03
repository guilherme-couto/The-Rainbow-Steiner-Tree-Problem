#ifndef D9F39EEE_069B_4BCE_8FD3_19CF50B3E199
#define D9F39EEE_069B_4BCE_8FD3_19CF50B3E199

#include "defines.hpp"

class Edge
{
    public:
        Edge(int target_id, int target_position);
        ~Edge();

        int target_id();
        int target_position();
        int weight();
        int color();
        std::shared_ptr<Edge> next_edge();

        void set_next_edge(std::shared_ptr<Edge> edge);
        void set_weight(int weight);
        void set_color(int color);

    private:
        std::shared_ptr<Edge> _next_edge;
        int _target_id;
        int _target_position;
        int _weight;
        int _color;
};

#endif /* D9F39EEE_069B_4BCE_8FD3_19CF50B3E199 */

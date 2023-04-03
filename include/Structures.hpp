#ifndef AE6A7111_91DB_4FA5_A8D1_BA926D46C876
#define AE6A7111_91DB_4FA5_A8D1_BA926D46C876

#include "Edge.hpp"
#include "defines.hpp"
struct NodeEdgeNode
{
    int id_source;
    int id_target;
    bool source_terminal;
    bool target_terminal;
    std::shared_ptr<Edge> edge;
    int color;
    int weight;
    bool in_forest = false;
};

#endif /* AE6A7111_91DB_4FA5_A8D1_BA926D46C876 */

#ifndef BF3567F3_4644_4738_A698_7C5192196670
#define BF3567F3_4644_4738_A698_7C5192196670

#include <iostream>
#include <vector>

bool is_duplicated(int i, std::vector<int> duplicated_positions)
{
    for (size_t j = 0; j < duplicated_positions.size(); j++)
    {
        if(duplicated_positions.at(j) == i)
        {
            return true;
        }
    }
    return false;
}

#endif /* BF3567F3_4644_4738_A698_7C5192196670 */

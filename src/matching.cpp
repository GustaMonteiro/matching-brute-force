#include "matching.hpp"

#include <algorithm>
#include <numeric>
#include <vector>

#include "defines.hpp"

int findOptimalMatching(const std::vector<std::vector<int>> &weights)
{
  int n = weights.size();
  std::vector<int> nodes(n);
  iota(nodes.begin(), nodes.end(), 0);
  int minCost = INF;

  do
  {
    int cost = 0;
    bool validMatching = true;
    for (int i = 0; i < n; i += 2)
    {
      int u = nodes[i];
      int v = nodes[i + 1];
      if (weights[u][v] == INF)
      {
        validMatching = false;
        break;
      }
      cost += weights[u][v];
    }

    if (validMatching && cost < minCost)
    {
      minCost = cost;
    }
  } while (next_permutation(nodes.begin(), nodes.end()));

  return minCost;
}

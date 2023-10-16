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

int findOptimalMatchingWithDfs(const std::vector<std::vector<int>> &weights)
{
  int n = weights.size();
  std::vector<int> nodes(n);
  iota(nodes.begin(), nodes.end(), 0);

  std::vector<std::vector<int>> permutations = generateRestrictedPermutations(nodes);

  int minCost = INF;

  for (auto &permutation : permutations)
  {

    int cost = 0;
    bool validMatching = true;
    for (int i = 0; i < n; i += 2)
    {
      int u = permutation[i];
      int v = permutation[i + 1];
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
  }

  return minCost;
}

void dfsRestricted(std::vector<int> &nums, std::vector<bool> &used, std::vector<int> &current, std::vector<std::vector<int>> &result, bool mustBeGreater)
{
  if (current.size() == nums.size())
  {
    result.push_back(current);
    // totalRestrictedPerms++;
    return;
  }

  for (int i = 0; i < nums.size(); ++i)
  {
    if (mustBeGreater)
    {
      if (!used[i] && current.back() < nums[i])
      {
        used[i] = true;
        current.push_back(nums[i]);
        dfsRestricted(nums, used, current, result, false);
        current.pop_back();
        used[i] = false;
      }
    }
    else
    {

      if (!used[i])
      {
        used[i] = true;
        current.push_back(nums[i]);
        dfsRestricted(nums, used, current, result, true);
        current.pop_back();
        used[i] = false;
      }
    }
  }
}

std::vector<std::vector<int>> generateRestrictedPermutations(std::vector<int> &nums)
{
  std::vector<std::vector<int>> result;
  std::vector<int> current;
  std::vector<bool> used(nums.size(), false);
  dfsRestricted(nums, used, current, result, false);
  return result;
}
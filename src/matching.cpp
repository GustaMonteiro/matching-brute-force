#include "matching.hpp"
#include <iostream>

#include <algorithm>
#include <numeric>
#include <vector>

#include "defines.hpp"

std::vector<std::vector<int>> generatePermutations(int n)
{
  bool nIsOdd = false;

  if (n % 2 != 0)
  {
    n++;
    nIsOdd = true;
  }

  std::vector<int> nodes(n);
  std::iota(nodes.begin(), nodes.end(), 0);

  int numberOfPairs = n / 2;

  std::vector<std::vector<int>> permutations;

  permutations.push_back(nodes);

  if (numberOfPairs != 1)
  {
    for (int p = 2; p <= numberOfPairs; p++)
    {
      if (p == 2)
      {
        auto copy = permutations.back();
        std::iter_swap(copy.begin() + 1, copy.begin() + 2);
        permutations.push_back(copy);
        std::iter_swap(copy.begin() + 1, copy.begin() + 3);
        permutations.push_back(copy);
      }
      else
      {
        int numberOfPermutationsAtMoment = permutations.size();
        int fixed = (p * 2) - 2;
        for (int i = 0; i < numberOfPermutationsAtMoment; i++)
        {
          for (int j = 0; j < fixed; j++)
          {
            auto copy = permutations[i];
            std::iter_swap(copy.begin() + j, copy.begin() + fixed);
            permutations.push_back(copy);
          }
        }
      }
    }
  }

  if (nIsOdd)
  {
    for (auto &perm : permutations)
    {
      perm.pop_back();
      perm.pop_back();
    }
  }

  std::cout << "Total permutations: " << permutations.size() << std::endl;
  return permutations;
}

int findOptimalMatching(const std::vector<std::vector<int>> &weights)
{
  int n = weights.size();
  std::vector<std::vector<int>> permutations = generatePermutations(n);

  int minCost = INF;
  int minIndex = -1;

  int currIndex = 0;
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
      minIndex = currIndex;
    }

    currIndex++;
  }

  std::cout << "Minimum matching:\n";

  std::cout << "(";
  for (int i = 0; i < permutations[minIndex].size(); i += 2)
  {
    if (i)
      std::cout << ", ";
    std::cout << (char)('A' + permutations[minIndex][i]) << (char)('A' + permutations[minIndex][i + 1]);
  }
  std::cout << ")" << std::endl;

  return minCost;
}
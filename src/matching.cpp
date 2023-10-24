#include "matching.hpp"
#include <iostream>

#include <algorithm>
#include <numeric>
#include <vector>

#include <cstdlib>
#include <ctime>

#include "defines.hpp"

std::vector<std::vector<int> > generatePermutations(int n)
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

  std::vector<std::vector<int> > permutations;

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

void testPermutation(const std::vector<int> &permutation, int &currentMinCost, std::vector<int> &currentBestPermutation, const std::vector<std::vector<int> > &weights)
{
  int cost = 0;
  bool validMatching = true;
  for (int i = 1; i < permutation.size(); i += 2)
  {
    int u = permutation[i - 1];
    int v = permutation[i];
    if (weights[u][v] == INF)
    {
      validMatching = false;
      break;
    }
    cost += weights[u][v];
  }

  if (validMatching && cost < currentMinCost)
  {
    currentMinCost = cost;
    currentBestPermutation = permutation;
  }
}

long long doubleFatorial(int n)
{
  long long res = 1;
  for (int i = 1; i <= n; i += 2)
    res *= i;
  return res;
}

int findOptimalMatching(const std::vector<std::vector<int> > &weights)
{
  int n = weights.size();

  int minCost = INF;
  int minIndex = -1;
  std::vector<int> bestPermutation;

  if (n < 19)
  {
    std::vector<std::vector<int> > permutations = generatePermutations(n);
    for (auto &permutation : permutations)
      testPermutation(permutation, minCost, bestPermutation, weights);
  }
  else
  {
    int randomPermutations = n <= 20 ? 300000000 : 1000000000;

    std::cout << "Testing with random permutations since n is too big (n = " << n << ")\n";
    std::cout << n << "!! = " << doubleFatorial(n) << " permutations!\n";
    std::cout << "Instead, trying " << randomPermutations << " random permutations\n\n";

    std::srand(std::time(0));

    bool nIsOdd = n % 2 != 0 ? true : false;

    std::vector<int> nodes(n);
    std::iota(nodes.begin(), nodes.end(), 0);
    for (int i = 0; i < randomPermutations; i++)
    {
      auto copy = nodes;
      if (nIsOdd)
        copy.pop_back();

      testPermutation(copy, minCost, bestPermutation, weights);

      int l = std::rand() % n;
      int r = std::rand() % n;

      std::iter_swap(nodes.begin() + l, nodes.begin() + r);
    }
  }

  std::cout << "Minimum matching:\n";

  std::cout << "(";
  for (int i = 0; i < bestPermutation.size(); i += 2)
  {
    if (n < 26)
    {
      if (i)
        std::cout << ", ";
      std::cout << (char)('A' + bestPermutation[i]) << (char)('A' + bestPermutation[i + 1]);
    }
    else
    {
      if (i)
        std::cout << " - ";
      std::cout << bestPermutation[i] << "," << bestPermutation[i + 1];
    }
  }
  std::cout << ")" << std::endl;

  return minCost;
}
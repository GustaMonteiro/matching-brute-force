#pragma once
#include <vector>

int findOptimalMatching(const std::vector<std::vector<int>> &weights);
int findOptimalMatchingWithDfs(const std::vector<std::vector<int>> &weights);
void dfsRestricted(std::vector<int> &nums, std::vector<bool> &used, std::vector<int> &current, std::vector<std::vector<int>> &result, bool mustBeGreater);
std::vector<std::vector<int>> generateRestrictedPermutations(std::vector<int> &nums);
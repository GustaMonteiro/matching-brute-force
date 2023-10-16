#include <iostream>
#include <numeric>
#include <vector>

int totalPerms = 0;

void printPermutation(std::vector<int> &nums) {
  std::cout << "(";
  for (int i = 0; i < nums.size(); i += 2) {
    if (i)
      std::cout << ", ";
    std::cout << (char)('A' + nums[i]) << (char)('A' + nums[i + 1]);
  }
  std::cout << ")" << std::endl;

  totalPerms++;
}

int main() {

  int n;
  std::cin >> n;

  bool nIsOdd = false;

  if (n % 2 != 0) {
    n++;
    nIsOdd = true;
  }

  std::vector<int> nodes(n);
  std::iota(nodes.begin(), nodes.end(), 0);

  int numberOfPairs = n / 2;

  std::vector<std::vector<int>> permutations;

  permutations.push_back(nodes);

  if (numberOfPairs != 1) {
    for (int p = 2; p <= numberOfPairs; p++) {
      if (p == 2) {
        auto copy = permutations.back();
        std::iter_swap(copy.begin() + 1, copy.begin() + 2);
        permutations.push_back(copy);
        std::iter_swap(copy.begin() + 1, copy.begin() + 3);
        permutations.push_back(copy);
      } else {
        int numberOfPermutationsAtMoment = permutations.size();
        int fixed = (p * 2) - 2;
        for (int i = 0; i < numberOfPermutationsAtMoment; i++) {
          for (int j = 0; j < fixed; j++) {
            auto copy = permutations[i];
            std::iter_swap(copy.begin() + j, copy.begin() + fixed);
            permutations.push_back(copy);
          }
        }
      }
    }
  }

  if (nIsOdd) {
    for (auto &perm : permutations) {
      perm.pop_back();
      perm.pop_back();
    }
  }

  for (auto &perm : permutations)
    printPermutation(perm);

  std::cout << "Total: " << totalPerms << std::endl;

  return 0;
}

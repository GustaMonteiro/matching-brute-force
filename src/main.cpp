#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <map>
#include <fstream>

#include "matching.hpp"
#include "inputModes.hpp"

void printUsage(char *executable)
{
  std::cout << "USAGE:\n\n";
  std::cout << executable << " <input mode> [file]\n\n"
                             "Input Modes:\n\n"
                             "--manual: Chose in runtime which input format to use\n\n"
                             "--matrix: Input each weight for edge Mij | for i, j = 1..n\n"
                             "\t0 X X X X\n"
                             "\tX 0 X X X\n"
                             "\tX X 0 X X\n"
                             "\tX X X 0 X\n"
                             "\tX X X X 0\n\n"
                             "--edge: Input each edge and its weitght (x y w) | x = origin, y = destination, w = weigth\n"
                             "\tX1 Y1 W1\n"
                             "\tX2 Y2 W2\n"
                             "\t...\n\n"
                             "--weight: Input only the weights of edge ij | for i = 1..n-1 and for j = i+1..n\n"
                             "\tW1,2 W1,3 W1,4 ... W1,n\n"
                             "\tW2,3 W2,4 ... W2,n\n"
                             "\t...\n"
                             "\tWn-1,n\n\n"
                             "--file <file_path>: Read input using a file\n"
                             "\tFile format:\n"
                             "\t\tmode (0 = matrix, 1 = edge, 2 = weitght)\n"
                             "\t\tn (number of vertices)\n"
                             "\t\t[depends on the mode chosen]\n"
            << std::endl;

  exit(-1);
}

std::map<std::string, std::function<void(int, std::vector<std::vector<int>> &, std::istream &)>> inputModes = {
    {"--matrix", matrixModeInput},
    {"--edge", edgeModeInput},
    {"--weight", weightsModeInput}};

std::set<std::string> acceptedModes{"--manual", "--matrix", "--edge", "--weight", "--file"};

std::map<int, std::string> modeNumberToString = {
    {0, "--matrix"},
    {1, "--edge"},
    {2, "--weight"}};

#define USE_ALL_PERMS 0

int main(int argc, char **argv)
{
  if (argc < 2 || (argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")))
    printUsage(argv[0]);

  std::string mode(argv[1]);
  if (acceptedModes.find(mode) == acceptedModes.end())
    printUsage(argv[0]);

  if (mode == "--manual")
    getInputModeManually(mode);

  if (mode == "--file")
  {
    if (argc < 3)
      printUsage(argv[0]);

    std::ifstream file(argv[2]);
    if (!file.is_open())
    {
      std::cout << "Not able to open file " << argv[2] << std::endl;
      exit(-1);
    }

    int m;
    file >> m;
    if (m < 0 || m > 2)
    {
      std::cout << "Input mode not recognized in file" << std::endl;
      file.close();
      exit(-1);
    }

    mode = modeNumberToString[m];
    int n;
    file >> n;

    std::vector<std::vector<int>> weights(n, std::vector<int>(n));

    inputModes[mode](n, weights, file);

#if USE_ALL_PERMS
    int minCost = findOptimalMatching(weights);
    std::cout << "Minimum cost matching is: " << minCost << std::endl;
#else
    int minCostDfs = findOptimalMatchingWithDfs(weights);
    std::cout << "Minimum cost matching with dfs is: " << minCostDfs << std::endl;
#endif

    file.close();

    return 0;
  }

  int n;
  std::cout << "Insert the number of vertices (n): ";
  std::cin >> n;

  std::vector<std::vector<int>> weights(n, std::vector<int>(n));

  inputModes[mode](n, weights, std::cin);

#if USE_ALL_PERMS
    int minCost = findOptimalMatching(weights);
    std::cout << "Minimum cost matching is: " << minCost << std::endl;
#else
    int minCostDfs = findOptimalMatchingWithDfs(weights);
    std::cout << "Minimum cost matching with dfs is: " << minCostDfs << std::endl;
#endif

  return 0;
}
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::cout << 2 << std::endl;
  int n;
  std::cin >> n;
  std::cout << n << std::endl;

  std::srand(std::time(0));

  while (n > 0) {
    for (int i = 0; i < n; i++) {
      std::cout << (std::rand() % 50) + 1 << " ";
    }
    std::cout << std::endl;

    n--;
  }

  return 0;
}

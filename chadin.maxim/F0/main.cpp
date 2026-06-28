#include "Manager.hpp"
#include <iostream>

int main()
{
  try {
    chadin::Manager manager;
    manager.run();
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << "\n";
    return 2;
  }
  return 0;
}

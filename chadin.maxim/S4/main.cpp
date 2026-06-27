#include <iostream>
#include <fstream>
#include <sstream>
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "Error: filename parameter is required.\n";
    return 1;
  }

  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::cerr << "Error: cannot open dictionary file.\n";
    return 1;
  }

  chadin::DictsTree dicts;
  std::string line;

  while (std::getline(ifs, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss(line);
    std::string dname;

    if (iss >> dname) {
      chadin::BSTree<int, std::string> d;
      if (dicts.has(dname)) {
        d = dicts.get(dname);
      }

      int k;
      std::string v;
      while (iss >> k >> v) {
        d.push(k, v);
      }
      dicts.push(dname, d);
    }
  }

  chadin::processCommands(std::cin, std::cout, dicts);

  return 0;
}

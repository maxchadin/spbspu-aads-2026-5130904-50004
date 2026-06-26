#include "commands.hpp"
#include <sstream>

namespace chadin {

void printDict(std::ostream& out, const std::string& name, const BSTree<int, std::string>& tree)
{
  if (tree.empty()) {
    out << "<EMPTY>\n";
    return;
  }
  out << name;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it) {
    out << " " << it->first << " " << it->second;
  }
  out << "\n";
}

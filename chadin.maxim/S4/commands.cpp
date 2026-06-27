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

void processCommands(std::istream& in, std::ostream& out, DictsTree& dicts)
{
  std::string line;
  while (std::getline(in, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss(line);
    std::string cmd;

    if (!(iss >> cmd)) {
      continue;
    }

    if (cmd == "print") {
      std::string name;
      std::string extra;
      if (iss >> name) {
        if (iss >> extra || !dicts.has(name)) {
          out << "<INVALID COMMAND>\n";
        } else {
          printDict(out, name, dicts.get(name));
        }
      } else {
        out << "<INVALID COMMAND>\n";
      }
    } else if (cmd == "complement") {
      std::string newName, name1, name2, extra;
      if (iss >> newName >> name1 >> name2) {
        if (iss >> extra || !dicts.has(name1) || !dicts.has(name2)) {
          out << "<INVALID COMMAND>\n";
        } else {
          auto d1 = dicts.get(name1);
          auto d2 = dicts.get(name2);
          BSTree<int, std::string> dnew;

          for (auto it = d1.cbegin(); it != d1.cend(); ++it) {
            if (!d2.has(it->first)) {
              dnew.push(it->first, it->second);
            }
          }
          dicts.push(newName, dnew);
        }
      } else {
        out << "<INVALID COMMAND>\n";
      }
    } else if (cmd == "intersect") {
      std::string newName, name1, name2, extra;
      if (iss >> newName >> name1 >> name2) {
        if (iss >> extra || !dicts.has(name1) || !dicts.has(name2)) {
          out << "<INVALID COMMAND>\n";
        } else {
          auto d1 = dicts.get(name1);
          auto d2 = dicts.get(name2);
          BSTree<int, std::string> dnew;

          for (auto it = d1.cbegin(); it != d1.cend(); ++it) {
            if (d2.has(it->first)) {
              dnew.push(it->first, it->second);
            }
          }
          dicts.push(newName, dnew);
        }
      } else {
        out << "<INVALID COMMAND>\n";
      }
    } else if (cmd == "union") {
      std::string newName, name1, name2, extra;
      if (iss >> newName >> name1 >> name2) {
        if (iss >> extra || !dicts.has(name1) || !dicts.has(name2)) {
          out << "<INVALID COMMAND>\n";
        } else {
          auto d1 = dicts.get(name1);
          auto d2 = dicts.get(name2);
          BSTree<int, std::string> dnew = d1;
          for (auto it = d2.cbegin(); it != d2.cend(); ++it) {
            if (!dnew.has(it->first)) {
              dnew.push(it->first, it->second);
            }
          }
          dicts.push(newName, dnew);
        }
      } else {
        out << "<INVALID COMMAND>\n";
      }
    } else {
      out << "<INVALID COMMAND>\n";
    }
  }
}

}

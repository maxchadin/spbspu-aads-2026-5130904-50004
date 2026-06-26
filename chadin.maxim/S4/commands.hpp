#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include "bstree.hpp"

namespace chadin {

using DictsTree = BSTree<std::string, BSTree<int, std::string>>;

void processCommands(std::istream& in, std::ostream& out, DictsTree& dicts);

}

#endif

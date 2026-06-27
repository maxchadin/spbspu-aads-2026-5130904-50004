#include "Manager.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

const int EQUATIONS_COUNT = 11;
const int UNKNOWNS_COUNT = 6;
const int COLUMNS_COUNT = 7;
const double MAGIC_DIVISOR = 10.0;
const double BONUS_CHEMISTRY_THRESHOLD = 25.0;
const double BONUS_VALUE = 2.0;

chadin::Manager::Manager():
  collection_(),
  squads_()
{
}

chadin::Manager::~Manager()
{
}

void chadin::Manager::run()
{
  squads_["Main Squad"] = Squad("Main Squad");
  std::string cmd;
  while (std::cin >> cmd) {
    if (cmd == "exit") {
      std::cout << "Goodbye ! Thanks for using FC26 Ultimate Team Manager .\n";
      break;
    }
    processCommand(cmd);
  }
}

std::string chadin::Manager::readStringToken()
{
  std::string token;
  std::cin >> std::ws;
  if (std::cin.peek() == '"') {
    std::cin.get();
    std::getline(std::cin, token, '"');
  } else {
    std::cin >> token;
  }
  return token;
}

std::string chadin::Manager::getSquadsForPlayer(const int id) const
{
  std::string result = "";
  for (const std::pair< const std::string, Squad >& pair : squads_) {
    if (pair.second.hasPlayer(id)) {
      if (!result.empty()) {
        result += ", ";
      }
      result += "\"" + pair.first + "\"";
    }
  }
  return result;
}

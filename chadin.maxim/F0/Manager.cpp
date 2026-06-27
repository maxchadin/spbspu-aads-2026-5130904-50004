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

void chadin::Manager::processCommand(const std::string& cmd)
{
  if (cmd == "add-player") cmdAddPlayer();
  else if (cmd == "remove-player") cmdRemovePlayer();
  else if (cmd == "find-player") cmdFindPlayer();
  else if (cmd == "list-players") cmdListPlayers();
  else if (cmd == "show-table-stats") cmdShowTableStats();
  else if (cmd == "create-squad") cmdCreateSquad();
  else if (cmd == "delete-squad") cmdDeleteSquad();
  else if (cmd == "list-squads") cmdListSquads();
  else if (cmd == "show-squad") cmdShowSquad();
  else if (cmd == "add-to-squad") cmdAddToSquad();
  else if (cmd == "remove-from-squad") cmdRemoveFromSquad();
  else if (cmd == "clear-squad") cmdClearSquad();
  else if (cmd == "calc-chemistry") cmdCalcChemistry();
  else if (cmd == "calc-team-rating") cmdCalcTeamRating();
  else if (cmd == "predict-match") cmdPredictMatch();
  else if (cmd == "save-collection") cmdSaveCollection();
  else if (cmd == "load-collection") cmdLoadCollection();
  else if (cmd == "save-all-squads") cmdSaveAllSquads();
  else if (cmd == "load-all-squads") cmdLoadAllSquads();
  else if (cmd == "help") cmdHelp();
  else {
    std::cerr << "<INVALID COMMAND> Unknown command: " << cmd << "\n";
  }
}

void chadin::Manager::cmdAddPlayer()
{
  int id = 0;
  int pac = 0;
  int sho = 0;
  int pas = 0;
  int dri = 0;
  int def = 0;
  int phy = 0;
  std::cin >> id;
  std::string name = readStringToken();
  std::string nation = readStringToken();
  std::string league = readStringToken();
  std::string pos = readStringToken();
  std::cin >> pac >> sho >> pas >> dri >> def >> phy;
  Player p(id, name, nation, league, pos, pac, sho, pas, dri, def, phy);
  if (collection_.addPlayer(p)) {
    std::cout << "[OK] Player " << id << " (" << name << ") added to club collection.\n";
  } else {
    std::cerr << "<INVALID COMMAND> Player with id " << id << " already exists.\n";
  }
}

void chadin::Manager::cmdRemovePlayer()
{
  int id = 0;
  std::cin >> id;
  Player p;
  if (collection_.findPlayer(id, p)) {
    collection_.removePlayer(id);
    std::cout << "[OK] Player " << id << " (" << p.getName() << ") removed from club collection.\n";
    std::string squadsStr = getSquadsForPlayer(id);
    if (!squadsStr.empty()) {
      std::cout << "[INFO] Player was also removed from squads: " << squadsStr << "\n";
      for (std::pair< const std::string, Squad >& pair : squads_) {
        pair.second.removePlayer(id);
      }
    }
  } else {
    std::cerr << "<INVALID COMMAND> Player with id " << id << " not found.\n";
  }
}

void chadin::Manager::cmdFindPlayer()
{
  int id = 0;
  std::cin >> id;
  Player p;
  if (collection_.findPlayer(id, p)) {
    std::cout << "[FOUND] ID: " << p.getId() << " | Name: " << p.getName()
              << " | Nation: " << p.getNation() << " | League: " << p.getLeague()
              << " | Position: " << p.getPosition() << "\n"
              << "Pace: " << p.getPace() << " | Shooting: " << p.getShooting()
              << " | Passing: " << p.getPassing() << " | Dribbling: " << p.getDribbling()
              << " | Defending: " << p.getDefending() << " | Physical: " << p.getPhysical() << "\n"
              << "Total rating (avg): " << std::fixed << std::setprecision(1) << p.getRating() << "\n";
    std::string squadsStr = getSquadsForPlayer(id);
    if (!squadsStr.empty()) {
      std::cout << "In squads: " << squadsStr << "\n";
    } else {
      std::cout << "In squads: None\n";
    }
  } else {
    std::cerr << "<INVALID COMMAND> Player with id " << id << " not found.\n";
  }
}

void chadin::Manager::cmdListPlayers()
{
  std::cout << "========== CLUB COLLECTION (Robin Hood Hash Table) ==========\n";
  const std::vector< Collection::Entry_t >& table = collection_.getTable();
  for (const Collection::Entry_t& entry : table) {
    if (entry.status_ == Collection::Status::OCCUPIED) {
      std::cout << "ID: " << entry.player_.getId() << " | Name: " << entry.player_.getName()
                << " | Rating: " << std::fixed << std::setprecision(1)
                << entry.player_.getRating() << "\n";
    }
  }
  std::cout << "Total players: " << collection_.getSize() << "\n";
}

void chadin::Manager::cmdCreateSquad()
{
  std::string name = readStringToken();
  if (squads_.find(name) == squads_.end()) {
    squads_[name] = Squad(name);
    std::cout << "[OK] Squad \"" << name << "\" created (0/11 players).\n";
  } else {
    std::cerr << "<INVALID COMMAND> Squad \"" << name << "\" already exists.\n";
  }
}

void chadin::Manager::cmdDeleteSquad()
{
  std::string name = readStringToken();
  if (squads_.size() <= 1) {
    std::cerr << "<INVALID COMMAND> Cannot delete the last squad. At least one must exist.\n";
  } else {
    std::map< std::string, Squad >::iterator it = squads_.find(name);
    if (it != squads_.end()) {
      squads_.erase(it);
      std::cout << "[OK] Squad \"" << name << "\" deleted.\n";
    } else {
      std::cerr << "<INVALID COMMAND> Squad \"" << name << "\" not found.\n";
    }
  }
}
void chadin::Manager::cmdShowTableStats()
{
  std::cout << "========== Robin Hood Hash Table Statistics ==========\n"
            << "Table size: " << collection_.getCapacity() << "\n"
            << "Elements: " << collection_.getSize() << "\n"
            << "Load factor: " << collection_.getLoadFactor() << "\n"
            << "Collisions total: " << collection_.getCollisions() << "\n"
            << "Average probe dist: " << collection_.getAverageProbe() << "\n"
            << "Max probe dist: " << collection_.getMaxProbe() << "\n"
            << "Rehash count: " << collection_.getRehashCount() << "\n";
}

void chadin::Manager::cmdListSquads()
{
  std::cout << "========== ALL SQUADS ==========\n";
  for (const std::pair< const std::string, Squad >& pair : squads_) {
    std::cout << pair.first << " (" << pair.second.getPlayerCount() << "/11 players)\n";
  }
  std::cout << "Total squads: " << squads_.size() << "\n";
}

void chadin::Manager::cmdShowSquad()
{
  std::string name = readStringToken();
  std::map< std::string, Squad >::iterator it = squads_.find(name);
  if (it != squads_.end()) {
    std::cout << "========== SQUAD: \"" << name << "\" ==========\n";
    std::cout << "Players in squad: " << it->second.getPlayerCount() << "/11\n";
  } else {
    std::cerr << "<INVALID COMMAND> Squad \"" << name << "\" not found.\n";
  }
}

#include "Manager.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

namespace chadin {

  std::string Manager::readString(std::istream &is) const
  {
    std::string result;
    is >> std::ws;
    if (is.peek() == '"') {
      is.get();
      std::getline(is, result, '"');
    } else {
      is >> result;
    }
    return result;
  }

  void Manager::run()
  {
    std::string command;
    while (std::cin >> command) {
      try {
        if (command == "exit") {
          std::cout << "Goodbye! Thanks for using FC26 Ultimate Team Manager.\n";
          break;
        } else if (command == "add-player") {
          processAddPlayer();
        } else if (command == "remove-player") {
          processRemovePlayer();
        } else if (command == "find-player") {
          processFindPlayer();
        } else if (command == "list-players") {
          processListPlayers();
        } else if (command == "show-table-stats") {
          processShowTableStats();
        } else if (command == "create-squad") {
          processCreateSquad();
        } else if (command == "delete-squad") {
          processDeleteSquad();
        } else if (command == "list-squads") {
          processListSquads();
        } else if (command == "show-squad") {
          processShowSquad();
        } else if (command == "add-to-squad") {
          processAddToSquad();
        } else if (command == "remove-from-squad") {
          processRemoveFromSquad();
        } else if (command == "clear-squad") {
          processClearSquad();
        } else if (command == "calc-team-rating") {
          processCalcTeamRating();
        } else if (command == "predict-match") {
          processPredictMatch();
        } else if (command == "help") {
          processHelp();
        } else {
          std::cout << "<INVALID COMMAND> Unknown command.\n";
        }
      } catch (const std::exception &e) {
        std::cout << "<INVALID COMMAND> " << e.what() << "\n";
      }
    }
  }

  void Manager::processAddPlayer()
  {
    int id = 0;
    std::cin >> id;
    std::string name = readString(std::cin);
    std::string nation = readString(std::cin);
    std::string league = readString(std::cin);
    std::string pos = readString(std::cin);
    int pac = 0;
    int sho = 0;
    int pas = 0;
    int dri = 0;
    int def = 0;
    int phy = 0;
    std::cin >> pac >> sho >> pas >> dri >> def >> phy;

    Player p(id, name, nation, league, pos, pac, sho, pas, dri, def, phy);
    collection_.addPlayer(p);
    std::cout << "[OK] Player " << id << " (" << name << ") added to club collection.\n";
  }

  void Manager::processRemovePlayer()
  {
    int id = 0;
    std::cin >> id;
    collection_.removePlayer(id);

    std::vector<std::string> removedFrom;
    for (auto &pair : squads_) {
      if (pair.second.hasPlayer(id)) {
        pair.second.removePlayer(id);
        removedFrom.push_back(pair.first);
      }
    }

    std::cout << "[OK] Player " << id << " removed from club collection.\n";
    if (!removedFrom.empty()) {
      std::cout << "[INFO] Player was also removed from squads: ";
      for (size_t i = 0; i < removedFrom.size(); ++i) {
        std::cout << "\"" << removedFrom[i] << "\"" << (i + 1 == removedFrom.size() ? "" : ", ");
      }
      std::cout << "\n";
    }
  }

  void Manager::processFindPlayer()
  {
    int id = 0;
    std::cin >> id;
    const Player *p = collection_.findPlayer(id);
    if (!p) {
      throw std::runtime_error("Player not found.");
    }

    std::cout << "[FOUND] ID: " << p->getId() << " | Name: " << p->getName() << "\n"
              << "Rating (avg): " << p->getAverageRating() << "\n";

    std::vector<std::string> inSquads;
    for (const auto &pair : squads_) {
      if (pair.second.hasPlayer(id)) {
        inSquads.push_back(pair.first);
      }
    }
    if (!inSquads.empty()) {
      std::cout << "In squads: ";
      for (size_t i = 0; i < inSquads.size(); ++i) {
        std::cout << "\"" << inSquads[i] << "\"" << (i + 1 == inSquads.size() ? "" : ", ");
      }
      std::cout << "\n";
    }
  }

  void Manager::processListPlayers()
  {
    collection_.listPlayers();
  }

  void Manager::processShowTableStats()
  {
    collection_.showTableStats();
  }

  void Manager::processCreateSquad()
  {
    std::string name = readString(std::cin);
    if (squads_.find(name) != squads_.end()) {
      throw std::runtime_error("Squad already exists.");
    }
    squads_.insert({name, Squad(name)});
    std::cout << "[OK] Squad \"" << name << "\" created (0/11 players).\n";
  }

  void Manager::processDeleteSquad()
  {
    std::string name = readString(std::cin);
    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }
    if (squads_.size() == 1) {
      throw std::runtime_error("Cannot delete the last squad. At least one must exist.");
    }
    squads_.erase(it);
    std::cout << "[OK] Squad \"" << name << "\" deleted.\n";
  }

  void Manager::processListSquads()
  {
    std::cout << "========== ALL SQUADS ==========\n";
    for (const auto &pair : squads_) {
      std::cout << pair.first << " (" << pair.second.getPlayerCount() << "/11 players)\n";
    }
    std::cout << "Total squads: " << squads_.size() << "\n";
  }

  void Manager::processShowSquad()
  {
    std::string name = readString(std::cin);
    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }
    it->second.show();
  }

  void Manager::processAddToSquad()
  {
    std::string name = readString(std::cin);
    int id = 0;
    std::cin >> id;

    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }
    const Player *p = collection_.findPlayer(id);
    if (!p) {
      throw std::runtime_error("Player not found in collection.");
    }
    it->second.addPlayer(*p);
    std::cout << "[OK] Player added to squad.\n";
  }

  void Manager::processRemoveFromSquad()
  {
    std::string name = readString(std::cin);
    int id = 0;
    std::cin >> id;

    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }
    it->second.removePlayer(id);
    std::cout << "[OK] Player removed from squad.\n";
  }

  void Manager::processClearSquad()
  {
    std::string name = readString(std::cin);
    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }
    it->second.clear();
    std::cout << "[OK] Squad \"" << name << "\" cleared.\n";
  }

  double Manager::calculateSquadRating(const Squad& squad, bool printDetails) const
  {
    if (squad.getPlayerCount() < 11) {
      throw std::runtime_error("Squad must have 11 players to calculate rating.");
    }

    std::vector<int> ids = squad.getPlayerIds();
    double a[11][7] = {0.0};

    for (int i = 0; i < 11; ++i) {
      const Player *p = collection_.findPlayer(ids[i]);
      if (p) {
        a[i][0] = p->getPace();
        a[i][1] = p->getShooting();
        a[i][2] = p->getPassing();
        a[i][3] = p->getDribbling();
        a[i][4] = p->getDefending();
        a[i][5] = p->getPhysical();
        a[i][6] = p->getAverageRating();
      }
    }

    if (printDetails) {
      std::cout << "========== GAUSSIAN ELIMINATION ==========\n"
                << "Squad: \"" << squad.getName() << "\" (11/11 players)\n";
    }

    for (int k = 0; k < 6; ++k) {
      int maxRow = k;
      for (int i = k + 1; i < 11; ++i) {
        if (std::abs(a[i][k]) > std::abs(a[maxRow][k])) {
          maxRow = i;
        }
      }

      for (int j = 0; j <= 6; ++j) {
        std::swap(a[k][j], a[maxRow][j]);
      }

      double pivot = a[k][k];
      if (std::abs(pivot) > 1e-9) {
        for (int j = 0; j <= 6; ++j) {
          a[k][j] /= pivot;
        }
        for (int i = k + 1; i < 11; ++i) {
          double factor = a[i][k];
          for (int j = k; j <= 6; ++j) {
            a[i][j] -= factor * a[k][j];
          }
        }
      }
    }

    std::vector<double> weights(6, 0.0);
    for (int i = 5; i >= 0; --i) {
      weights[i] = a[i][6];
      for (int j = i + 1; j < 6; ++j) {
        weights[i] -= a[i][j] * weights[j];
      }
    }

    double weightSum = 0.0;
    for (double w : weights) {
      weightSum += std::abs(w);
    }
    if (weightSum > 1e-9) {
      for (double &w : weights) {
        w = std::abs(w) / weightSum;
      }
    }

    double teamRating = 0.0;
    for (int i = 0; i < 11; ++i) {
      const Player *p = collection_.findPlayer(ids[i]);
      if (p) {
        teamRating += weights[0] * p->getPace() +
                      weights[1] * p->getShooting() +
                      weights[2] * p->getPassing() +
                      weights[3] * p->getDribbling() +
                      weights[4] * p->getDefending() +
                      weights[5] * p->getPhysical();
      }
    }

    double finalRating = teamRating / 11.0;

    if (printDetails) {
      std::cout << "Final team rating for \"" << squad.getName() << "\": "
                << std::fixed << std::setprecision(1) << finalRating << "\n";
    }

    return finalRating;
  }

  void Manager::processCalcTeamRating()
  {
    std::string name = readString(std::cin);
    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }

    calculateSquadRating(it->second, true);
  }

  void Manager::processPredictMatch()
  {
    std::string name = readString(std::cin);
    double opponentRating = 0.0;
    std::cin >> opponentRating;

    auto it = squads_.find(name);
    if (it == squads_.end()) {
      throw std::runtime_error("Squad does not exist.");
    }

    double teamRating = calculateSquadRating(it->second, false);

    double pWin = 1.0 / (1.0 + std::exp(-(teamRating - opponentRating) / 10.0));
    double pLoss = 1.0 / (1.0 + std::exp(-(opponentRating - teamRating) / 10.0));
    double pDraw = 1.0 - pWin - pLoss;

    if (pDraw < 0.0) pDraw = 0.0;

    double diff = teamRating - opponentRating;

    std::cout << "======= MATCH PREDICTION ==========\n"
              << "Squad: \"" << name << "\"\n"
              << "Team rating: " << std::fixed << std::setprecision(1) << teamRating << "\n"
              << "Opponent rating: " << opponentRating << "\n"
              << "Rating difference: " << (diff > 0 ? "+" : "") << diff << "\n"
              << "Win probability: " << std::fixed << std::setprecision(1) << (pWin * 100.0) << "%\n"
              << "Loss probability: " << (pLoss * 100.0) << "%\n";
  }

  void Manager::processHelp() const
  {
    std::cout << "=== FC26 ULTIMATE TEAM MANAGER ===\n"
              << "Commands:\n"
              << " add-player, remove-player, find-player, list-players, show-table-stats\n"
              << " create-squad, delete-squad, list-squads, show-squad\n"
              << " add-to-squad, remove-from-squad, clear-squad\n"
              << " calc-team-rating, predict-match\n"
              << " help, exit\n";
  }

}

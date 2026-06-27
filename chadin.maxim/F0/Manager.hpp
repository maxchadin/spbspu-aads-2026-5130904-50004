#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Collection.hpp"
#include "Squad.hpp"
#include <map>
#include <string>

namespace chadin {

class Manager {
public:
  Manager();
  ~Manager();

  void run();

private:
  Collection collection_;
  std::map< std::string, Squad > squads_;

  void processCommand(const std::string& cmd);
  void cmdAddPlayer();
  void cmdRemovePlayer();
  void cmdFindPlayer();
  void cmdListPlayers();
  void cmdShowTableStats();

  void cmdCreateSquad();
  void cmdDeleteSquad();
  void cmdListSquads();
  void cmdShowSquad();
  void cmdAddToSquad();
  void cmdRemoveFromSquad();
  void cmdClearSquad();

  void cmdCalcChemistry();
  void cmdCalcTeamRating();
  void cmdPredictMatch();

  void cmdSaveCollection();
  void cmdLoadCollection();
  void cmdSaveAllSquads();
  void cmdLoadAllSquads();
  void cmdHelp();

  std::string readStringToken();
  std::string getSquadsForPlayer(int id) const;
};

}

#endif

#ifndef CHADIN_MANAGER_HPP
#define CHADIN_MANAGER_HPP

#include "Collection.hpp"
#include "Squad.hpp"
#include <string>
#include <map>

namespace chadin {

  class Manager {
  public:
    void run();

  private:
    std::string readString(std::istream &is) const;

    void processAddPlayer();
    void processRemovePlayer();
    void processFindPlayer();
    void processListPlayers();
    void processShowTableStats();

    void processCreateSquad();
    void processDeleteSquad();
    void processListSquads();
    void processShowSquad();

    void processAddToSquad();
    void processRemoveFromSquad();
    void processClearSquad();

    void processCalcTeamRating();
    void processPredictMatch();
    double calculateSquadRating(const Squad& squad, bool printDetails) const;
    void processHelp() const;


    Collection collection_;
    std::map<std::string, Squad> squads_;
  };

}

#endif

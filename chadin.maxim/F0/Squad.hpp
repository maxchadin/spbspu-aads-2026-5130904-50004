#ifndef SQUAD_HPP
#define SQUAD_HPP

#include <string>
#include <vector>

namespace chadin {

class Squad {
public:
  Squad();
  Squad(const std::string& name);
  ~Squad();

  const std::string& getName() const;
  bool addPlayer(int playerId, const std::string& position);
  bool removePlayer(int playerId);
  void clear();
  bool hasPlayer(int playerId) const;
  int getPlayerCount() const;

  int getPlayerAt(int slotIndex) const;
  int getSlotIndex(const std::string& position) const;

  static const int SQUAD_SIZE = 11;

private:
  std::string name_;
  std::vector< int > positions_;
};

}

#endif

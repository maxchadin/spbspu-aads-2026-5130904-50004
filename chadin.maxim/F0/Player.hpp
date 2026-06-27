#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

namespace chadin {

class Player {
public:
  Player();
  Player(int id, const std::string& name, const std::string& nation, const std::string& league,
         const std::string& pos, int pac, int sho, int pas, int dri, int def, int phy);

  int getId() const;
  const std::string& getName() const;
  const std::string& getNation() const;
  const std::string& getLeague() const;
  const std::string& getPosition() const;

  int getPace() const;
  int getShooting() const;
  int getPassing() const;
  int getDribbling() const;
  int getDefending() const;
  int getPhysical() const;

  double getRating() const;

private:
  int id_;
  std::string name_;
  std::string nation_;
  std::string league_;
  std::string position_;
  int pace_;
  int shooting_;
  int passing_;
  int dribbling_;
  int defending_;
  int physical_;
};

}

#endif

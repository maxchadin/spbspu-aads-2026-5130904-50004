#include "Squad.hpp"

chadin::Squad::Squad():
  name_(""),
  positions_(SQUAD_SIZE, -1)
{
}

chadin::Squad::Squad(const std::string& name):
  name_(name),
  positions_(SQUAD_SIZE, -1)
{
}

chadin::Squad::~Squad()
{
}

const std::string& chadin::Squad::getName() const
{
  return name_;
}

#include <boost/test/unit_test.hpp>
#include "Squad.hpp"
#include "Player.hpp"

BOOST_AUTO_TEST_CASE(SquadAddAndRemovePlayer)
{
  chadin::Squad squad("TestSquad");
  chadin::Player p(1, "Messi", "Argentina", "MLS", "RW", 88, 85, 90, 94, 35, 65);

  squad.addPlayer(p);
  BOOST_CHECK(squad.hasPlayer(1));
  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 1);

  squad.removePlayer(1);
  BOOST_CHECK(!squad.hasPlayer(1));
  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 0);
}

BOOST_AUTO_TEST_CASE(SquadDuplicatePositionThrows)
{
  chadin::Squad squad("TestSquad");
  chadin::Player p1(1, "Messi", "Argentina", "MLS", "RW", 88, 85, 90, 94, 35, 65);
  chadin::Player p2(2, "Salah", "Egypt", "EPL", "RW", 90, 89, 82, 90, 45, 76);

  squad.addPlayer(p1);
  BOOST_CHECK_THROW(squad.addPlayer(p2), std::runtime_error);
}

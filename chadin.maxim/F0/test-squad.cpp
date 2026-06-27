#include <boost/test/unit_test.hpp>
#include "Squad.hpp"

BOOST_AUTO_TEST_SUITE(SquadTestSuite)

BOOST_AUTO_TEST_CASE(testSquadInitialization)
{
  chadin::Squad squad("Main Squad");

  BOOST_CHECK_EQUAL(squad.getName(), "Main Squad");
  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 0);
}

BOOST_AUTO_TEST_CASE(testAddAndRemoveFromSquad)
{
  chadin::Squad squad("U23 Team");

  BOOST_CHECK(squad.addPlayer(10, "ST"));
  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 1);
  BOOST_CHECK(squad.hasPlayer(10));

  BOOST_CHECK(!squad.addPlayer(11, "ST"));
  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 1);

  BOOST_CHECK(squad.removePlayer(10));
  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 0);
  BOOST_CHECK(!squad.hasPlayer(10));
}

BOOST_AUTO_TEST_CASE(testClearSquad)
{
  chadin::Squad squad("Legends Team");

  squad.addPlayer(1, "GK");
  squad.addPlayer(2, "LB");
  squad.addPlayer(3, "RB");

  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 3);

  squad.clear();

  BOOST_CHECK_EQUAL(squad.getPlayerCount(), 0);
  BOOST_CHECK(!squad.hasPlayer(1));
  BOOST_CHECK(!squad.hasPlayer(2));
  BOOST_CHECK(!squad.hasPlayer(3));
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include "Collection.hpp"
#include "Player.hpp"

BOOST_AUTO_TEST_SUITE(CollectionTestSuite)

BOOST_AUTO_TEST_CASE(testAddPlayer)
{
  chadin::Collection collection;
  chadin::Player player(10, "Mbappe", "France", "La_Liga", "ST", 91, 88, 82, 85, 45, 78);

  BOOST_CHECK(collection.addPlayer(player));
  BOOST_CHECK_EQUAL(collection.getSize(), 1);

  BOOST_CHECK(!collection.addPlayer(player));
  BOOST_CHECK_EQUAL(collection.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(testFindPlayer)
{
  chadin::Collection collection;
  chadin::Player player(7, "Messi", "Argentina", "MLS", "RW", 88, 85, 90, 94, 35, 65);
  collection.addPlayer(player);

  chadin::Player foundPlayer;
  BOOST_CHECK(collection.findPlayer(7, foundPlayer));
  BOOST_CHECK_EQUAL(foundPlayer.getName(), "Messi");

  chadin::Player notFound;
  BOOST_CHECK(!collection.findPlayer(99, notFound));
}

BOOST_AUTO_TEST_CASE(testRemovePlayer)
{
  chadin::Collection collection;
  chadin::Player player(3, "Van Dijk", "Netherlands", "PremierLeague", "CB", 75, 50, 70, 65, 89, 86);
  collection.addPlayer(player);

  BOOST_CHECK(collection.hasPlayer(3));
  BOOST_CHECK(collection.removePlayer(3));
  BOOST_CHECK_EQUAL(collection.getSize(), 0);
  BOOST_CHECK(!collection.hasPlayer(3));

  BOOST_CHECK(!collection.removePlayer(3));
}

BOOST_AUTO_TEST_CASE(testRehash)
{
  chadin::Collection collection;
  int initialCapacity = collection.getCapacity();

  for (int i = 0; i < 10; ++i) {
    chadin::Player p(i, "Dummy", "Nation", "League", "CM", 50, 50, 50, 50, 50, 50);
    collection.addPlayer(p);
  }

  BOOST_CHECK(collection.getCapacity() > initialCapacity);
  BOOST_CHECK_EQUAL(collection.getSize(), 10);
  BOOST_CHECK_EQUAL(collection.getRehashCount(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

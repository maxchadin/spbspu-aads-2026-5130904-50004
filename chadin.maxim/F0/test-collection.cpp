#include <boost/test/unit_test.hpp>
#include "Collection.hpp"
#include "Player.hpp"

BOOST_AUTO_TEST_CASE(CollectionInsertAndFind)
{
  chadin::Collection coll;
  chadin::Player p(10, "Mbappe", "France", "La_Liga", "ST", 91, 88, 82, 85, 45, 78);

  coll.addPlayer(p);
  const chadin::Player* found = coll.findPlayer(10);

  BOOST_REQUIRE(found != nullptr);
  BOOST_CHECK_EQUAL(found->getName(), "Mbappe");
}

BOOST_AUTO_TEST_CASE(CollectionRemove)
{
  chadin::Collection coll;
  chadin::Player p(10, "Mbappe", "France", "La_Liga", "ST", 91, 88, 82, 85, 45, 78);

  coll.addPlayer(p);
  coll.removePlayer(10);

  BOOST_CHECK(coll.findPlayer(10) == nullptr);
}

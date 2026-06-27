#include <boost/test/unit_test.hpp>
#include "hashTable.hpp"
#include "blake2.hpp"
#include <stdexcept>
#include <string>

BOOST_AUTO_TEST_SUITE(AdvancedHashTests)

BOOST_AUTO_TEST_CASE(exception_on_empty_get)
{
  chadin::HashTable< std::string, int, chadin::Blake2sHash, chadin::StringEqual > table(4, 2);
  BOOST_CHECK_THROW(table.get("missing_key"), std::invalid_argument);
  BOOST_CHECK_THROW(table.drop("missing_key"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(spare_bucket_allocation_and_overflow)
{
  chadin::HashTable< std::string, int, chadin::Blake2sHash, chadin::StringEqual > table(1, 2);

  table.add("A", 10);
  table.add("B", 20);
  table.add("C", 30);
  table.add("D", 40);

  BOOST_CHECK(table.has("C"));
  BOOST_CHECK_EQUAL(table.get("D"), 40);

  BOOST_CHECK_THROW(table.add("E", 50), std::overflow_error);
}

BOOST_AUTO_TEST_CASE(drop_frees_space_for_new_elements)
{
  chadin::HashTable< std::string, int, chadin::Blake2sHash, chadin::StringEqual > table(1, 2);
  table.add("X", 100);
  table.add("Y", 200);
  table.add("Z", 300);

  BOOST_CHECK_EQUAL(table.drop("X"), 100);
  BOOST_CHECK(!table.has("X"));

  BOOST_CHECK_NO_THROW(table.add("W", 400));
  BOOST_CHECK_NO_THROW(table.add("V", 500));
}

BOOST_AUTO_TEST_CASE(rehash_preserves_all_data)
{
  chadin::HashTable< std::string, int, chadin::Blake2sHash, chadin::StringEqual > table(2, 2);
  table.add("Key1", 1);
  table.add("Key2", 2);

  table.rehash(10);

  BOOST_CHECK(table.has("Key1"));
  BOOST_CHECK(table.has("Key2"));
  BOOST_CHECK_EQUAL(table.get("Key1"), 1);
}

BOOST_AUTO_TEST_SUITE_END()

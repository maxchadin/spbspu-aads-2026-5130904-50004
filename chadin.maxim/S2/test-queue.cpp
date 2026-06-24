#include <boost/test/unit_test.hpp>
#include "queue.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(QueueTests)

BOOST_AUTO_TEST_CASE(PushAndPop)
{
  chadin::Queue< int > queue;
  BOOST_CHECK(queue.isEmpty());

  queue.push(3);
  queue.push(4);

  BOOST_CHECK(!queue.isEmpty());
  BOOST_CHECK_EQUAL(queue.front(), 3);

  queue.pop();
  BOOST_CHECK_EQUAL(queue.front(), 4);

  queue.pop();
  BOOST_CHECK(queue.isEmpty());
}

BOOST_AUTO_TEST_CASE(Exceptions)
{
  chadin::Queue< int > queue;
  BOOST_CHECK_THROW(queue.pop(), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

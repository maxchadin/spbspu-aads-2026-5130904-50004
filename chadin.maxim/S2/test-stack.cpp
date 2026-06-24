#include <boost/test/unit_test.hpp>
#include "stack.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(StackTests)

BOOST_AUTO_TEST_CASE(PushAndPop)
{
  chadin::Stack< int > stack;
  BOOST_CHECK(stack.isEmpty());

  stack.push(3);
  stack.push(4);

  BOOST_CHECK(!stack.isEmpty());
  BOOST_CHECK_EQUAL(stack.top(), 4);

  stack.pop();
  BOOST_CHECK_EQUAL(stack.top(), 3);

  stack.pop();
  BOOST_CHECK(stack.isEmpty());
}

BOOST_AUTO_TEST_CASE(Exceptions)
{
  chadin::Stack< int > stack;
  BOOST_CHECK_THROW(stack.pop(), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include "expression_processor.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(BitwiseOrTests)

BOOST_AUTO_TEST_CASE(Basic)
{
  BOOST_CHECK_EQUAL(chadin::performOp('|', 4, 6), 6);
  BOOST_CHECK_EQUAL(chadin::performOp('|', 3, 5), 7);
  BOOST_CHECK_EQUAL(chadin::performOp('|', 10, 15), 15);
}

BOOST_AUTO_TEST_CASE(InExpression)
{
  BOOST_CHECK_EQUAL(chadin::evaluateInfix("4 | 6"), 6);

  BOOST_CHECK_EQUAL(chadin::evaluateInfix("4 | 2 + 1"), 7);

  BOOST_CHECK_EQUAL(chadin::evaluateInfix("( 4 | 2 ) + 1"), 7);
}

BOOST_AUTO_TEST_CASE(Exceptions)
{
  BOOST_CHECK_THROW(chadin::performOp('^', 5, 2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

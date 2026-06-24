#ifndef EXPRESSION_PROCESSOR_HPP
#define EXPRESSION_PROCESSOR_HPP

#include <string>
#include "stack.hpp"
#include "queue.hpp"

namespace chadin
{
  long long evaluateInfix(const std::string & expr);
  int getPriority(char op);
  long long performOp(char op, long long a, long long b);
}

#endif

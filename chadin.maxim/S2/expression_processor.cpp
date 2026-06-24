#include "expression_processor.hpp"
#include <stdexcept>
#include <limits>
#include <cctype>

int chadin::getPriority(char op)
{
  if (op == '*' || op == '/' || op == '%') return 3;
  if (op == '+' || op == '-') return 2;
  if (op == '|') return 1;
  return 0;
}

long long chadin::performOp(char op, long long a, long long b)
{
  const long long maxV = std::numeric_limits< long long >::max();
  const long long minV = std::numeric_limits< long long >::min();

  if (op == '+')
  {
    if ((b > 0 && a > maxV - b) || (b < 0 && a < minV - b)) throw std::overflow_error("Overflow");
    return a + b;
  }
  if (op == '-')
  {
    if ((b < 0 && a > maxV + b) || (b > 0 && a < minV + b)) throw std::overflow_error("Overflow");
    return a - b;
  }
  if (op == '*')
  {
    if (a != 0 && (b > maxV / a || b < minV / a)) throw std::overflow_error("Overflow");
    return a * b;
  }
  if (op == '/')
  {
    if (b == 0) throw std::runtime_error("Div by zero");
    return a / b;
  }
  if (op == '%')
  {
    if (b == 0) throw std::runtime_error("Div by zero");
    return (a % b + b) % b;
  }
  if (op == '|') return a | b;
  throw std::invalid_argument("Op error");
}

long long chadin::evaluateInfix(const std::string & expr)
{
  chadin::Stack< char > ops;
  chadin::Queue< std::string > postfix;

  for (size_t i = 0; i < expr.length(); ++i)
  {
    if (std::isspace(expr[i])) continue;
    if (std::isdigit(expr[i]))
    {
      std::string num = "";
      while (i < expr.length() && std::isdigit(expr[i])) num += expr[i++];
      postfix.push(num);
      --i;
    }
    else if (expr[i] == '(') ops.push('(');
    else if (expr[i] == ')')
    {
      while (!ops.isEmpty() && ops.top() != '(')
      {
        postfix.push(std::string(1, ops.top()));
        ops.pop();
      }
      if (ops.isEmpty()) throw std::runtime_error("Bracket error");
      ops.pop();
    }
    else
    {
      while (!ops.isEmpty() && getPriority(ops.top()) >= getPriority(expr[i]))
      {
        postfix.push(std::string(1, ops.top()));
        ops.pop();
      }
      ops.push(expr[i]);
    }
  }
  while (!ops.isEmpty())
  {
    if (ops.top() == '(') throw std::runtime_error("Bracket error");
    postfix.push(std::string(1, ops.top()));
    ops.pop();
  }

  chadin::Stack< long long > res;
  while (!postfix.isEmpty())
  {
    std::string t = postfix.front();
    postfix.pop();
    if (std::isdigit(t[0])) res.push(std::stoll(t));
    else
    {
      long long b = res.top(); res.pop();
      long long a = res.top(); res.pop();
      res.push(performOp(t[0], a, b));
    }
  }
  return res.top();
}

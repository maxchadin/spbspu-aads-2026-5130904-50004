#include <iostream>
#include <fstream>
#include <string>
#include "stack.hpp"
#include "expression_processor.hpp"

int main(int argc, char * argv[])
{
  std::ifstream file;
  std::istream * input = &std::cin;

  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
    input = &file;
  }
  else if (argc > 2)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  chadin::Stack< long long > res;
  std::string line = "";

  try
  {
    while (std::getline(*input, line))
    {
      if (!line.empty())
      {
        res.push(chadin::evaluateInfix(line));
      }
    }
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!res.isEmpty())
  {
    std::cout << res.top();
    res.pop();
    while(!res.isEmpty())
    {
      std::cout << " " << res.top();
      res.pop();
    }
  }

  std::cout << "\n";

  return 0;
}

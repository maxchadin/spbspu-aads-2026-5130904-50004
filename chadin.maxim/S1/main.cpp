#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <stdexcept>
#include <utility>
#include "BiList.hpp"

int main()
{
  using namespace chadin;

  BiList< std::pair< std::string, BiList< unsigned long long > > > data;
  std::string name = "";

  while (std::cin >> name)
  {
    BiList< unsigned long long > numbers;
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF)
    {
      if (std::isspace(std::cin.peek()))
      {
        std::cin.ignore();
        continue;
      }

      unsigned long long num = 0;
      if (std::cin >> num)
      {
        numbers.pushBack(num);
      }
      else
      {
        std::cin.clear();
        while (std::cin.peek() != '\n' && std::cin.peek() != EOF && !std::isdigit(std::cin.peek()))
        {
          std::cin.ignore();
        }
      }
    }
    data.pushBack({name, std::move(numbers)});
  }

  if (data.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  size_t nameCount = 0;
  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    std::cout << it->first;
    if (++nameCount < data.getSize())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  size_t maxLen = 0;
  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    if (it->second.getSize() > maxLen)
    {
      maxLen = it->second.getSize();
    }
  }

  if (maxLen == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  BiList< unsigned long long > sums;
  BiList< LCIter< unsigned long long > > currentIters;

  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    currentIters.pushBack(it->second.cbegin());
  }

  try
  {
    for (size_t i = 0; i < maxLen; ++i)
    {
      unsigned long long rowSum = 0;
      bool isFirstInRow = true;
      auto currIt = currentIters.begin();

      for (auto dataIt = data.cbegin(); dataIt != data.cend(); ++dataIt)
      {
        if (*currIt != dataIt->second.cend())
        {
          unsigned long long val = **currIt;
          if (!isFirstInRow)
          {
            std::cout << " ";
          }
          std::cout << val;
          isFirstInRow = false;

          if (std::numeric_limits< unsigned long long >::max() - rowSum < val)
          {
            throw std::overflow_error("Sum overflow");
          }
          rowSum += val;
          ++(*currIt);
        }
        ++currIt;
      }
      std::cout << "\n";
      sums.pushBack(rowSum);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  size_t sumCount = 0;
  for (auto it = sums.cbegin(); it != sums.cend(); ++it)
  {
    std::cout << *it;
    if (++sumCount < sums.getSize())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}

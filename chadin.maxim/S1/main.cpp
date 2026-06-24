#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "BiList.hpp"

int main()
{
  using namespace chadin;

  BiList< std::pair< std::string, BiList< unsigned long long > > > data;
  std::string name;

  while (std::cin >> name)
  {
    BiList< unsigned long long > numbers;
    char c;
    while (std::cin.get(c))
    {
      if (c == '\n')
      {
        break;
      }
      if (std::isspace(c))
      {
        continue;
      }

      std::cin.putback(c);
      unsigned long long num = 0;

      if (std::cin >> num)
      {
        numbers.pushBack(num);
      }
      else
      {
        std::cin.clear();
        std::cin.ignore();
      }
    }
    data.pushBack({name, std::move(numbers)});
  }

  if (data.isEmpty())
  {
    std::cout << "0\n";
    return 0;
  }

  size_t maxLen = 0;
  for (auto it = data.cbegin(); it != data.cend(); )
  {
    std::cout << it->first;
    if (it->second.getSize() > maxLen)
    {
      maxLen = it->second.getSize();
    }
    if (++it != data.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  if (maxLen == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  BiList< LCIter< unsigned long long > > currentIters;
  BiList< LCIter< unsigned long long > > endIters;

  for (auto it = data.cbegin(); it != data.cend(); ++it)
  {
    currentIters.pushBack(it->second.cbegin());
    endIters.pushBack(it->second.cend());
  }

  BiList< unsigned long long > sums;

  for (size_t i = 0; i < maxLen; ++i)
  {
    unsigned long long rowSum = 0;
    bool isFirstInRow = true;

    auto currIt = currentIters.begin();
    auto endIt = endIters.cbegin();

    for (auto dataIt = data.cbegin(); dataIt != data.cend(); ++dataIt)
    {
      if (*currIt != *endIt)
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
          std::cerr << "Sum overflow\n";
          return 1;
        }
        rowSum += val;
        ++(*currIt);
      }
      ++currIt;
      ++endIt;
    }
    std::cout << "\n";
    sums.pushBack(rowSum);
  }

  for (auto it = sums.cbegin(); it != sums.cend(); )
  {
    std::cout << *it;
    if (++it != sums.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}

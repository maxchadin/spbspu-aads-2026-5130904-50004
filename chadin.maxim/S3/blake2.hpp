#ifndef BLAKE2_HPP
#define BLAKE2_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace chadin {
  struct Blake2sHash {
    size_t operator()(const std::string& str) const;
  };

  struct PairBlake2sHash {
    size_t operator()(const std::pair< std::string, std::string >& p) const;
  };

  struct StringEqual {
    bool operator()(const std::string& a, const std::string& b) const;
  };

  struct PairEqual {
    bool operator()(const std::pair< std::string, std::string >& a,
                    const std::pair< std::string, std::string >& b) const;
  };
}

#endif

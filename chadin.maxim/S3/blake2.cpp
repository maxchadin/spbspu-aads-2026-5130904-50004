#include "blake2.hpp"

namespace chadin {
  size_t Blake2sHash::operator()(const std::string& str) const
  {
    const uint32_t IV[8] = {
      0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
      0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
    };
    uint32_t hash[8];
    for (int i = 0; i < 8; ++i) {
      hash[i] = IV[i];
    }

    for (size_t i = 0; i < str.length(); ++i) {
      uint32_t charData = static_cast< uint32_t >(str[i]);
      hash[i % 8] ^= charData;
      hash[(i + 1) % 8] += charData;
    }

    size_t finalHash = 0;
    for (int i = 0; i < 8; ++i) {
      finalHash ^= hash[i];
      finalHash = (finalHash << 5) | (finalHash >> (sizeof(size_t) * 8 - 5));
    }
    return finalHash;
  }

  size_t PairBlake2sHash::operator()(const std::pair< std::string, std::string >& p) const
  {
    Blake2sHash hasher;
    size_t h1 = hasher(p.first);
    size_t h2 = hasher(p.second);
    return h1 ^ (h2 << 1);
  }

  bool StringEqual::operator()(const std::string& a, const std::string& b) const
  {
    return a == b;
  }

  bool PairEqual::operator()(const std::pair< std::string, std::string >& a, const std::pair< std::string, std::string >& b) const
  {
    return (a.first == b.first) && (a.second == b.second);
  }
}

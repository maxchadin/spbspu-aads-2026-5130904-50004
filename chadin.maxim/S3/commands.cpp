#include "commands.hpp"

namespace {
  template< class T >
  void sortAscending(chadin::Vector< T >& vec)
  {
    if (vec.size() < 2) {
      return;
    }
    for (size_t i = 0; i < vec.size() - 1; ++i) {
      for (size_t j = 0; j < vec.size() - i - 1; ++j) {
        if (vec[j] > vec[j + 1]) {
          T temp = vec[j];
          vec[j] = vec[j + 1];
          vec[j + 1] = temp;
        }
      }
    }
  }
}

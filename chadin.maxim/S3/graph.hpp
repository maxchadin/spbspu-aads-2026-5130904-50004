#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vector.hpp"
#include "hashTable.hpp"
#include "blake2.hpp"
#include <string>

namespace chadin {
  class Graph {
  public:
    void addVertex(const std::string& v);
    void addEdge(const std::string& from, const std::string& to, unsigned int weight);
    const Vector< std::string >& getVertexes() const;
    HashTable< std::pair< std::string, std::string >, Vector< unsigned int >,
               PairBlake2sHash, PairEqual >& getEdges();

  private:
    Vector< std::string > vertexes_;
    HashTable< std::pair< std::string, std::string >, Vector< unsigned int >,
               PairBlake2sHash, PairEqual > edges_{16, 4};
  };
}

#endif

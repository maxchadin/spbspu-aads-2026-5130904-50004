#include "graph.hpp"

namespace chadin {
  void Graph::addVertex(const std::string& v)
  {
    for (size_t i = 0; i < vertexes_.size(); ++i) {
      if (vertexes_[i] == v) {
        return;
      }
    }
    vertexes_.pushBack(v);
  }

  void Graph::addEdge(const std::string& from, const std::string& to, unsigned int weight)
  {
    addVertex(from);
    addVertex(to);
    std::pair< std::string, std::string > key(from, to);

    if (!edges_.has(key)) {
      Vector< unsigned int > weights;
      weights.pushBack(weight);
      edges_.add(key, weights);
    } else {
      edges_.get(key).pushBack(weight);
    }
  }

  const Vector< std::string >& Graph::getVertexes() const
  {
    return vertexes_;
  }

  HashTable< std::pair< std::string, std::string >, Vector< unsigned int >,
             PairBlake2sHash, PairEqual >& Graph::getEdges()
  {
    return edges_;
  }
}

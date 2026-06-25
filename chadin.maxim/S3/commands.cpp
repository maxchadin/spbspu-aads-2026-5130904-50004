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

namespace chadin {
  void printGraphs(GraphTable& allGraphs, std::ostream& out)
  {
    Vector< std::string > names;
    for (auto it = allGraphs.begin(); it != allGraphs.end(); ++it) {
      names.pushBack(it.getKey());
    }
    sortAscending(names);
    for (size_t i = 0; i < names.size(); ++i) {
      out << names[i] << '\n';
    }
  }

  void printVertexes(GraphTable& allGraphs, const std::string& graphName, std::ostream& out)
  {
    if (!allGraphs.has(graphName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Graph& g = allGraphs.get(graphName);
    Vector< std::string > verts = g.getVertexes();
    sortAscending(verts);
    for (size_t i = 0; i < verts.size(); ++i) {
      out << verts[i] << '\n';
    }
  }

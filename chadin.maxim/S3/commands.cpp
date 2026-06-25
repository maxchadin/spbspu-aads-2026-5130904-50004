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

  void printOutbound(GraphTable& allGraphs, const std::string& graphName, const std::string& vertexName, std::ostream& out)
  {
    if (!allGraphs.has(graphName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Graph& g = allGraphs.get(graphName);
    const Vector< std::string >& verts = g.getVertexes();
    bool hasVertex = false;
    for (size_t i = 0; i < verts.size(); ++i) {
      if (verts[i] == vertexName) {
        hasVertex = true;
        break;
      }
    }
    if (!hasVertex) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    auto& edges = g.getEdges();
    Vector< std::string > destinations;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
      std::pair< std::string, std::string > key = it.getKey();
      if (key.first == vertexName) {
        destinations.pushBack(key.second);
      }
    }
    sortAscending(destinations);

    for (size_t i = 0; i < destinations.size(); ++i) {
      out << destinations[i];
      std::pair< std::string, std::string > edgeKey(vertexName, destinations[i]);
      Vector< unsigned int > weights = edges.get(edgeKey);
      sortAscending(weights);
      for (size_t j = 0; j < weights.size(); ++j) {
        out << " " << weights[j];
      }
      out << '\n';
    }
  }

  void printInbound(GraphTable& allGraphs, const std::string& graphName, const std::string& vertexName, std::ostream& out)
  {
    if (!allGraphs.has(graphName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Graph& g = allGraphs.get(graphName);
    const Vector< std::string >& verts = g.getVertexes();
    bool hasVertex = false;
    for (size_t i = 0; i < verts.size(); ++i) {
      if (verts[i] == vertexName) {
        hasVertex = true;
        break;
      }
    }
    if (!hasVertex) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    auto& edges = g.getEdges();
    Vector< std::string > origins;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
      std::pair< std::string, std::string > key = it.getKey();
      if (key.second == vertexName) {
        origins.pushBack(key.first);
      }
    }
    sortAscending(origins);

    for (size_t i = 0; i < origins.size(); ++i) {
      out << origins[i];
      std::pair< std::string, std::string > edgeKey(origins[i], vertexName);
      Vector< unsigned int > weights = edges.get(edgeKey);
      sortAscending(weights);
      for (size_t j = 0; j < weights.size(); ++j) {
        out << " " << weights[j];
      }
      out << '\n';
    }
  }

  void executeBind(GraphTable& allGraphs, std::istream& in, std::ostream& out)
  {
    std::string graphName, v1, v2;
    unsigned int weight;
    in >> graphName >> v1 >> v2 >> weight;
    if (!allGraphs.has(graphName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    allGraphs.get(graphName).addEdge(v1, v2, weight);
  }

  void executeCut(GraphTable& allGraphs, std::istream& in, std::ostream& out)
  {
    std::string graphName, v1, v2;
    unsigned int weight;
    in >> graphName >> v1 >> v2 >> weight;
    if (!allGraphs.has(graphName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    Graph& g = allGraphs.get(graphName);
    std::pair< std::string, std::string > edgeKey(v1, v2);
    auto& edges = g.getEdges();

    if (!edges.has(edgeKey)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    Vector< unsigned int >& weights = edges.get(edgeKey);
    bool weightFound = false;
    for (size_t i = 0; i < weights.size(); ++i) {
      if (weights[i] == weight) {
        weights.erase(i);
        weightFound = true;
        break;
      }
    }

    if (!weightFound) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (weights.size() == 0) {
      edges.drop(edgeKey);
    }
  }

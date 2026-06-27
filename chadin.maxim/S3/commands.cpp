#include "commands.hpp"
#include <sstream>

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

  void executeBind(GraphTable& allGraphs, const std::string& gName, const std::string& v1, const std::string& v2, unsigned int weight, std::ostream& out)
  {
    if (!allGraphs.has(gName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    allGraphs.get(gName).addEdge(v1, v2, weight);
  }

  void executeCut(GraphTable& allGraphs, const std::string& gName, const std::string& v1, const std::string& v2, unsigned int weight, std::ostream& out)
  {
    if (!allGraphs.has(gName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    Graph& g = allGraphs.get(gName);

    const auto& verts = g.getVertexes();
    bool hasV1 = false;
    bool hasV2 = false;
    for (size_t i = 0; i < verts.size(); ++i) {
      if (verts[i] == v1) {
        hasV1 = true;
      }
      if (verts[i] == v2) {
        hasV2 = true;
      }
    }
    if (!hasV1 || !hasV2) {
      out << "<INVALID COMMAND>\n";
      return;
    }

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

  void executeCreate(GraphTable& allGraphs, const std::string& gName, const Vector< std::string >& newVerts, std::ostream& out)
  {
    if (allGraphs.has(gName)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Graph g;
    for (size_t i = 0; i < newVerts.size(); ++i) {
      g.addVertex(newVerts[i]);
    }
    allGraphs.add(gName, g);
  }

  void executeMerge(GraphTable& allGraphs, const std::string& newGraph, const std::string& oldG1, const std::string& oldG2, std::ostream& out)
  {
    if (allGraphs.has(newGraph) || !allGraphs.has(oldG1) || !allGraphs.has(oldG2)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    Graph g;
    Graph& g1 = allGraphs.get(oldG1);
    Graph& g2 = allGraphs.get(oldG2);

    const auto& verts1 = g1.getVertexes();
    for (size_t i = 0; i < verts1.size(); ++i) {
      g.addVertex(verts1[i]);
    }
    const auto& verts2 = g2.getVertexes();
    for (size_t i = 0; i < verts2.size(); ++i) {
      g.addVertex(verts2[i]);
    }

    auto& edges1 = g1.getEdges();
    for (auto it = edges1.begin(); it != edges1.end(); ++it) {
      const auto& w = *it;
      for (size_t i = 0; i < w.size(); ++i) {
        g.addEdge(it.getKey().first, it.getKey().second, w[i]);
      }
    }

    auto& edges2 = g2.getEdges();
    for (auto it = edges2.begin(); it != edges2.end(); ++it) {
      const auto& w = *it;
      for (size_t i = 0; i < w.size(); ++i) {
        g.addEdge(it.getKey().first, it.getKey().second, w[i]);
      }
    }
    allGraphs.add(newGraph, g);
  }

  void executeExtract(GraphTable& allGraphs, const std::string& newGraph, const std::string& oldGraph, const Vector< std::string >& extrVerts, std::ostream& out)
  {
    if (allGraphs.has(newGraph) || !allGraphs.has(oldGraph)) {
      out << "<INVALID COMMAND>\n";
      return;
    }

    Graph& oldG = allGraphs.get(oldGraph);
    const auto& oldVerts = oldG.getVertexes();
    for (size_t i = 0; i < extrVerts.size(); ++i) {
      bool found = false;
      for (size_t j = 0; j < oldVerts.size(); ++j) {
        if (oldVerts[j] == extrVerts[i]) {
          found = true;
          break;
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
        return;
      }
    }

    Graph g;
    for (size_t i = 0; i < extrVerts.size(); ++i) {
      g.addVertex(extrVerts[i]);
    }

    auto& oldEdges = oldG.getEdges();
    for (auto it = oldEdges.begin(); it != oldEdges.end(); ++it) {
      const auto& key = it.getKey();
      bool hasSrc = false;
      bool hasDst = false;
      for (size_t i = 0; i < extrVerts.size(); ++i) {
        if (extrVerts[i] == key.first) { hasSrc = true; }
        if (extrVerts[i] == key.second) { hasDst = true; }
      }
      if (hasSrc && hasDst) {
        const auto& w = *it;
        for (size_t i = 0; i < w.size(); ++i) {
          g.addEdge(key.first, key.second, w[i]);
        }
      }
    }
    allGraphs.add(newGraph, g);
  }

  void processCommands(std::istream& in, std::ostream& out, GraphTable& allGraphs)
  {
    std::string line;
    while (std::getline(in, line)) {
      if (line.empty()) {
        continue;
      }

      std::istringstream iss(line);
      std::string cmd;
      if (!(iss >> cmd)) {
        continue;
      }

      if (cmd == "graphs") {
        std::string extra;
        if (iss >> extra) {
          out << "<INVALID COMMAND>\n";
        } else {
          printGraphs(allGraphs, out);
        }
      } else if (cmd == "vertexes") {
        std::string graphName, extra;
        if (!(iss >> graphName) || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          printVertexes(allGraphs, graphName, out);
        }
      } else if (cmd == "outbound") {
        std::string graphName, vertexName, extra;
        if (!(iss >> graphName >> vertexName) || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          printOutbound(allGraphs, graphName, vertexName, out);
        }
      } else if (cmd == "inbound") {
        std::string graphName, vertexName, extra;
        if (!(iss >> graphName >> vertexName) || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          printInbound(allGraphs, graphName, vertexName, out);
        }
      } else if (cmd == "bind") {
        std::string graphName, v1, v2, extra;
        unsigned int weight;
        if (!(iss >> graphName >> v1 >> v2 >> weight) || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          executeBind(allGraphs, graphName, v1, v2, weight, out);
        }
      } else if (cmd == "cut") {
        std::string graphName, v1, v2, extra;
        unsigned int weight;
        if (!(iss >> graphName >> v1 >> v2 >> weight) || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          executeCut(allGraphs, graphName, v1, v2, weight, out);
        }
      } else if (cmd == "create") {
        std::string graphName;
        size_t countK;
        if (!(iss >> graphName >> countK)) {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        Vector< std::string > newVerts;
        bool parsingOk = true;
        for (size_t i = 0; i < countK; ++i) {
          std::string v;
          if (!(iss >> v)) {
            parsingOk = false;
            break;
          }
          newVerts.pushBack(v);
        }
        std::string extra;
        if (!parsingOk || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          executeCreate(allGraphs, graphName, newVerts, out);
        }
      } else if (cmd == "merge") {
        std::string newGraph, oldG1, oldG2, extra;
        if (!(iss >> newGraph >> oldG1 >> oldG2) || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          executeMerge(allGraphs, newGraph, oldG1, oldG2, out);
        }
      } else if (cmd == "extract") {
        std::string newGraph, oldGraph;
        size_t countK;
        if (!(iss >> newGraph >> oldGraph >> countK)) {
          out << "<INVALID COMMAND>\n";
          continue;
        }
        Vector< std::string > extrVerts;
        bool parsingOk = true;
        for (size_t i = 0; i < countK; ++i) {
          std::string v;
          if (!(iss >> v)) {
            parsingOk = false;
            break;
          }
          extrVerts.pushBack(v);
        }
        std::string extra;
        if (!parsingOk || (iss >> extra)) {
          out << "<INVALID COMMAND>\n";
        } else {
          executeExtract(allGraphs, newGraph, oldGraph, extrVerts, out);
        }
      } else {
        out << "<INVALID COMMAND>\n";
      }
    }
  }
}

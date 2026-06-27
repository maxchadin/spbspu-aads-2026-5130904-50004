#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph.hpp"
#include "hashTable.hpp"
#include "blake2.hpp"
#include <string>
#include <istream>
#include <ostream>

namespace chadin {
  using GraphTable = HashTable< std::string, Graph, Blake2sHash, StringEqual >;

  void printGraphs(GraphTable& allGraphs, std::ostream& out);

  void printVertexes(GraphTable& allGraphs, const std::string& graphName,
                     std::ostream& out);

  void printOutbound(GraphTable& allGraphs, const std::string& graphName,
                     const std::string& vertexName, std::ostream& out);

  void printInbound(GraphTable& allGraphs, const std::string& graphName,
                    const std::string& vertexName, std::ostream& out);

  void executeBind(GraphTable& allGraphs, const std::string& gName,
                   const std::string& v1, const std::string& v2,
                   unsigned int weight, std::ostream& out);

  void executeCut(GraphTable& allGraphs, const std::string& gName,
                  const std::string& v1, const std::string& v2,
                  unsigned int weight, std::ostream& out);

  void executeCreate(GraphTable& allGraphs, const std::string& gName,
                     const Vector< std::string >& newVerts, std::ostream& out);

  void executeMerge(GraphTable& allGraphs, const std::string& newGraph,
                    const std::string& oldG1, const std::string& oldG2,
                    std::ostream& out);

  void executeExtract(GraphTable& allGraphs, const std::string& newGraph,
                      const std::string& oldGraph,
                      const Vector< std::string >& extrVerts, std::ostream& out);

  void processCommands(std::istream& in, std::ostream& out, GraphTable& allGraphs);
}

#endif
